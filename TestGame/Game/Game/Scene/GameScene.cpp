#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	//���C�g��������
	light.SetAmbinetLight(CVector3::One);

	map		= NewGO<Map>(0);		//�}�b�v����
	player	= NewGO<Player>(0);		//�v���C���[����
	camera	= NewGO<Camera>(0);		//�J��������

	g_fade->StartFadeIn();
	return true;
}

void GameScene::Update()
{

}
/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{

}

//�����������̂��������
void GameScene::Release() {
	DeleteGO(camera);	//�J����
	DeleteGO(player);	//�v���C���[
	DeleteGO(map);		//�}�b�v
}