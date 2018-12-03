#pragma once

// �O���t�B�b�N�n���h��   
using HGRP = int;
// �T�E���h�n���h��
using HSND = int;
// �t�H���g�n���h��
using HFNT = int;
// �l�b�g���[�N�n���h�� 
using HNET = int;

// <�F�R�[�h>
using Color = unsigned int;

// <�F�R�[�h(�W���J���[16�F)>
namespace Colors
{
	enum : Color
	{
		Black = 0xff000000,		// ���F
		Navy = 0xff000080,		// �Z���F
		Green = 0xff008000,		// �ΐF
		Teal = 0xff008080,		// �ΐF
		Maroon = 0xff800000,	// �}���[���F
		Purple = 0xff800080,	// ���F
		Olive = 0xff808000,		// �I���[�u�F
		Gray = 0xff808080,		// �D�F
		Silver = 0xffc0c0c0,	// ��F
		Blue = 0xff0000ff,		// �F
		Lime = 0xff00ff00,		// ���C���O���[���F
		Aqua = 0xff00ffff,		// ���F
		Red = 0xffff0000,		// �ԐF
		Fuchsia = 0xffff00ff,	// �Ԏ��F
		Yellow = 0xffffff00,	// ���F
		White = 0xffffffff,		// ���F
	};
};

// <�}�`�`��֘A>
namespace DrawUtils
{
	// �j����`��
	int DrawDashedLine(int x1, int y1, int x2, int y2, Color color, int length, int thickness = 1);

	// �j����`��(�A���`�G�C���A�X���ʕt��)
	int DrawDashedLineAA(float x1, float y1, float x2, float y2, Color color, float length, float thickness = 1.0f);

	// �J�v�Z����`��
	int DrawCapsule(int x1, int y1, int x2, int y2, int r, Color color, int thickness = 1);

	// �J�v�Z����`��(�A���`�G�C���A�X���ʕt��)
	int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, Color color, float thickness = 1.0f);
}