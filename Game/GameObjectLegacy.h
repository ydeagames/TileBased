#pragma once

#ifdef GOBJ

// <�A�j���[�V�����̌���>
enum class AnimationState
{
	RUNNING,					// �A�j���[�V���������s���̏��
	FINISHED,					// �A�j���[�V�����Đ��������������
	IDLE,						// �A�j���[�V�������Ă��Ȃ����
};

// <�e�N�X�`��>
class GameTexture final
{
public:
	static constexpr int TEXTURE_MISSING = -1;		// �e�N�X�`����������܂���
	static constexpr int TEXTURE_NONE = -2;			// �e�N�X�`���Ȃ�

public:
	HGRP texture;				// <�e�N�X�`��>
	Vec2 anchor;				// <�e�N�X�`����_>
	Vec2 size;					// <�e�N�X�`���T�C�Y>
	Vec2 pivot;					// <�e�N�X�`�����S>

public:
	// <�e�N�X�`���쐬>
	GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot = Vec2{ .5f, .5f });

	// <�e�N�X�`���쐬>
	GameTexture(HGRP texture);

	// <�e�N�X�`���Ȃ�>
	GameTexture();
};

class Transform final
{
public:
	Vec2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	float scale;				// <�X�P�[��>

public:
	Transform(const Vec2& position, float rotation, float scale);

	Transform();
};

class Sprite
{
public:
	virtual ~Sprite() {}

	// <�X�v���C�g�`��>
	virtual void Render(const Transform& tranform) = 0;
};

class TextureSprite : public Sprite
{
public:
	GameTexture texture;		
	Transform transform;

public:
	TextureSprite(const GameTexture& texture, const Transform& transform);

	// <�X�v���C�g�Ȃ�>
	TextureSprite();

	virtual ~TextureSprite() {}

	// <�X�v���C�g�`��>
	void Render(const Transform& tranform) override;
};

class ClippingSprite : public Sprite
{

};

// <�X�v���C�g�I�u�W�F�N�g>
class GameSprite
{
public:
	Color color;			// <�F>
	GameTexture texture;		// <�e�N�X�`��>
	Vec2 size;					// <�T�C�Y>
	int num_columns;			// <1�s������̃t���[����>
	int frame_index;			// <���݂̃t���[���̃C���f�b�N�X>
	Vec2 offset;				// <�I�t�Z�b�g>
	float scale;				// <�X�P�[��>
	float angle;				// <��]>
public:
	GameSprite(GameTexture texture, float scale = 1, float angle = 0);

	// <�X�v���C�g�Ȃ�>
	GameSprite();

	virtual ~GameSprite() {};

	// <�X�v���C�g�X�V>
	void SetFrame(int frame);

	// <�X�v���C�g�`��>
	void Render(const Vec2* pos);
};

// <�X�v���C�g�A�j���[�V����>
class GameSpriteAnimation : public GameSprite
{
public:
	int frame_start;			// �J�n�t���[���̃C���f�b�N�X
	int frame_end;				// �I���t���[���̃C���f�b�N�X
	int frame_duration;			// �t���[���Ԋu
	int elapsed_time;			// ���݂̃t���[���̌o�ߎ���
	bool loop_flag;				// �A�j���[�V�����̃��[�v
	bool pause_flag;			// �A�j���[�V�����̒�~
	AnimationState result;		// �Ō�̏��
public:
	// <�X�v���C�g�A�j���[�V�����쐬>
	GameSpriteAnimation(GameTexture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

	// <�X�v���C�g�A�j���[�V�����Ȃ�>
	GameSpriteAnimation();

	virtual ~GameSpriteAnimation() {};

	// <�X�v���C�g�A�j���[�V�����X�V>
	AnimationState Update();
};

// <�Q�[���I�u�W�F�N�g>
class GameObject
{
public:
	// <�f�o�b�O�p�����蔻��\��>
	static bool DEBUG_HITBOX;
public:
	Vec2 pos;					// <�ʒu>
	Vec2 vel;					// <���x>
	Vec2 size;					// <�傫��>
	ShapeType shape;				// <�`>
	GameSprite sprite;			// <�X�v���C�g>
	bool fill;					// <�h��Ԃ�>
	float edge;					// <��>
	Connection sprite_connection;	// <�X�v���C�g�̂Ȃ���>
	bool alive;					// <�\�����>
	int state;					// <���>
	int type;					// <�^�C�v>
	Timer count;				// <�J�E���^>
public:
	// <�I�u�W�F�N�g�쐬>
	GameObject(Vec2 pos = {}, Vec2 vel = {}, Vec2 size = {});

	virtual ~GameObject() {};

	// <���I�u�W�F�N�g�쐬>
	static GameObject CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel = {});

	// <�I�u�W�F�N�g�폜>
	void Dispose();

	// <�I�u�W�F�N�g�m�F>
	bool IsAlive();

	// <�I�u�W�F�N�g���W�X�V>
	void UpdatePosition();

	// <�g�擾>
	Dimension GetCollision();

	// <�I�u�W�F�N�g�`��>
	void Render(const Vec2* translate = &Vec2{});

	// <�e�I�u�W�F�N�g�T�C�Y�ύX>
	void SetSize(float scale, float size = 10);
};

class Field : GameObject
{
public:
	// <�t�B�[���h�I�u�W�F�N�g�쐬>
	Field(void);

	virtual ~Field() {};
};

// <�I�u�W�F�N�g�쐬>
void GameTick_Update(void);

#endif