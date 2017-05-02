#include "stdafx.h"
#include "GameOverScene.h"
#include "Fade\Fade.h"
#include "Scene\GameScene.h"
#include "Scene\ResultScene.h"
#include "Scene\SceneManager.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}

GameOverScene::GameOverScene()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/GameOverBGM.wav");
	bgmSource->Play(true);
}

GameOverScene::~GameOverScene()
{
	DeleteGO(bgmSource);
}

bool GameOverScene::Start()
{
	texture.Load("Assets/sprite/GameOver.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	//�t�F�[�h�C��
	g_fade->StartFadeIn();
	return true;
}

void GameOverScene::Update()
{
	//�V�[�����؂�ւ�����玩�g���폜
	//if (sceneManager->GetScene() != SceneManager::stateGameOver) {
	//	DeleteGO(this);
	//}
	if ((g_gameScene == nullptr) ||g_gameScene->isStep()!= GameScene::step_GameOver) {
		DeleteGO(this);
	}
}
void GameOverScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}