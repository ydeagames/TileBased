#include "GameGlobal.h"

GameGlobal::GameGlobal()
	: titlefont(std::make_shared<FontResource>("logotypejp_mp_b_1.1.ttf", "コーポレート・ロゴＢ", 72, 0, DX_FONTTYPE_ANTIALIASING_4X4, -1, 12))
	, font(std::make_shared<FontResource>("logotypejp_mp_b_1.1.ttf", "コーポレート・ロゴＢ", 32, 0, DX_FONTTYPE_ANTIALIASING_4X4))
	, movie(std::make_shared<TextureResource>(MovieResource::MOVIE_DIR, "ydeagames.mp4"))
	, icon(std::make_shared<TextureResource>("icon.png"))
	, background(std::make_shared<TextureResource>("background.jpg"))
	, bgm01(std::make_shared<AudioResource>("bgm_maoudamashii_cyber41.mp3"))
	, se01(std::make_shared<AudioResource>("se_maoudamashii_system44.mp3"))
	, se02(std::make_shared<AudioResource>("se_maoudamashii_explosion05.mp3"))
	, se03(std::make_shared<AudioResource>("se_maoudamashii_system42.mp3"))
{
	PlaySoundMem(bgm01->GetResource(), DX_PLAYTYPE_LOOP);
}

GameGlobal::~GameGlobal()
{
}
