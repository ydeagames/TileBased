#include "GameGlobal.h"

GameGlobal::GameGlobal()
	: titlefont(std::make_shared<FontResource>("logotypejp_mp_b_1.1.ttf", "�R�[�|���[�g�E���S�a", 72, 0, DX_FONTTYPE_ANTIALIASING_4X4, -1, 12))
	, font(std::make_shared<FontResource>("logotypejp_mp_b_1.1.ttf", "�R�[�|���[�g�E���S�a", 32, 0, DX_FONTTYPE_ANTIALIASING_4X4))
{
}

GameGlobal::~GameGlobal()
{
}
