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
	//�^�C�g����ʐ���
	title = NewGO<TitleScene>(0);
	state = stateTitel;
	f_step = step_nomal;

	return true;
}

void SceneManager::Update()
{
	//�t�F�[�h�C����
	if (f_step == step_WaitFadeIn) {
		//�t�F�[�h���I�����
		if (!g_fade->IsExecute()) {
			f_step = step_nomal;
		}
	}

	switch (state)
	{
//�^�C�g����ʂ̎�
	case stateTitel:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I�����
			if (!g_fade->IsExecute()) {
				//�Q�[���V�[���֑J��
				g_gameScene = NewGO<GameScene>(0);
				f_step = step_WaitFadeIn;
				state = stateGame;
			}
		}
		//�ʏ펞
		else if(f_step==step_nomal){
			//���������
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

//�Q�[���V�[���̎�
	case stateGame:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I�����
			if (!g_fade->IsExecute()) {

				if (g_gameScene->isStep() == GameScene::step_GameEnd) {
					//�^�C�g���֑J��
					title = NewGO<TitleScene>(0);
					state = stateTitel;
				}
				else {
					//���U���g�֑J��
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
		//�ʏ펞
		else if (f_step == step_nomal) {
			GameScene::Step g_step = g_gameScene->isStep();
			//�N���A���Q�[���I�[�o�[
			if (g_step ==GameScene::step_GameClear|| g_step == GameScene::step_GameEnd) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;

//���U���g��ʂ̎�
	case stateResult:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I�����
			if (!g_fade->IsExecute()) {
				//�^�C�g����ʂ֑J��
				title = NewGO<TitleScene>(0);
				f_step = step_WaitFadeIn;
				state = stateTitel;
			}
		}
		//�ʏ펞
		else if (f_step == step_nomal) {
			//A�{�^����������
			if (Pad(0).IsTrigger(enButtonA)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}