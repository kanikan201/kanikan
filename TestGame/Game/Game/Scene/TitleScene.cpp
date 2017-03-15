#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	DeleteGO(bgmSource);
}
bool TitleScene::Start()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/TitleBGM.wav");
	bgmSource->Play(true);

	texture.Load("Assets/sprite/title.png");
	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);
	return true;
}
void TitleScene::Update()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		g_gameScene = NewGO<GameScene>(0);
		//é©ï™ÇçÌèúÅB
		DeleteGO(this);
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}