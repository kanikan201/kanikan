/*
	�Q�[���V�[���֐�
*/

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera/Camera.h"
#include "Map/Map.h"
#include "Interface/inventory.h"
#include "Interface/DisplayTime.h"
#include "RouteJudge.h"

class GameScene :
	public IGameObject
{
public:

	GameScene();

	~GameScene();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext);

	void Release();		//���
	void ChangeStage();

	//�X�e�[�W�ԍ�
	enum state_stage {
		en_Stage1,	//�X�e�[�W1
		en_Stage2,	//�X�e�[�W2
		en_Stage3,	//�X�e�[�W3
	};

	//�t�F�[�h�̏��
	enum FadeStep {
		step_WaitFadeIn,	//�t�F�[�h�C���҂�
		step_WaitFadeOut,	//�t�F�[�h�A�E�g�҂�
		step_nomal,			//�����Ȃ�
		step_StageLoad,
	};

	//���C�g�擾
	CLight& getLight() {
		return light;
	}

	//�J�����擾
	Camera* getCamera(){
		return camera;
	}

	//�v���C���[�擾
	Player* getPlayer() {
		return player;
	}

	//�N���A�t���O�Z�b�g
	void setClear(bool flag) {
		isClear = flag;
	}

	//�I�u�W�F�N�g�폜�t���O�擾
	bool isObjectDelete() {
		return isDelete;
	}

	//���X�e�b�v���擾
	FadeStep isStep() {
		return fadeStep;
	}

	float GetTime() {
		return gameTime;
	}
	float GetTotalTime() {
		return totalTime;
	}
private:
	//�R���X�g���N�^
	Camera*				camera;				//�J����
	CLight				light;				//���C�g
	Player*				player;				//�v���C���[
	Map*				map;				//�}�b�v
	inventory*			ivt;				//�C���x���g��
	DisplayTime*		time;				//�^�C���\��
	RouteJudge*			route;

	//�ϐ�
	bool				isDelete;			//�I�u�W�F�N�g�����t���O
	bool				isClear;			//�N���A�t���O
	FadeStep			fadeStep = step_WaitFadeOut;

	float				gameTime = 0.0f;
	float				totalTime = 0.0f;

	state_stage			currentStage = en_Stage1;	//���݂̃X�e�[�W
	CSoundSource* bgmSource;
};

extern GameScene* g_gameScene;
