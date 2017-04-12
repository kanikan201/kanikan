/*
	�V�[���Ǘ��֐�
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

	//�V�[�����
	enum SceneState {
		stateTitel,
		stateGame,
		stateResult,
	};

	//�t�F�[�h�̏��
	enum FadeStep {
		step_WaitFadeIn,	//�t�F�[�h�C���҂�
		step_WaitFadeOut,	//�t�F�[�h�A�E�g�҂�
		step_nomal,			//�����Ȃ�
	};

	//���݂̃V�[�����擾
	SceneState GetScene() {
		return state;
	}

private:
	SceneState			state;		//���݂̃V�[��
	FadeStep			f_step;
};

extern SceneManager* sceneManager;