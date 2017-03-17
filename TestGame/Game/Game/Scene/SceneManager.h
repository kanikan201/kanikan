/*
	シーン管理関数
*/

#pragma once
#include "TitleScene.h"
#include "ResultScene.h"

class SceneManager : public IGameObject
{
public:
	SceneManager();
	~SceneManager();
	bool Start();
	void Update();

	//シーン状態
	enum SceneState {
		stateTitel,
		stateGame,
		stateResult,
	};

	//フェードの状態
	enum FadeStep {
		step_WaitFadeIn,	//フェードイン待ち
		step_WaitFadeOut,	//フェードアウト待ち
		step_nomal,			//何もない
	};

private:
	SceneState			state;		//現在のシーン
	FadeStep			f_step;

	TitleScene*			titel;		//タイトル
	ResultScene*		result;		//リザルト
};