/*
	ゲームシーン関数
*/

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera.h"
#include "Map/Map.h"
#include "inventory.h"

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
	void ChangeStage();

	//ステージ番号
	enum state_stage {
		en_Stage1,	//ステージ1
		en_Stage2,	//ステージ2
		en_Stage3,	//ステージ3
	};

	//フェードの状態
	enum FadeStep {
		step_WaitFadeIn,	//フェードイン待ち
		step_WaitFadeOut,	//フェードアウト待ち
		step_nomal,			//何もない
		step_StageLoad,
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

	//クリアフラグセット
	void setClear(bool flag) {
		isClear = flag;
	}

	//オブジェクト削除フラグ取得
	bool isObjectDelete() {
		return isDelete;
	}

	//現ステップを取得
	FadeStep isStep() {
		return fadeStep;
	}
private:
	Camera*				camera;				//カメラ
	CLight				light;				//ライト
	Player*				player;				//プレイヤー
	Map*				map;				//マップ
	inventory*			ivt;				//インベントリ
	bool				isDelete = false;		//オブジェクト消去フラグ
	bool				isClear	 = false;		//クリアフラグ
	FadeStep			fadeStep = step_WaitFadeOut;

	state_stage			currentStage = en_Stage1;	//現在のステージ
};

extern GameScene* g_gameScene;
