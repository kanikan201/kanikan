/*
	�Q�[���V�[���֐�
*/

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera.h"
#include "Map/Map.h"

class GameScene :
	public IGameObject
{
public:

	GameScene();

	~GameScene();
	bool Start() override;
	/*!
	 *@brief	�X�V�֐��B
	 */
	void Update() override;
	/*!
	*@brief	�`��֐��B
	*/
	void Render(CRenderContext& renderContext);

	//���
	void Release();

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
};

extern GameScene* g_gameScene;
