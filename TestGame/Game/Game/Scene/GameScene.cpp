#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{
	DeleteGO(bgmSource);
}

bool GameScene::Start()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/GameBGM.wav");
	bgmSource->Play(true);

	//ライトを初期化。
	light.SetAmbinetLight(CVector3::One);

	map=NewGO<Map>(0);
	player=NewGO<Player>(0);
	camera = NewGO<Camera>(0);

	return true;
}

void GameScene::Update()
{

	if (Pad(0).IsTrigger(enButtonStart)) {
		//タイトル画面に遷移する。
		NewGO<ResultScene>(0);
		DeleteGO(camera);
		DeleteGO(player);
		DeleteGO(map);
		DeleteGO(this);
		return;
	}
	
}
/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext)
{

}