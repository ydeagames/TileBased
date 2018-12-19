#pragma once
#include "Color.h"

// �O���t�B�b�N�n���h��   
using HGRP = int;
// �T�E���h�n���h��
using HSND = int;
// �t�H���g�n���h��
using HFNT = int;
// �l�b�g���[�N�n���h�� 
using HNET = int;

// �X�N���[���J�n
#define screen_start(screen) \
{ \
	HGRP screen_stack = GetDrawScreen(); \
	SetDrawScreen(screen); \
	{
// �X�N���[���I��
#define screen_end \
	} \
	SetDrawScreen(screen_stack); \
}

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