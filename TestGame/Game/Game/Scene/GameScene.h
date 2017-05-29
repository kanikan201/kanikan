/*
	ゲームシーン関数
*/

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera/Camera.h"
#include "Map/Map.h"
#include "Interface/inventory.h"
#include "Interface/DisplayTime.h"
#include "Route/RouteJudge.h"
#include "GameOverScene.h"

class GameScene :
	public IGameObject
{
public:

	GameScene();

	~GameScene();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext);

	void Release();		//解放
	void SetGameOver();	//ゲームオーバーをセット
	void Reset();

	//ステージ番号
	enum state_stage {
		en_Stage1,	//ステージ1
		en_Stage2,	//ステージ2
		en_Stage3,	//ステージ3
		en_end,		//ゲームクリア処理用のダミー
	};

	//フェードの状態
	enum Step {
		step_WaitFadeIn,	//フェードイン待ち
		step_WaitFadeOut,	//フェードアウト待ち
		step_WaitGameOver,	//ゲームオーバー待ち
		step_nomal,			//何もない
		step_StageLoad,
		step_GameOver,
		step_GameClear,
		step_GameEnd,
	};

	//ライト取得
	CLight& getLight() {
		return light;
	}

	//カメラ取得
	Camera* getCamera(){
		return camera;
	}

	//プレイヤー取得
	Player* getPlayer() {
		return player;
	}

	//ルート判定クラス取得
	RouteJudge* getJudge() {
		return route;
	}

	//クリアフラグセット
	void setClear(bool flag) {
		isClear = flag;
	}
	//クリアフラグセット
	bool GetClear() {
		return isClear;
	}

	//オブジェクト削除フラグ取得
	bool isObjectDelete() {
		return isDelete;
	}

	//現ステップを取得
	Step isStep() {
		return step;
	}

	//ステージ番号取得
	state_stage GetStage()
	{
		return currentStage;
	}

	//現在のプレイタイム取得
	float GetTime() {
		return gameTime;
	}
	//合計プレイタイム取得
	float GetTotalTime() {
		return totalTime;
	}
private:
	void CreateStage(state_stage stage);

	//コンストラクタ
	Camera*				camera;				//カメラ
	CLight				light;				//ライト
	Player*				player;				//プレイヤー
	Map*				map;				//マップ
	inventory*			ivt;				//インベントリ
	DisplayTime*		time;				//タイム表示
	RouteJudge*			route;				//ルート判定
	CSoundSource*		bgmSource = nullptr;
	GameOverScene*		gameOver;

	//変数
	bool				isDelete;			//オブジェクト消去フラグ
	bool				isClear;			//クリアフラグ
	Step				step = step_WaitFadeOut;

	float				gameTime = 0.0f;	//プレイ時間
	float				totalTime = 0.0f;	//合計プレイ時間
	float				timer = 0.0f;	

	state_stage			currentStage = en_Stage1;	//現在のステージ
	state_stage			nextStage = en_Stage2;		//次のステージ
	CSoundSource		GameOverSE;					//ゲームオーバーのSE
};

extern GameScene* g_gameScene;
