#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "fade/Fade.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{

}
bool TitleScene::Start()
{
	texture.Load("Assets/sprite/title.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	g_fade->StartFadeIn();

	return true;
}
void TitleScene::Update()
{
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}