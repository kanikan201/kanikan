#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{
	DeleteGO(bgmSource);
}

bool GameScene::Start()
{
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/GameBGM.wav");
	bgmSource->Play(true);

	//���C�g���������B
	light.SetAmbinetLight(CVector3::One);

	map=NewGO<Map>(0);
	player=NewGO<Player>(0);
	camera = NewGO<Camera>(0);

	return true;
}

void GameScene::Update()
{

	if (Pad(0).IsTrigger(enButtonStart)) {
		//�^�C�g����ʂɑJ�ڂ���B
		NewGO<ResultScene>(0);
		DeleteGO(camera);
		DeleteGO(player);
		DeleteGO(map);
		DeleteGO(this);
		return;
	}
	
}
/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{

}