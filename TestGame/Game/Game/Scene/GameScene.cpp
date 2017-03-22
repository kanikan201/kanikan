#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

//マップの配置情報
SMapInfo Stage[] = {
#include "locationInfo.h"
};

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	//ライトを初期化
	light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	light.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	light.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });

	//light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	//light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

	map		= NewGO<Map>(0);		//マップ生成
	int numObject;
	//マップに配置されているオブジェクト数を計算
	numObject = sizeof(Stage) / sizeof(Stage[0]);
	map->Create(Stage, numObject);
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