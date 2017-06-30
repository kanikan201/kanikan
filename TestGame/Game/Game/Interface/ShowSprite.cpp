#include "stdafx.h"
#include "ShowSprite.h"
#include "scene/GameScene.h"


namespace {
	const CVector2 SSize = { 535.0f, 104.f };
	const CVector2 SPos = { 0.0f, 160.0f };
}

ShowSprite::ShowSprite()
{
}


ShowSprite::~ShowSprite()
{
}

bool ShowSprite::Start()
{
	switch (g_gameScene->GetStage()) {
	case en_Stage1:
		//”wŒi
		texture.Load("Assets/sprite/stage/stage1.png");
		break;

	case en_Stage2:
		//texture.Load("Assets/sprite/stage/stage2.png");
		texture.Load("Assets/sprite/stage/stage3_ex.png");
		break;

	case en_Stage3:
		//texture.Load("Assets/sprite/stage/stage3.png");
		texture.Load("Assets/sprite/stage/stage2_ex.png");
		break;
	}
	sprite.Init(&texture);
	sprite.SetSize(SSize);
	sprite.SetPivot({ 0.5f, 0.5f });		//ƒsƒ{ƒbƒg‚Í’†‰›
	sprite.SetPosition(SPos);
	return true;
}

void ShowSprite::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	if (timer > 2.0f) {
		DeleteGO(this);
	}

}
void ShowSprite::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}
