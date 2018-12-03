#include "GameObjectLegacy.h"
#include "GameMain.h"

#ifdef GOBJ

using namespace MathUtils;

bool GameObject::DEBUG_HITBOX = FALSE;

//*

// <<�e�B�b�N>> --------------------------------------------------------

// <�ŏI����>
static int g_lastcount = -1;
// <�f���^�~���b>
static int g_deltamilliseconds = 0;

// <<�e�N�X�`��>> ------------------------------------------------------

// <�e�N�X�`���쐬>
GameTexture::GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <�e�N�X�`���쐬>
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

// <�e�N�X�`���Ȃ�>
GameTexture::GameTexture() :
	GameTexture(TEXTURE_NONE, Vec2{}, Vec2{})
{
}

// <<�X�v���C�g>> ------------------------------------------------------

// <�X�v���C�g�쐬>
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

// <�X�v���C�g�Ȃ�>
GameSprite::GameSprite() :
	GameSprite(GameTexture{}, 0, 0)
{
}

// <�X�v���C�g�X�V>
void GameSprite::SetFrame(int frame)
{
	// �t���[���ԍ�
	frame_index = frame;
}

// <�X�v���C�g�`��>
void GameSprite::Render(const Vec2* pos)
{
	int column = frame_index%num_columns;
	int row = frame_index / num_columns;

	Vec2 anchor = texture.anchor + Vec2{ size.x * column, size.y * row };

	// �X�v���C�g�`��
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

// <<�X�v���C�g�A�j���[�V����>> ----------------------------------------

// <�X�v���C�g�A�j���[�V�����쐬>
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

// <�X�v���C�g�A�j���[�V�����Ȃ�>
GameSpriteAnimation::GameSpriteAnimation() :
	GameSpriteAnimation(GameTexture{}, -1, -1, 1, 0, 0, true)
{
}

// <�X�v���C�g�A�j���[�V�����X�V>
AnimationState GameSpriteAnimation::Update()
{
	if (!pause_flag && frame_start >= 0 && frame_end >= 0)
	{
		// �A�j���[�V�������Ă��邩
		result = AnimationState::RUNNING;
		// �o�ߎ���
		elapsed_time++;
		// �ŏ��̃t���[���ȏ�
		frame_index = GetMax(frame_index, frame_start);

		// �t���[���o��
		if (elapsed_time > frame_duration)
		{
			// �o�ߎ���
			elapsed_time = 0;
			// �t���[���ԍ�
			frame_index++;

			// �ŏ��ɖ߂�
			if (frame_index > frame_end)
			{
				// ���[�v����Ȃ�
				if (loop_flag)
					// �ŏ��ɖ߂�
					frame_index = frame_start;
				else
					// �Ō�̃t���[���Œ�~
					frame_index = frame_end;
				// �A�j���[�V��������
				result = AnimationState::FINISHED;
			}
		}
	}
	else
		// �A�j���[�V�������Ă��邩
		result = AnimationState::IDLE;

	return result;
}

// <<�e�B�b�N>> --------------------------------------------------------

// <�I�u�W�F�N�g�쐬>
void GameTick_Update(void)
{
	int now = GetNowCount();
	g_deltamilliseconds = GetMin(100, now - g_lastcount);
	g_lastcount = now;
}

// <<�I�u�W�F�N�g>> ----------------------------------------------------

// <�I�u�W�F�N�g�쐬>
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

// <���I�u�W�F�N�g�쐬>
GameObject GameObject::CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel)
{
	Vec2 pos = (pos1 + pos2) * .5f;
	Vec2 size = pos2 - pos1;
	GameObject obj = GameObject{ pos, vel, size };
	obj.shape = ShapeType::LINE;
	return obj;
}

// <�I�u�W�F�N�g�폜>
void GameObject::Dispose()
{
	alive = FALSE;
}

// <�I�u�W�F�N�g�m�F>
bool GameObject::IsAlive()
{
	return alive;
}

// <�I�u�W�F�N�g���W�X�V>
void GameObject::UpdatePosition()
{
	pos.x += vel.x;// *(g_deltamilliseconds / 17.f);
	pos.y += vel.y;// *(g_deltamilliseconds / 17.f);
}

// <�g�擾>
Dimension GameObject::GetCollision()
{
	return{ pos, size };
}

// <�I�u�W�F�N�g�`��>
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

	// �e�N�X�`�����m�F
	if (sprite.texture.texture != GameTexture::TEXTURE_NONE)
	{
		if (sprite.texture.texture != GameTexture::TEXTURE_MISSING)
		{
			switch (sprite_connection)
			{
			case Connection::LOOP:
			case Connection::BARRIER:
				{
					// ���s�[�g�^�C�� (��]�A�e�N�X�`�����S���W �ɂ͖��Ή�)
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
			// NULL�e�N�X�`����\��
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, Colors::Black, TRUE);
			DrawBoxAA(box_xl, box_yt, box_xc, box_ym, Colors::Fuchsia, TRUE);
			DrawBoxAA(box_xc, box_ym, box_xr, box_yb, Colors::Fuchsia, TRUE);
			//DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
		}
	}

	// �}�`�`��
	switch (shape)
	{
	default:
	case ShapeType::BOX:
		// ��`�`��
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
			// �~
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
			// ��
			if (DEBUG_HITBOX)
				Graphics::DrawVector(size, Vec2{ box_xl, box_yt }, sprite.color, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, r1);
			break;
		}
	}
}

// <�I�u�W�F�N�g�T�C�Y�ύX>
void GameObject::SetSize(float scale, float objsize)
{
	sprite.scale = scale;
	size = { objsize * scale, objsize * scale };
}

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�t�B�[���h�I�u�W�F�N�g�쐬>
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