#pragma once

#ifdef GOBJ

/*

// <アニメーションの結果>
enum class AnimationState
{
	RUNNING,					// アニメーションが実行中の状態
	FINISHED,					// アニメーション再生が完了した状態
	IDLE,						// アニメーションしていない状態
};

// <テクスチャ>
class Texture final
{
public:
	static constexpr int TEXTURE_MISSING = -1;		// テクスチャが見つかりません
	static constexpr int TEXTURE_NONE = -2;			// テクスチャなし

public:
	HGRP texture;				// <テクスチャ>
	Vector2 anchor;				// <テクスチャ基点>
	Vector2 size;					// <テクスチャサイズ>
	Vector2 pivot;					// <テクスチャ中心>

public:
	// <テクスチャ作成>
	Texture(HGRP texture, const Vector2& anchor, const Vector2& size, const Vector2& pivot = Vector2{ .5f, .5f });

	// <テクスチャ作成>
	Texture(HGRP texture);

	// <テクスチャなし>
	Texture();
};

class Transform final
{
public:
	Vector2 position;				// <テクスチャ>
	float rotation;				// <回転>
	float scale;				// <スケール>

public:
	Transform(const Vector2& position, float rotation, float scale);

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
	Texture texture;		
	Transform transform;

public:
	TextureSprite(const Texture& texture, const Transform& transform);

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
	Texture texture;		// <テクスチャ>
	Vector2 size;					// <サイズ>
	int num_columns;			// <1行あたりのフレーム数>
	int frame_index;			// <現在のフレームのインデックス>
	Vector2 offset;				// <オフセット>
	float scale;				// <スケール>
	float angle;				// <回転>
public:
	GameSprite(Texture texture, float scale = 1, float angle = 0);

	// <スプライトなし>
	GameSprite();

	virtual ~GameSprite() {};

	// <スプライト更新>
	void SetFrame(int frame);

	// <スプライト描画>
	void Render(const Vector2* pos);
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
	GameSpriteAnimation(Texture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

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
	Vector2 pos;					// <位置>
	Vector2 vel;					// <速度>
	Vector2 size;					// <大きさ>
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
	GameObject(Vector2 pos = {}, Vector2 vel = {}, Vector2 size = {});

	virtual ~GameObject() {};

	// <線オブジェクト作成>
	static GameObject CreateLine(Vector2 pos1, Vector2 pos2, Vector2 vel = {});

	// <オブジェクト削除>
	void Dispose();

	// <オブジェクト確認>
	bool IsAlive();

	// <オブジェクト座標更新>
	void UpdatePosition();

	// <枠取得>
	Dimension GetCollision();

	// <オブジェクト描画>
	void Render(const Vector2* translate = &Vector2{});

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

/**/
#endif