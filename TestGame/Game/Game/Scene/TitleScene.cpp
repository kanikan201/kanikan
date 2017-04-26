#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "fade/Fade.h"
#include "SceneManager.h"

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

	bgm = NewGO<CSoundSource>(0);
	bgm->Init("Assets/sound/Title.wav");
	bgm->Play(true);

	g_fade->StartFadeIn();

	return true;
}
void TitleScene::Update()
{
	//シーンが切り替わったら自身を削除
	if (sceneManager->GetScene() != SceneManager::stateTitel) {
		DeleteGO(this);
	}

	if (Pad(0).IsTrigger(enButtonStart)) {
		DeleteGO(bgm);
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init("Assets/sound/Decision.wav");
		se->Play(false);
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}