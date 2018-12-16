#pragma once

#ifdef GOBJ

/*

// <�A�j���[�V�����̌���>
enum class AnimationState
{
	RUNNING,					// �A�j���[�V���������s���̏��
	FINISHED,					// �A�j���[�V�����Đ��������������
	IDLE,						// �A�j���[�V�������Ă��Ȃ����
};

// <�e�N�X�`��>
class Texture final
{
public:
	static constexpr int TEXTURE_MISSING = -1;		// �e�N�X�`����������܂���
	static constexpr int TEXTURE_NONE = -2;			// �e�N�X�`���Ȃ�

public:
	HGRP texture;				// <�e�N�X�`��>
	Vector2 anchor;				// <�e�N�X�`����_>
	Vector2 size;					// <�e�N�X�`���T�C�Y>
	Vector2 pivot;					// <�e�N�X�`�����S>

public:
	// <�e�N�X�`���쐬>
	Texture(HGRP texture, const Vector2& anchor, const Vector2& size, const Vector2& pivot = Vector2{ .5f, .5f });

	// <�e�N�X�`���쐬>
	Texture(HGRP texture);

	// <�e�N�X�`���Ȃ�>
	Texture();
};

class Transform final
{
public:
	Vector2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	float scale;				// <�X�P�[��>

public:
	Transform(const Vector2& position, float rotation, float scale);

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
	Texture texture;		
	Transform transform;

public:
	TextureSprite(const Texture& texture, const Transform& transform);

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
	Texture texture;		// <�e�N�X�`��>
	Vector2 size;					// <�T�C�Y>
	int num_columns;			// <1�s������̃t���[����>
	int frame_index;			// <���݂̃t���[���̃C���f�b�N�X>
	Vector2 offset;				// <�I�t�Z�b�g>
	float scale;				// <�X�P�[��>
	float angle;				// <��]>
public:
	GameSprite(Texture texture, float scale = 1, float angle = 0);

	// <�X�v���C�g�Ȃ�>
	GameSprite();

	virtual ~GameSprite() {};

	// <�X�v���C�g�X�V>
	void SetFrame(int frame);

	// <�X�v���C�g�`��>
	void Render(const Vector2* pos);
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
	GameSpriteAnimation(Texture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

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
	Vector2 pos;					// <�ʒu>
	Vector2 vel;					// <���x>
	Vector2 size;					// <�傫��>
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
	GameObject(Vector2 pos = {}, Vector2 vel = {}, Vector2 size = {});

	virtual ~GameObject() {};

	// <���I�u�W�F�N�g�쐬>
	static GameObject CreateLine(Vector2 pos1, Vector2 pos2, Vector2 vel = {});

	// <�I�u�W�F�N�g�폜>
	void Dispose();

	// <�I�u�W�F�N�g�m�F>
	bool IsAlive();

	// <�I�u�W�F�N�g���W�X�V>
	void UpdatePosition();

	// <�g�擾>
	Dimension GetCollision();

	// <�I�u�W�F�N�g�`��>
	void Render(const Vector2* translate = &Vector2{});

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

/**/
#endif