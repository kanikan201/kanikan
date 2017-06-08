#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"
#include "ClearScene.h"

GameScene* g_gameScene = NULL;

//ステージ1の配置情報
SMapInfo Stage1[] = {
#include "locationInfo/stage1.h"
};
//ステージ2の配置情報
SMapInfo Stage2[] = {
#include "locationInfo/stage2.h"
};

SMapInfo Stage3[] = {
#include "locationInfo/stage3.h"
};

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	if (step == step_WaitFadeOut) {
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

		player = NewGO<Player>(0);		//プレイヤー生成
		camera = NewGO<Camera>(0);		//カメラ生成
		//ivt = NewGO<inventory>(0);		//インベントリ生成
		time = NewGO<DisplayTime>(0);	//タイム表示生成
		route = NewGO<RouteJudge>(0);

		bgmSource = NULL;
		CreateStage(currentStage);

		step = step_StageLoad;
		isDelete = false;
		isClear = false;

		return false;
	}
	else {
		step = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}
	return true;
}

void GameScene::Update()
{
	switch (step) {

	//ステージの読み込みが終わった
	case step_StageLoad:
		g_fade->StartFadeIn();
		step = step_WaitFadeIn;
		break;

	//フェードアウト時
	case step_WaitFadeIn:
		//フェードが終わった
		if (!g_fade->IsExecute()) {
			step = step_nomal;
		}
		break;

	//通常時
	case step_nomal:
		//クリアした
		if (isClear == true) {
			if (timer == 0.0f) {
				DeleteGO(bgmSource);
				bgmSource = nullptr;
				//クリアボイス(仮)
				CSoundSource* SE = NewGO<CSoundSource>(0);
				SE->Init("Assets/sound/V0024.wav");
				SE->Play(false);
				NewGO<ClearScene>(0);
			}
			//2秒待ってから遷移
			else if (timer > 2.0f) {
				if (nextStage == en_end) {
					//最後のステージをクリアした
					step = step_GameClear;
				}
				else{
					g_fade->StartFadeOut();
					step = step_WaitFadeOut;
					//route->Reset(3, 7);	//テスト用(あとで変更)
				}
				totalTime += gameTime;
				timer = 0.0f;
				return;
			}
			timer += GameTime().GetFrameDeltaTime();
		}
		else {
			gameTime += GameTime().GetFrameDeltaTime();	//プレイ時間カウント
		}
		break;
	//フェードアウト時
	case step_WaitFadeOut:
		//オブジェクトを削除した
		if (isDelete == true) {
			//ステージの切り替え
			CreateStage(nextStage);
			isDelete = false;
		}
		//フェードが終わった
		else if (!g_fade->IsExecute()) {
			Reset();
			setClear(false);
			//オブジェクトを削除
			isDelete = true;
		}
		break;
	case step_WaitGameOver:
		if (!GameOverSE.IsPlaying()) {
			step = step_GameOver;
			gameOver = NewGO<GameOverScene>(0);

		}
		break;
	//ゲームオーバーの時
	case step_GameOver:
		if (gameOver->GetChoice()) {
			//続けるを選択
			if (gameOver->GetState()== GameOverScene::enContinue) {
				//bgmSource->Play(true);
				g_fade->StartFadeOut();
				step = step_WaitFadeOut;
				nextStage = currentStage;
				//Reset();
			}
			//やめるを選択
			else if (gameOver->GetState()== GameOverScene::enEnd) {
				step = step_GameEnd;
			}
		}

		break;
	}
}

void GameScene::CreateStage(state_stage stage)
{
	int numObject;
	currentStage = stage;
	switch (stage) {
	case en_Stage1:
		route->Init(3, 7);
		route->Reset(3, 7);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);

		camera->Init(2);

		nextStage = en_Stage2;
		//nextStage = en_end;	//こっちはテスト用
		step = step_StageLoad;

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);
		break;
	case en_Stage2:
		route->Init(1, 5);
		route->Reset(1, 5);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);

		camera->Init(3);

		nextStage = en_Stage3;
		step = step_StageLoad;

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/GameBGM.wav");
		bgmSource->Play(true);
		break;
	case en_Stage3:
		route->Init(5, 8);
		route->Reset(5, 8);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage3) / sizeof(Stage3[0]);
		map->Create(Stage3, numObject);

		camera->Init(4);

		nextStage = en_end;
		step = step_StageLoad;

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/GameBGM.wav");
		bgmSource->Play(true);
		break;
	}
	step = step_StageLoad;
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
	time->DeleteNum();
	DeleteGO(time);
	DeleteGO(bgmSource);
	bgmSource = nullptr;
	DeleteGO(route);
}

//ゲームオーバーへ切り替え
void GameScene::SetGameOver() {
	DeleteGO(bgmSource);
	bgmSource = nullptr;
	AddGO(0, &GameOverSE);
	GameOverSE.Init("Assets/sound/jingle.wav");
	GameOverSE.Play(false);
	step = step_WaitGameOver;
	route->Reset(route->GetinitialGrid_x(), route->GetinitialGrid_y());
}

//リセット
void GameScene::Reset() {
	player->Reset();
	gameTime = 0.0f;
	camera->Reset();
}