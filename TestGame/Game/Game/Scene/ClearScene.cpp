#include "stdafx.h"
#include "ClearScene.h"
#include "GameScene.h"

namespace {
	const CVector2 Size = { 400.0f, 225.0f };
	const CVector2 Pos = { 0.0f,0.0f };
}

ClearScene::ClearScene()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/clearBGM.wav");
	bgmSource->Play(false);
}


ClearScene::~ClearScene()
{
	DeleteGO(bgmSource);

}

bool ClearScene::Start()
{
	texture.Load("Assets/sprite/clear.png");
	sprite.Init(&texture);
	sprite.SetSize(Size);
	sprite.SetPosition(Pos);

	return true;
}

void ClearScene::Update() {
	if ((g_gameScene == nullptr) || !g_gameScene->GetClear()) {
		DeleteGO(this);
	}

}

void ClearScene::PostRender(CRenderContext& renderContext) {
	sprite.Draw(renderContext);
}