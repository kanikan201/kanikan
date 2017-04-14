/*
	�Q�[���V�[���֐�
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
private:
	Camera*				camera;				//�J����
	CLight				light;				//���C�g
	Player*				player;				//�v���C���[
	Map*				map;				//�}�b�v
	inventory*			ivt;				//�C���x���g��
	bool				isDelete;			//�I�u�W�F�N�g�����t���O
	bool				isClear;			//�N���A�t���O
	FadeStep			fadeStep = step_WaitFadeOut;

	state_stage			currentStage = en_Stage1;	//���݂̃X�e�[�W
};

extern GameScene* g_gameScene;
