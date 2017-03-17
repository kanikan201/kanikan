#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	//ライトを初期化
	light.SetAmbinetLight(CVector3::One);

	map		= NewGO<Map>(0);		//マップ生成
	player	= NewGO<Player>(0);		//プレイヤー生成
	camera	= NewGO<Camera>(0);		//カメラ生成

	g_fade->StartFadeIn();
	return true;
}

void GameScene::Update()
{

}
/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext)
{

}

//生成したものを解放する
void GameScene::Release() {
	DeleteGO(camera);	//カメラ
	DeleteGO(player);	//プレイヤー
	DeleteGO(map);		//マップ
}