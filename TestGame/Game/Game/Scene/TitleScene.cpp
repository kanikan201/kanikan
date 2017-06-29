#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "fade/Fade.h"
#include "SceneManager.h"

namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
	const CVector2 strSize = { 255.0f,85.0f };
	const CVector2 conPos = { 250.0f,-100.0f };
	const CVector2 endPos = { 250.0f,-200.0f };
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{

}
bool TitleScene::Start()
{
	texture.Load("Assets/sprite/starsky.png");

	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	con1Tex.Load("Assets/sprite/command/start1.png");
	continue1.Init(&con1Tex);
	continue1.SetSize(strSize);
	continue1.SetPosition(conPos);

	con2Tex.Load("Assets/sprite/command/start2.png");
	continue2.Init(&con2Tex);
	continue2.SetSize(strSize);
	continue2.SetPosition(conPos);

	end1Tex.Load("Assets/sprite/command/exit1.png");
	end1.Init(&end1Tex);
	end1.SetSize(strSize);
	end1.SetPosition(endPos);

	end2Tex.Load("Assets/sprite/command/exit2.png");
	end2.Init(&end2Tex);
	end2.SetSize(strSize);
	end2.SetPosition(endPos);

	bgm = NewGO<CSoundSource>(0);
	bgm->Init("Assets/sound/Title.wav");
	bgm->Play(true);

	g_fade->StartFadeIn();
	state = enStart;
	isChoice = false;

	return true;
}
void TitleScene::Update()
{
	//シーンが切り替わったら自身を削除
	if (sceneManager->GetScene() != SceneManager::stateTitel) {
		DeleteGO(this);
	}

	if (isChoice) { return; }

	timer += GameTime().GetFrameDeltaTime();
	if (timer >= 2.6f) { 
		timer = 0.0f; 
		alpha = 1.0f;
	}
	if(timer>=1.5f && timer<2.0f){
		alpha -= 0.06f;
	}
	else if(timer>=2.0f &&timer<2.5f) {
		alpha += 0.06;
	}


	float input = Pad(0).GetLStickYF();

	//上選択(つづける)
	if (input > 0.0 || Pad(0).IsTrigger(enButtonUp)) {
		if (state == enExit) {
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/Choice.wav");
			SE->Play(false);
			state = enStart;
			alpha = 1.0f;
			timer = 0.0f;
		}
	}
	//下選択(おわる)
	else if (input < 0.0 || Pad(0).IsTrigger(enButtonDown)) {
		if (state == enStart) {
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/Choice.wav");
			SE->Play(false);
			state = enExit;
			timer = 0.0f;
			alpha = 1.0f;
		}
	}

	//決定
	if (Pad(0).IsTrigger(enButtonA)) {
		DeleteGO(bgm);
		//サウンド
		CSoundSource* SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/Decision.wav");
		SE->Play(false);
		isChoice = true;
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
	sprite.Draw(renderContext);
	if (state == enStart) {
		continue1.SetAlpha(alpha);
		//if (timer >= 0 && timer <= 1.3) {
		//	continue1.Draw(renderContext);
		//}
		continue1.Draw(renderContext);
		end2.Draw(renderContext);
	}
	else {
		continue2.Draw(renderContext);
		//if (timer >= 0 && timer <= 1.3) {
		//	end1.Draw(renderContext);
		//}
		end1.SetAlpha(alpha);
		end1.Draw(renderContext);
	}
}