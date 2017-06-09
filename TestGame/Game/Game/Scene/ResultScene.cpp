#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "fade/Fade.h"
#include "SceneManager.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };

	const CVector2 NumSize = { 62.0f, 78.5f };	//数字のサイズ
	const CVector2 StrSize = { 393.0f, 84.0f };	//文字のサイズ
	const CVector2 StrPos = { -160.0f, 0.0f };	//文字のポジション

	const CVector2 colonSize = { 32.0f, 78.0f };
}

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	DeleteGO(bgm);
}
bool ResultScene::Start()
{
	texture.Load("Assets/sprite/result.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	m_StrTex.Load("Assets/sprite/total_time.png");

	m_Str.Init(&m_StrTex);
	m_Str.SetSize(StrSize);
	//ピボットは中央。
	m_Str.SetPivot({ 0.5f, 0.5f });
	m_Str.SetPosition(StrPos);

	//コロンの準備
	m_colonTex.Load("Assets/sprite/num/colon.png");
	m_colon.Init(&m_colonTex);
	m_colon.SetSize(colonSize);
	//ピボットは中央。
	m_colon.SetPivot({ 0.5f, 0.5f });

	float work = StrPos.x + (StrSize.x / 2.0f) + (NumSize.x / 2.0f) + 3.0f;
	m_colon.SetPosition({ (work + NumSize.x + NumSize.x / 2.0f + colonSize.x / 2.0f), StrPos.y });



	//フェードイン
	g_fade->StartFadeIn();


	bgm = NewGO<CSoundSource>(0);
	bgm->Init("Assets/sound/Result.wav");
	bgm->Play(true);
	return true;
}

void ResultScene::Init()
{
	for (int i = 0; i < 4; i++) {
		num[i] = NewGO<Number>(0);
	}

	float work = StrPos.x + (StrSize.x / 2.0f) + (NumSize.x / 2.0f) + 3.0f;

	//数字のポジション設定
	num[0]->Init({ (work), StrPos.y }, NumSize);
	num[1]->Init({ (work + NumSize.x), StrPos.y }, NumSize);
	num[2]->Init({ (work + NumSize.x*2.0f + colonSize.x), StrPos.y }, NumSize);
	num[3]->Init({ (work + NumSize.x*3.0f + colonSize.x), StrPos.y }, NumSize);

	int time = (int)(g_gameScene->GetTotalTime());

	num[0]->NumSet((time / 600));
	time %= 600;
	num[1]->NumSet((time / 60));
	time %= 60;
	num[2]->NumSet(time / 10);
	time %= 10;
	num[3]->NumSet(time);
}

void ResultScene::Update()
{
	//シーンが切り替わったら自身を削除
	if (sceneManager->GetScene() != SceneManager::stateResult) {
		for (int i = 0; i < 4; i++) {
			DeleteGO(num[i]);
		}
		DeleteGO(this);
	}
}
void ResultScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
	m_Str.Draw(renderContext);
	m_colon.Draw(renderContext);
}