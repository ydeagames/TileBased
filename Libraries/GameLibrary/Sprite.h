#pragma once

class Sprite
{
public:
	Texture texture;
	Transform transform;

public:
	Sprite(const Texture& texture, const Transform& transform);

	virtual ~Sprite() = default;

	// <�X�v���C�g�`��>
	void Render(const Transform& tranform);
};
