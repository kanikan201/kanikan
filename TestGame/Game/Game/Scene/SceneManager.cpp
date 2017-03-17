#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "fade/Fade.h"

SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{
	//�^�C�g����ʐ���
	titel=NewGO<TitleScene>(0);
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
				g_gameScene = NewGO<GameScene>(0);
				DeleteGO(titel);
				f_step = step_WaitFadeIn;
				state = stateGame;
			}
		}
		//�ʏ펞
		else if(f_step==step_nomal){
			//�X�^�[�g�{�^����������
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;

	//�Q�[���V�[���̎�
	case stateGame:
		if (Pad(0).IsTrigger(enButtonStart)) {
			//���U���g��ʂ֑J��
			result=NewGO<ResultScene>(0);
			g_gameScene->Release();
			DeleteGO(g_gameScene);
			
			state = stateResult;
		}
		break;

	//���U���g��ʂ̎�
	case stateResult:
		if (Pad(0).IsTrigger(enButtonStart)) {
			//�^�C�g����ʂ֑J��
			titel=NewGO<TitleScene>(0);

			DeleteGO(result);

			state = stateTitel;
		}
		break;
	}
}