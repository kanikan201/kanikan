#include "stdafx.h"
#include "DisplayTime.h"
#include "Scene/GameScene.h"

namespace {
	const CVector2 NumSize = { 46.5f, 58.5f };	//数字のサイズ

	const CVector2 StrSize = { 136.5f, 63.0f };	//文字のサイズ
	const CVector2 StrPos = { -560.0f, 320.0f };	//文字のポジション

	const CVector2 colonSize = { 24.0f, 58.5f };
}

DisplayTime::DisplayTime()
{
}


DisplayTime::~DisplayTime()
{

}

bool DisplayTime::Start()
{
	m_StrTex.Load("Assets/sprite/time.png");

	m_Str.Init(&m_StrTex);
	m_Str.SetSize(StrSize);
	//ピボットは中央。
	m_Str.SetPivot({ 0.5f, 0.5f });
	m_Str.SetPosition(StrPos);

	for (int i = 0; i < 4; i++) {
		num[i] = NewGO<Number>(0);
	}

	//コロンの準備
	m_colonTex.Load("Assets/sprite/num/colon.png");
	m_colon.Init(&m_colonTex);
	m_colon.SetSize(colonSize);
	//ピボットは中央。
	m_colon.SetPivot({ 0.5f, 0.5f });

	float work = StrPos.x + (StrSize.x / 2.0f)+(NumSize.x/2.0f)+3.0f;

	//数字のポジション設定
	num[0]->Init({ (work), StrPos.y }, NumSize);
	num[1]->Init({ (work + NumSize.x), StrPos.y }, NumSize);
	m_colon.SetPosition({ (work + NumSize.x+ NumSize.x / 2.0f+ colonSize.x/2.0f), StrPos.y });
	num[2]->Init({ (work + NumSize.x*2.0f + colonSize.x), StrPos.y }, NumSize);
	num[3]->Init({ (work + NumSize.x*3.0f + colonSize.x), StrPos.y }, NumSize);

	return true;
}
void DisplayTime::Update()
{
	int time = (int)(g_gameScene->GetTime());

	num[0]->NumSet((time / 600));
	time %= 600;

	num[1]->NumSet((time / 60));
	time %= 60;

	num[2]->NumSet(time / 10);
	time %= 10;

	num[3]->NumSet(time);
}
void DisplayTime::PostRender(CRenderContext& renderContext)
{
	m_Str.Draw(renderContext);
	m_colon.Draw(renderContext);
}

void DisplayTime::DeleteNum()
{
	for (int i = 0; i < 4; i++) {
		DeleteGO(num[i]);
	}
}