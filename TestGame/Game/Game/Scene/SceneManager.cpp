#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "fade/Fade.h"

SceneManager* sceneManager;

SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{
	//タイトル画面生成
	titel=NewGO<TitleScene>(0);
	state = stateTitel;
	f_step = step_nomal;

	return true;
}

void SceneManager::Update()
{
	//フェードイン中
	if (f_step == step_WaitFadeIn) {
		//フェードが終わった
		if (!g_fade->IsExecute()) {
			f_step = step_nomal;
		}
	}

	switch (state)
	{
	//タイトル画面の時
	case stateTitel:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終わった
			if (!g_fade->IsExecute()) {
				//ゲームシーンへ遷移
				g_gameScene = NewGO<GameScene>(0);
				DeleteGO(titel);
				f_step = step_WaitFadeIn;
				state = stateGame;
			}
		}
		//通常時
		else if(f_step==step_nomal){
			//スタートボタンを押した
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;

	//ゲームシーンの時
	case stateGame:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終わった
			if (!g_fade->IsExecute()) {
				//リザルトへ遷移
				result = NewGO<ResultScene>(0);
				g_gameScene->Release();
				DeleteGO(g_gameScene);
				f_step = step_WaitFadeIn;
				state = stateResult;
			}
		}
		//通常時
		else if (f_step == step_nomal) {
			//スタートボタンを押した
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;

	//リザルト画面の時
	case stateResult:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終わった
			if (!g_fade->IsExecute()) {
				//タイトル画面へ遷移
				titel = NewGO<TitleScene>(0);
				DeleteGO(result);
				f_step = step_WaitFadeIn;
				state = stateTitel;
			}
		}
		//通常時
		else if (f_step == step_nomal) {
			//スタートボタンを押した
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}