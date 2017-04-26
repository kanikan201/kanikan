#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "fade/Fade.h"
#include "SceneManager.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	DeleteGO(bgm);
}
bool ResultScene::Start()
{
	texture.Load("Assets/sprite/result.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	bgm = NewGO<CSoundSource>(0);
	bgm->Init("Assets/sound/Result.wav");
	bgm->Play(true);

	//�t�F�[�h�C��
	g_fade->StartFadeIn();
	return true;
}
void ResultScene::Update()
{
	//�V�[�����؂�ւ�����玩�g���폜
	if (sceneManager->GetScene() != SceneManager::stateResult) {
		DeleteGO(this);
	}
}
void ResultScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}