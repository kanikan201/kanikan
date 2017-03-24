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

	//�X�e�[�W�ԍ�
	enum state_stage {
		en_Stage1,	//�X�e�[�W1
		en_Stage2,	//�X�e�[�W2
		en_Stage3,	//�X�e�[�W3
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

private:
	Camera*				camera;				//�J����
	CLight				light;				//���C�g
	Player*				player;				//�v���C���[
	Map*				map;				//�}�b�v
	inventory*			ivt;

	state_stage			currentStage = en_Stage1;
};

extern GameScene* g_gameScene;
