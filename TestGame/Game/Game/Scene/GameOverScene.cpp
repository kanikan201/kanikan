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
	CSoundSource* bgmSource = NULL;
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/GameOverBGM2.wav");
	bgmSource->Play(true);
}

GameOverScene::~GameOverScene()
{
	DeleteGO(bgmsource);
}

bool GameOverScene::Start()
{
	texture.Load("Assets/sprite/GameOver.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	//フェードイン
	g_fade->StartFadeIn();
	return true;
}

void GameOverScene::Update()
{
	//シーンが切り替わったら自身を削除
	if (sceneManager->GetScene() != SceneManager::stateGameOver) {
		DeleteGO(this);
	}
}
void GameOverScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}