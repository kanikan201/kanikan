#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "fade/Fade.h"

SceneManager* sceneManager;

SceneManager::SceneManager()
{	
	//タイトル画面生成
	title = NewGO<TitleScene>(0);
	state = stateTitel;
	f_step = step_nomal;
}
SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{


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
				f_step = step_WaitFadeIn;
				state = stateGame;
			}
		}
		//通常時
		else if(f_step==step_nomal){
			//決定をした
			if (title->GetChoice()) {
				if (title->GetState()== TitleScene::enStart) {
					g_fade->StartFadeOut();
					f_step = step_WaitFadeOut;
				}
				else {
					exit(0);
				}
			}
		}
		break;

//ゲームシーンの時
	case stateGame:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終わった
			if (!g_fade->IsExecute()) {

				if (g_gameScene->isStep() == GameScene::step_GameEnd) {
					//タイトルへ遷移
					title = NewGO<TitleScene>(0);
					state = stateTitel;
				}
				else {
					//リザルトへ遷移
					ResultScene* result= NewGO<ResultScene>(0);
					result->Init();
					state = stateResult;
				}

				g_gameScene->Release();
				DeleteGO(g_gameScene);
				g_gameScene = nullptr;

				f_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (f_step == step_nomal) {
			GameScene::Step g_step = g_gameScene->isStep();
			//クリアかゲームオーバー
			if (g_step ==GameScene::step_GameClear|| g_step == GameScene::step_GameEnd) {
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
				title = NewGO<TitleScene>(0);
				f_step = step_WaitFadeIn;
				state = stateTitel;
			}
		}
		//通常時
		else if (f_step == step_nomal) {
			//Aボタンを押した
			if (Pad(0).IsTrigger(enButtonA)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}