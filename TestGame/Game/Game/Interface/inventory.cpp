#include "stdafx.h"
#include "inventory.h"
#include "Scene/GameScene.h"

namespace {
	const CVector2 NumSize = { 46.5f, 58.5f };	//�����̃T�C�Y
	const CVector2 frameSize = { 120.0f, 120.0f };		//�g�̃T�C�Y(��)
	const CVector2 framePos = { -570.0f,-290.0f };		//�g�̈ʒu(��)
}

inventory::inventory()
{
	
}


inventory::~inventory()
{
}

void inventory::Reset()
{
	stageNum = g_gameScene->GetStage();

	for (int i = 0; i < 6; i++) {
		Num[i] = i;
	}

	switch (stageNum)
	{
	case 0:
		num->NumSet(Num[2]);
		Count = Num[2];
		break;
	case 1:
		num->NumSet(Num[3]);
		Count = Num[3];
		break;
	case 2:
		num->NumSet(Num[4]);
		Count = Num[4];
		break;
	default:
		break;
	}
}

bool inventory::Start()
{
	//�e�N�X�`�����[�h
	texture.Load("Assets/sprite/Camera.jpg");

	sprite.Init(&texture);
	sprite.SetSize(frameSize);
	sprite.SetPosition(framePos);

	num = NewGO<Number>(0);

	Reset();

	float work = framePos.x + (frameSize.x / 2.0f) + (NumSize.x / 2.0f) + 3.0f;

	num->Init({ (work), framePos.y }, NumSize);

	for (int i = 0; i < 6; i++) {
		Num[i] = i;
	}

	stageNum = g_gameScene->GetStage();
	switch (stageNum)
	{
	case 0:
		num->NumSet(Num[2]);
		Count = Num[2];
		break;
	case 1:
		num->NumSet(Num[3]);
		Count = Num[3];
		break;
	case 2:
		num->NumSet(Num[4]);
		Count = Num[4];
		break;
	default:
		break;
	}

	return true;
}

void inventory::Update()
{
	if (Pad(0).IsTrigger(enButtonX) && g_gameScene->getCamera()->GetChengeIn()) {
		if (g_gameScene->getCamera()->GetTimer() > 0.0f && g_gameScene->getCamera()->GetTimer() < 0.1f) {
			Count--;
			if (Count < 0) {
				num->NumSet(0);
			}
			else {
				num->NumSet(Count);
			}
		}
	}
}

void inventory::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}

void inventory::Delete()
{
	DeleteGO(num);
}