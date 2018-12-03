#pragma once

#ifdef GOBJ

// <アニメーションの結果>
enum class AnimationState
{
	RUNNING,					// アニメーションが実行中の状態
	FINISHED,					// アニメーション再生が完了した状態
	IDLE,						// アニメーションしていない状態
};

// <テクスチャ>
class GameTexture final
{
public:
	static constexpr int TEXTURE_MISSING = -1;		// テクスチャが見つかりません
	static constexpr int TEXTURE_NONE = -2;			// テクスチャなし

public:
	HGRP texture;				// <テクスチャ>
	Vec2 anchor;				// <テクスチャ基点>
	Vec2 size;					// <テクスチャサイズ>
	Vec2 pivot;					// <テクスチャ中心>

public:
	// <テクスチャ作成>
	GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot = Vec2{ .5f, .5f });

	// <テクスチャ作成>
	GameTexture(HGRP texture);

	// <テクスチャなし>
	GameTexture();
};

class Transform final
{
public:
	Vec2 position;				// <テクスチャ>
	float rotation;				// <回転>
	float scale;				// <スケール>

public:
	Transform(const Vec2& position, float rotation, float scale);

	Transform();
};

class Sprite
{
public:
	virtual ~Sprite() {}

	// <スプライト描画>
	virtual void Render(const Transform& tranform) = 0;
};

class TextureSprite : public Sprite
{
public:
	GameTexture texture;		
	Transform transform;

public:
	TextureSprite(const GameTexture& texture, const Transform& transform);

	// <スプライトなし>
	TextureSprite();

	virtual ~TextureSprite() {}

	// <スプライト描画>
	void Render(const Transform& tranform) override;
};

class ClippingSprite : public Sprite
{

};

// <スプライトオブジェクト>
class GameSprite
{
public:
	Color color;			// <色>
	GameTexture texture;		// <テクスチャ>
	Vec2 size;					// <サイズ>
	int num_columns;			// <1行あたりのフレーム数>
	int frame_index;			// <現在のフレームのインデックス>
	Vec2 offset;				// <オフセット>
	float scale;				// <スケール>
	float angle;				// <回転>
public:
	GameSprite(GameTexture texture, float scale = 1, float angle = 0);

	// <スプライトなし>
	GameSprite();

	virtual ~GameSprite() {};

	// <スプライト更新>
	void SetFrame(int frame);

	// <スプライト描画>
	void Render(const Vec2* pos);
};

// <スプライトアニメーション>
class GameSpriteAnimation : public GameSprite
{
public:
	int frame_start;			// 開始フレームのインデックス
	int frame_end;				// 終了フレームのインデックス
	int frame_duration;			// フレーム間隔
	int elapsed_time;			// 現在のフレームの経過時間
	bool loop_flag;				// アニメーションのループ
	bool pause_flag;			// アニメーションの停止
	AnimationState result;		// 最後の状態
public:
	// <スプライトアニメーション作成>
	GameSpriteAnimation(GameTexture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

	// <スプライトアニメーションなし>
	GameSpriteAnimation();

	virtual ~GameSpriteAnimation() {};

	// <スプライトアニメーション更新>
	AnimationState Update();
};

// <ゲームオブジェクト>
class GameObject
{
public:
	// <デバッグ用当たり判定表示>
	static bool DEBUG_HITBOX;
public:
	Vec2 pos;					// <位置>
	Vec2 vel;					// <速度>
	Vec2 size;					// <大きさ>
	ShapeType shape;				// <形>
	GameSprite sprite;			// <スプライト>
	bool fill;					// <塗りつぶし>
	float edge;					// <縁>
	Connection sprite_connection;	// <スプライトのつながり>
	bool alive;					// <表示状態>
	int state;					// <状態>
	int type;					// <タイプ>
	Timer count;				// <カウンタ>
public:
	// <オブジェクト作成>
	GameObject(Vec2 pos = {}, Vec2 vel = {}, Vec2 size = {});

	virtual ~GameObject() {};

	// <線オブジェクト作成>
	static GameObject CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel = {});

	// <オブジェクト削除>
	void Dispose();

	// <オブジェクト確認>
	bool IsAlive();

	// <オブジェクト座標更新>
	void UpdatePosition();

	// <枠取得>
	Dimension GetCollision();

	// <オブジェクト描画>
	void Render(const Vec2* translate = &Vec2{});

	// <弾オブジェクトサイズ変更>
	void SetSize(float scale, float size = 10);
};

class Field : GameObject
{
public:
	// <フィールドオブジェクト作成>
	Field(void);

	virtual ~Field() {};
};

// <オブジェクト作成>
void GameTick_Update(void);

#endif