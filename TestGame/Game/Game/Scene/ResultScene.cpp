#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	DeleteGO(bgmSource);
}
bool ResultScene::Start()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/TitleBGM.wav");
	bgmSource->Play(true);

	texture.Load("Assets/sprite/result.png");
	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);
	return true;
}
void ResultScene::Update()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		NewGO<TitleScene>(0);
		//é©ï™ÇçÌèúÅB
		DeleteGO(this);
	}
}
void ResultScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}