#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"
#include "ClearScene.h"

GameScene* g_gameScene = NULL;

//�X�e�[�W1�̔z�u���
SMapInfo Stage1[] = {
#include "locationInfo/stage1.h"
};
//�X�e�[�W2�̔z�u���
SMapInfo Stage2[] = {
#include "locationInfo/stage2.h"
};

SMapInfo Stage3[] = {
#include "locationInfo/stage3.h"
};

namespace {
	const CVector2 Size = { 300.0f, 160.0f };
	const CVector2 Pos = { 0.0f,100.0f };
}

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	if (step == step_WaitFadeOut) {
		//���C�g��������
		light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
		light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
		light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
		light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

		light.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
		light.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });

		//light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
		//light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

		background = NewGO<BackGround>(0);//�w�i
		map = NewGO<Map>(0);		//�}�b�v����

		player = NewGO<Player>(0);		//�v���C���[����
		camera = NewGO<Camera>(0);		//�J��������
		ivt = NewGO<inventory>(0);		//�C���x���g������
		time = NewGO<DisplayTime>(0);	//�^�C���\������
		route = NewGO<RouteJudge>(0);

		bgmSource = NULL;
		CreateStage(currentStage);

		step = step_StageLoad;
		isDelete = false;
		isClear = false;

		/*�e�X�g?*/
		texture.Load("Assets/sprite/test2.png");
		sprite.Init(&texture);
		sprite.SetSize(Size);
		sprite.SetPosition(Pos);

		return false;
	}
	else {
		step = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}
	return true;
}

void GameScene::Update()
{
	switch (step) {

	//�X�e�[�W�̓ǂݍ��݂��I�����
	case step_StageLoad:
		g_fade->StartFadeIn();
		step = step_WaitFadeIn;
		break;

	//�t�F�[�h�A�E�g��
	case step_WaitFadeIn:
		//�t�F�[�h���I�����
		if (!g_fade->IsExecute()) {
			step = step_nomal;
		}
		break;

	//�ʏ펞
	case step_nomal:
		//�N���A����
		if (isClear == true) {
			if (timer == 0.0f) {
				DeleteGO(bgmSource);
				bgmSource = nullptr;
				//�N���A�{�C�X(��)
				CSoundSource* SE = NewGO<CSoundSource>(0);
				SE->Init("Assets/sound/V0024.wav");
				SE->Play(false);
				NewGO<ClearScene>(0);
			}
			//3�b�҂��Ă���J��
			else if (timer > 3.0f) {
				//�Ō�̃X�e�[�W���N���A����
				if (nextStage == en_end) {
					step = step_GameClear;
				}
				else{
					g_fade->StartFadeOut();
					step = step_WaitFadeOut;
				}
				totalTime += gameTime;
				timer = 0.0f;
				return;
			}
			timer += GameTime().GetFrameDeltaTime();
		}
		else {
			gameTime += GameTime().GetFrameDeltaTime();	//�v���C���ԃJ�E���g
		}
		break;
	//�t�F�[�h�A�E�g��
	case step_WaitFadeOut:
		//�I�u�W�F�N�g���폜����
		if (isDelete == true) {
			//�X�e�[�W�̐؂�ւ�
			CreateStage(nextStage);
			ivt->Reset();
			isDelete = false;
		}
		//�t�F�[�h���I�����
		else if (!g_fade->IsExecute()) {
			Reset();
			setClear(false);
			//�I�u�W�F�N�g���폜
			isDelete = true;
		}
		break;
	//�Q�[���I�[�o�[�҂�
	case step_WaitGameOver:
		timer += GameTime().GetFrameDeltaTime();
		if (!isMiss && timer > 1.7f) {
			isMiss = true;
		}
		//SE���I�����
		if (!GameOverSE.IsPlaying()) {
			step = step_GameOver;
			gameOver = NewGO<GameOverScene>(0);
			timer = 0.0f;
			isMiss = false;
		}
		break;
	//�Q�[���I�[�o�[�̎�
	case step_GameOver:
		if (gameOver->GetChoice()) {
			//�������I��
			if (gameOver->GetState()== GameOverScene::enContinue) {
				//bgmSource->Play(true);
				g_fade->StartFadeOut();
				step = step_WaitFadeOut;
				nextStage = currentStage;
			}
			//��߂��I��
			else if (gameOver->GetState()== GameOverScene::enEnd) {
				step = step_GameEnd;
			}
		}
		break;
	}
}

void GameScene::CreateStage(state_stage stage)
{
	int numObject;
	currentStage = stage;

	switch (stage) {
	case en_Stage1:
		route->Init(1, 5);
		camera->Init(2);

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);

		nextStage = en_Stage2;
		//nextStage = en_end;	//�������̓e�X�g�p
		step = step_StageLoad;

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);
		break;
	case en_Stage2:
		route->Init(5, 8);
		camera->Init(3);

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);

		nextStage = en_Stage3;
		step = step_StageLoad;
		//nextStage = en_end;	//�������̓e�X�g�p

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);
		break;
	case en_Stage3:
		route->Init(2, 5);

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage3) / sizeof(Stage3[0]);
		map->Create(Stage3, numObject);

		camera->Init(4);

		nextStage = en_end;
		step = step_StageLoad;

		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/Dungeon.wav");
		bgmSource->Play(true);
		break;
	}
	step = step_StageLoad;
}
/*!
*@brief	�`��֐��B
*/
void GameScene::PostRender(CRenderContext& renderContext)
{
	if (isMiss) {
		sprite.Draw(renderContext);
	}
}

//�����������̂��������
void GameScene::Release() {
	DeleteGO(camera);	//�J����
	DeleteGO(player);	//�v���C���[
	DeleteGO(background);//�w�i
	DeleteGO(map);		//�}�b�v
	ivt->Delete();
	DeleteGO(ivt);
	time->DeleteNum();
	DeleteGO(time);
	DeleteGO(bgmSource);
	bgmSource = nullptr;
	DeleteGO(route);
}

//�Q�[���I�[�o�[�֐؂�ւ�
void GameScene::SetGameOver() {
	DeleteGO(bgmSource);
	bgmSource = nullptr;
	AddGO(0, &GameOverSE);
	GameOverSE.Init("Assets/sound/jingle.wav");
	GameOverSE.Play(false);
	step = step_WaitGameOver;
	route->Reset(route->GetInitialGrid_x(), route->GetInitialGrid_y());
	timer = 0.0f;
	getPlayer()->DeadAnimation();
}

//���Z�b�g
void GameScene::Reset() {
	player->Reset();
	gameTime = 0.0f;
	camera->Reset();
}