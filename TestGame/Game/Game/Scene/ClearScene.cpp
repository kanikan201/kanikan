#include "stdafx.h"
#include "ClearScene.h"
#include "GameScene.h"

namespace {
	const CVector2 Size = { 420.0f, 160.0f };
	const CVector2 Pos = { 0.0f,100.0f };
}

ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}

bool ClearScene::Start() 
{
	texture.Load("Assets/sprite/test.png");
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