#include "GameObjectLegacy.h"
#include "GameMain.h"

#ifdef GOBJ

using namespace MathUtils;

bool GameObject::DEBUG_HITBOX = FALSE;

//*

// <<ティック>> --------------------------------------------------------

// <最終時刻>
static int g_lastcount = -1;
// <デルタミリ秒>
static int g_deltamilliseconds = 0;

// <<テクスチャ>> ------------------------------------------------------

// <テクスチャ作成>
GameTexture::GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <テクスチャ作成>
GameTexture::GameTexture(HGRP texture) :
	texture(texture)
{
	anchor = {};
	size = {};
	pivot = { .5f, .5f };

	if (texture == TEXTURE_MISSING)
		return;

	float width, height;
	if (GetGraphSizeF(texture, &width, &height) != -1)
	{
		size = { width, height };
		return;
	}

	texture = TEXTURE_MISSING;
}

// <テクスチャなし>
GameTexture::GameTexture() :
	GameTexture(TEXTURE_NONE, Vec2{}, Vec2{})
{
}

// <<スプライト>> ------------------------------------------------------

// <スプライト作成>
GameSprite::GameSprite(GameTexture texture, float scale, float angle) :
	color(Colors::White),
	texture(texture),
	size(texture.size),
	num_columns(1),
	frame_index(0),
	offset(Vec2{}),
	scale(scale),
	angle(angle)
{
}

// <スプライトなし>
GameSprite::GameSprite() :
	GameSprite(GameTexture{}, 0, 0)
{
}

// <スプライト更新>
void GameSprite::SetFrame(int frame)
{
	// フレーム番号
	frame_index = frame;
}

// <スプライト描画>
void GameSprite::Render(const Vec2* pos)
{
	int column = frame_index%num_columns;
	int row = frame_index / num_columns;

	Vec2 anchor = texture.anchor + Vec2{ size.x * column, size.y * row };

	// スプライト描画
	DrawRectRotaGraph2F(
		pos->x + offset.x, pos->y + offset.y,
		(int)anchor.x, (int)anchor.y,
		(int)texture.size.x, (int)texture.size.y,
		texture.pivot.x * texture.size.x, texture.pivot.y * texture.size.x,
		(double)scale,
		(double)angle,
		texture.texture,
		TRUE
	);
}

// <<スプライトアニメーション>> ----------------------------------------

// <スプライトアニメーション作成>
GameSpriteAnimation::GameSpriteAnimation(GameTexture texture, int frame_start, int frame_end, int frame_duration, float scale, float angle, bool pause) :
	GameSprite(texture, scale, angle),
	frame_start(frame_start),
	frame_end(frame_end),
	frame_duration(0),
	elapsed_time(0),
	loop_flag(true),
	pause_flag(pause),
	result(AnimationState::RUNNING)
{
}

// <スプライトアニメーションなし>
GameSpriteAnimation::GameSpriteAnimation() :
	GameSpriteAnimation(GameTexture{}, -1, -1, 1, 0, 0, true)
{
}

// <スプライトアニメーション更新>
AnimationState GameSpriteAnimation::Update()
{
	if (!pause_flag && frame_start >= 0 && frame_end >= 0)
	{
		// アニメーションしているか
		result = AnimationState::RUNNING;
		// 経過時間
		elapsed_time++;
		// 最初のフレーム以上
		frame_index = GetMax(frame_index, frame_start);

		// フレーム経過
		if (elapsed_time > frame_duration)
		{
			// 経過時間
			elapsed_time = 0;
			// フレーム番号
			frame_index++;

			// 最初に戻る
			if (frame_index > frame_end)
			{
				// ループするなら
				if (loop_flag)
					// 最初に戻る
					frame_index = frame_start;
				else
					// 最後のフレームで停止
					frame_index = frame_end;
				// アニメーション完了
				result = AnimationState::FINISHED;
			}
		}
	}
	else
		// アニメーションしているか
		result = AnimationState::IDLE;

	return result;
}

// <<ティック>> --------------------------------------------------------

// <オブジェクト作成>
void GameTick_Update(void)
{
	int now = GetNowCount();
	g_deltamilliseconds = GetMin(100, now - g_lastcount);
	g_lastcount = now;
}

// <<オブジェクト>> ----------------------------------------------------

// <オブジェクト作成>
GameObject::GameObject(Vec2 pos, Vec2 vel, Vec2 size) :
	pos(pos),
	vel(vel),
	size(size),
	shape(ShapeType::BOX),
	fill(false),
	edge(0),
	sprite_connection(Connection::NONE),
	alive(true),
	state(1),
	type(0),
	count(Timer{})
{
}

// <線オブジェクト作成>
GameObject GameObject::CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel)
{
	Vec2 pos = (pos1 + pos2) * .5f;
	Vec2 size = pos2 - pos1;
	GameObject obj = GameObject{ pos, vel, size };
	obj.shape = ShapeType::LINE;
	return obj;
}

// <オブジェクト削除>
void GameObject::Dispose()
{
	alive = FALSE;
}

// <オブジェクト確認>
bool GameObject::IsAlive()
{
	return alive;
}

// <オブジェクト座標更新>
void GameObject::UpdatePosition()
{
	pos.x += vel.x;// *(g_deltamilliseconds / 17.f);
	pos.y += vel.y;// *(g_deltamilliseconds / 17.f);
}

// <枠取得>
Dimension GameObject::GetCollision()
{
	return{ pos, size };
}

// <オブジェクト描画>
void GameObject::Render(const Vec2* translate)
{
	Dimension collision = GetCollision();

	float box_xl = collision.GetX(HorizontalSide::LEFT) + translate->x;
	float box_xc = collision.GetX(HorizontalSide::CENTER) + translate->x;
	float box_xr = collision.GetX(HorizontalSide::RIGHT) + translate->x;
	float box_yt = collision.GetY(VerticalSide::TOP) + translate->y;
	float box_ym = collision.GetY(VerticalSide::CENTER) + translate->y;
	float box_yb = collision.GetY(VerticalSide::BOTTOM) + translate->y;
	Vec2 box_t = { box_xc, box_ym };

	// テクスチャを確認
	if (sprite.texture.texture != GameTexture::TEXTURE_NONE)
	{
		if (sprite.texture.texture != GameTexture::TEXTURE_MISSING)
		{
			switch (sprite_connection)
			{
			case Connection::LOOP:
			case Connection::BARRIER:
				{
					// リピートタイル (回転、テクスチャ中心座標 には未対応)
					Vec2 center_offset = sprite.texture.pivot * sprite.texture.size * sprite.scale;
					Vec2 sp_pos = box_t + sprite.offset;
					Vec2 sp_size = sprite.texture.size * sprite.scale;

					float go_left = box_xl;
					float go_right = box_xr;
					float go_top = box_yt;
					float go_bottom = box_yb;

					float sp_left = sp_pos.x - sp_size.x / 2;
					float sp_right = sp_pos.x + sp_size.x / 2;
					float sp_top = sp_pos.y - sp_size.y / 2;
					float sp_bottom = sp_pos.y + sp_size.y / 2;

					switch (sprite_connection)
					{
					case Connection::BARRIER:
						if (sp_left < go_right && go_left < sp_right && sp_top < go_bottom && go_top < sp_bottom)
							sprite.Render(&box_t);
						break;
					case Connection::LOOP:
						float offset_x = GetLoopRange(go_left, sp_left, sp_right) - sp_left;
						float offset_y = GetLoopRange(go_top, sp_top, sp_bottom) - sp_top;

						if (sp_size.x >= 1.f && sp_size.y >= 1.f)
						{
							for (float iy = go_top + sp_size.y / 2 - offset_y - center_offset.y; iy < go_bottom; iy += sp_size.y)
							{
								for (float ix = go_left + sp_size.x / 2 - offset_x - center_offset.x; ix < go_right; ix += sp_size.x)
								{
									sprite.Render(&Vec2{ ix + sp_size.x / 2 - sprite.offset.x, iy + sp_size.y / 2 - sprite.offset.y });

									if (DEBUG_HITBOX)
										DrawBoxAA(ix, iy, ix + sp_size.x, iy + sp_size.y, sprite.color, FALSE, .5f);
								}
							}
						}

						break;
					}

					break;
				}
			default:
				sprite.Render(&box_t);
				break;
			}
		}
		else
		{
			// NULLテクスチャを表示
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, Colors::Black, TRUE);
			DrawBoxAA(box_xl, box_yt, box_xc, box_ym, Colors::Fuchsia, TRUE);
			DrawBoxAA(box_xc, box_ym, box_xr, box_yb, Colors::Fuchsia, TRUE);
			//DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
		}
	}

	// 図形描画
	switch (shape)
	{
	default:
	case ShapeType::BOX:
		// 矩形描画
		if (fill)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, TRUE);
		if (edge > 0)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, edge);
		if (DEBUG_HITBOX)
		{
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, .5f);
			DrawLineAA(box_xr, box_yt, box_xl, box_yb, sprite.color, .5f);
		}
		break;
	case ShapeType::CIRCLE:
		{
			float r1 = GetMin(GetAbs(size.x), GetAbs(size.y)) / 2;
			// 円
			if (fill)
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, TRUE);
			if (edge > 0)
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, FALSE, edge);
			if (DEBUG_HITBOX)
			{
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, FALSE, .5f);
				DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
				DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, .5f);
				DrawLineAA(box_xr, box_yt, box_xl, box_yb, sprite.color, .5f);
			}
			break;
		}
	case ShapeType::LINE:
		{
			float r1 = edge;
			// 線
			if (DEBUG_HITBOX)
				Graphics::DrawVector(size, Vec2{ box_xl, box_yt }, sprite.color, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, r1);
			break;
		}
	}
}

// <オブジェクトサイズ変更>
void GameObject::SetSize(float scale, float objsize)
{
	sprite.scale = scale;
	size = { objsize * scale, objsize * scale };
}

// <<フィールドオブジェクト>> ------------------------------------------

// <フィールドオブジェクト作成>
Field::Field(void) :
	GameObject(
		Vec2{ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) },
		Vec2{},
		Vec2{ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) }
	)
{
}

/**/
#endif GOBJ