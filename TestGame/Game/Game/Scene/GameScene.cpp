#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

//ステージ1の配置情報
SMapInfo Stage1[] = {
#include "locationInfo/stage1.h"
};
//ステージ2の配置情報
SMapInfo Stage2[] = {
#include "locationInfo/stage2.h"
};

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	if (fadeStep == step_WaitFadeOut) {
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

		map = NewGO<Map>(0);		//マップ生成

		//マップに配置されているオブジェクト数を計算
		int numObject;
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);

		player = NewGO<Player>(0);		//プレイヤー生成
		camera = NewGO<Camera>(0);		//カメラ生成
		ivt = NewGO<inventory>(0);		//インベントリ生成
		time = NewGO<DisplayTime>(0);	//タイム表示生成

		bgmSource = NULL;
		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);

		fadeStep = step_StageLoad;
		isDelete = false;
		isClear = false;

		return false;
	}
	else {
		fadeStep = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}
	return true;
}

void GameScene::Update()
{

	switch (fadeStep) {

	//ステージの読み込みが終わった
	case step_StageLoad:
		g_fade->StartFadeIn();
		fadeStep = step_WaitFadeIn;
		break;

	//フェードアウト時
	case step_WaitFadeIn:
		//フェードが終わった
		if (!g_fade->IsExecute()) {
			fadeStep = step_nomal;
		}
		break;

	//通常時
	case step_nomal:
		//クリアした
		if (isClear == true) {
			g_fade->StartFadeOut();
			fadeStep = step_WaitFadeOut;
			totalTime += gameTime;
		}
		else {
			gameTime += GameTime().GetFrameDeltaTime();	//プレイ時間カウント
		}
		break;
	//フェードアウト時
	case step_WaitFadeOut:
		//オブジェクトを削除した
		if (isDelete == true) {
			ChangeStage();
			isDelete = false;
			fadeStep = step_StageLoad;
		}
		//フェードが終わった
		else if (!g_fade->IsExecute()) {
			player->SetPosition({ 0.0f, 0.0f, 0.0f });
			setClear(false);
			gameTime = 0.0f;
			//オブジェクトを削除
			isDelete = true;
		}
		break;
	}
}

void GameScene::ChangeStage()
{
	int numObject;
	switch (currentStage) {
	case en_Stage1:
		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		currentStage = en_Stage2;
		break;
	case en_Stage2:
		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		currentStage = en_Stage2;
		break;
	}
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
	DeleteGO(ivt);
	DeleteGO(time);
	DeleteGO(bgmSource);
}