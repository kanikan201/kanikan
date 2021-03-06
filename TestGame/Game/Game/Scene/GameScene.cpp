#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"
#include "ClearScene.h"
#include "Interface/ShowSprite.h"

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

namespace {
	const CVector2 Size = { 300.0f, 160.0f };
	const CVector2 Pos = { 0.0f,100.0f };
}

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

		//ライトを初期化
		PanelLight.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
		PanelLight.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
		PanelLight.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
		PanelLight.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

		PanelLight.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
		PanelLight.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
		PanelLight.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
		PanelLight.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });

		background	= NewGO<BackGround>(0);//背景
		map			= NewGO<Map>(0);		//マップ生成
		camera		= NewGO<Camera>(0);		//カメラ生成
		route		= NewGO<RouteJudge>(0);

		bgmSource = NULL;
		CreateStage(currentStage);

		player		= NewGO<Player>(0);		//プレイヤー生成
		ivt			= NewGO<inventory>(0);		//インベントリ生成
		time		= NewGO<DisplayTime>(0);	//タイム表示生成
		

		step		= step_StageLoad;
		isDelete	= false;
		isClear		= false;

		/*テスト?*/
		texture.Load("Assets/sprite/test2.png");
		sprite.Init(&texture);
		sprite.SetSize(Size);
		sprite.SetPosition(Pos);

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

			//スタート時のスプライト表示
			NewGO<ShowSprite>(0);
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
			//3秒待ってから遷移
			else if (timer > 3.0f) {
				//最後のステージをクリアした
				if (nextStage == en_end) {
					step = step_GameClear;
				}
				else{
					g_fade->StartFadeOut();
					step = step_WaitFadeOut;
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
			ivt->Reset();
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
	//ゲームオーバー待ち
	case step_WaitGameOver:
		timer += GameTime().GetFrameDeltaTime();
		if (!isMiss && timer > 1.7f) {
			isMiss = true;
		}
		//SEが終わった
		if (!GameOverSE.IsPlaying()) {
			step = step_GameOver;
			gameOver = NewGO<GameOverScene>(0);
			timer = 0.0f;
			isMiss = false;
		}
		break;
	//ゲームオーバーの時
	case step_GameOver:
		if (gameOver->GetChoice()) {
			//続けるを選択
			if (gameOver->GetState()== GameOverScene::enContinue) {
				g_fade->StartFadeOut();
				step = step_WaitFadeOut;
				nextStage = currentStage;
				totalTime += gameTime;
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
	CVector3 ambientLight;
	int numObject;
	currentStage = stage;

	switch (stage) {
	case en_Stage1:
		route->Init(1, 5);
		camera->Init(2);

		//パネルのライト設定
		ambientLight = { 0.0f, 0.30f , 0.42f };
		ambientLight.Scale(2.8f);
		PanelLight.SetAmbinetLight(ambientLight);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);

		//nextStage = en_Stage2;
		nextStage = en_Stage3;	//ステージ2と3を入れ替え(仮)

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);
		break;
	case en_Stage2:
		route->Init(5, 8);
		camera->Init(3);

		//パネルのライト設定
		ambientLight = { 0.40f, 0.0f , 0.10f };
		ambientLight.Scale(2.8f);
		PanelLight.SetAmbinetLight(ambientLight);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);

		//nextStage = en_Stage3;
		nextStage = en_end;		//ステージ2と3を入れ替え(仮)

		bgmSource = NewGO<CSoundSource>(0);

		//仮BGM
		bgmSource->Init("Assets/sound/tw022.wav");
		bgmSource->Play(true);
		break;
	case en_Stage3:
		route->Init(2, 5);
		camera->Init(4);

		//パネルのライト設定
		ambientLight = { 0.01f, 0.35f , 0.0f };
		ambientLight.Scale(2.8f);
		PanelLight.SetAmbinetLight(ambientLight);

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage3) / sizeof(Stage3[0]);
		map->Create(Stage3, numObject);

		//nextStage = en_end;
		nextStage = en_Stage2;	//ステージ2と3を入れ替え(仮)

		bgmSource = NewGO<CSoundSource>(0);

		//仮BGM
		bgmSource->Init("Assets/sound/tw081.wav");
		bgmSource->Play(true);
		break;
	}
	step = step_StageLoad;

	route->Reset(route->GetInitialGrid_x(), route->GetInitialGrid_y());
}
/*!
*@brief	描画関数。
*/
void GameScene::PostRender(CRenderContext& renderContext)
{
	if (isMiss) {
		sprite.Draw(renderContext);
	}
}

//生成したものを解放する
void GameScene::Release() {
	DeleteGO(camera);	//カメラ
	DeleteGO(player);	//プレイヤー
	DeleteGO(background);//背景
	DeleteGO(map);		//マップ
	ivt->Delete();
	DeleteGO(ivt);
	time->DeleteNum();
	DeleteGO(time);
	DeleteGO(bgmSource);
	DeleteGO(route);
}

//ゲームオーバーへ切り替え
void GameScene::SetGameOver() {
	getPlayer()->ScaleReset(2.5f);
	DeleteGO(bgmSource);
	bgmSource = nullptr;
	AddGO(0, &GameOverSE);
	GameOverSE.Init("Assets/sound/jingle.wav");
	GameOverSE.Play(false);
	step = step_WaitGameOver;
	timer = 0.0f;

	route->SetResetEnd(false);
	route->SetThroughFlg(false);
	player->SetSoundflg(false);
	player->SetSound2flg(false);

	//パネルのライトを暗くする
	CVector3 ambientLight;
	switch (currentStage) {
	case en_Stage1:
		ambientLight = { 0.0f, 0.20f , 0.20f };
		break;

	case en_Stage2:
		ambientLight = { 0.20f, 0.0f , 0.10f };
		break;

	case en_Stage3:
		ambientLight = { 0.03f, 0.20f , 0.0f };
		break;
	}
	ambientLight.Scale(2.8f);
	PanelLight.SetAmbinetLight(ambientLight);
}

//リセット
void GameScene::Reset() {
	player->Reset();
	gameTime = 0.0f;
	camera->Reset();
}

void GameScene::PanelLightReset()
{
	//パネルのライトを暗くする
	CVector3 ambientLight;
	switch (currentStage) {
	case en_Stage1:
		ambientLight = { 0.0f, 0.30f , 0.42f };
		break;

	case en_Stage2:
		ambientLight = { 0.40f, 0.0f , 0.10f };
		break;

	case en_Stage3:
		ambientLight = { 0.01f, 0.35f , 0.0f };
		break;
	}
	ambientLight.Scale(2.8f);
	PanelLight.SetAmbinetLight(ambientLight);
}