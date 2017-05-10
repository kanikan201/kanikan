#include "stdafx.h"
#include "GameOverScene.h"
#include "Fade\Fade.h"
#include "Scene\GameScene.h"
#include "Scene\ResultScene.h"
#include "Scene\SceneManager.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
	const CVector2 strSize = { 182.0f,68.0f };
	const CVector2 conPos= { 200.0f,-150.0f };
	const CVector2 endPos= { 200.0f,-220.0f };
}

GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{
	DeleteGO(bgmSource);
}

bool GameOverScene::Start()
{
	texture.Load("Assets/sprite/GameOver.png");
	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	con1Tex.Load("Assets/sprite/continue1.png");
	continue1.Init(&con1Tex);
	continue1.SetSize(strSize);
	continue1.SetPosition(conPos);

	con2Tex.Load("Assets/sprite/continue2.png");
	continue2.Init(&con2Tex);
	continue2.SetSize(strSize);
	continue2.SetPosition(conPos);

	end1Tex.Load("Assets/sprite/end1.png");
	end1.Init(&end1Tex);
	end1.SetSize(strSize);
	end1.SetPosition(endPos);

	end2Tex.Load("Assets/sprite/end2.png");
	end2.Init(&end2Tex);
	end2.SetSize(strSize);
	end2.SetPosition(endPos);

	//フェードイン
	g_fade->StartFadeIn();

	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/GameOverBGM.wav");
	bgmSource->Play(true);

	state = enContinue;
	isChoice = false;

	return true;
}

void GameOverScene::Update()
{
	//シーンが切り替わったら自身を削除
	if ((g_gameScene == nullptr) ||g_gameScene->isObjectDelete()) {
		DeleteGO(this);
	}

	if (isChoice) { return; }

	float input = Pad(0).GetLStickYF();

	//上選択(つづける)
	if (input > 0.0 || Pad(0).IsTrigger(enButtonUp)) {
		if (state == enEnd) {
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/Choice.wav");
			SE->Play(false);
			state = enContinue;
		}
	}
	//下選択(おわる)
	else if (input < 0.0 || Pad(0).IsTrigger(enButtonDown)) {
		if (state == enContinue) {
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/Choice.wav");
			SE->Play(false);
			state = enEnd;
		}
	}

	//決定
	if (Pad(0).IsTrigger(enButtonB)) {
		DeleteGO(bgmSource);
		//サウンド
		CSoundSource* SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/Decision.wav");
		SE->Play(false);
		isChoice = true;
	}
}
void GameOverScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
	if (state == enContinue) {
		continue1.Draw(renderContext);
		end2.Draw(renderContext);
	}
	else {
		continue2.Draw(renderContext);
		end1.Draw(renderContext);
	}
}