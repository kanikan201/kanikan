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
			//�X�^�[�g�{�^����������
			if (title->GetChoice()) {
				if (title->GetState()== TitleScene::enContinue) {
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
					NewGO<ResultScene>(0);
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
			//�N���A���Q�[���I�[�o�[
			if (Pad(0).IsTrigger(enButtonStart)||g_gameScene->isStep()== GameScene::step_GameEnd) {
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
			//�X�^�[�g�{�^����������
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}