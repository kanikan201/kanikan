#include "stdafx.h"
#include "BackGround.h"
#include "Scene\GameScene.h"
#include "SceneManager.h"


namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
	const CVector2 BackPos = { 0.0f,0.0f };
}


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}


bool BackGround::Start()
{
	texture.Load("Assets/sprite/BackGround.png");
	sprite.Init(&texture);
	sprite.SetSize(BackSize);
	sprite.SetPosition(BackPos);

	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&g_gameScene->getLight());			//デフォルトライトを設定。
	animation.PlayAnimation(AnimationRun);


	qRotX.SetRotation(CVector3(1.0f, 0.0f, 0.0f), CMath::DegToRad(-90.0f));
	qRotY.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(20.0f));
	View.Multiply(qRotX, qRotY);

	return true;
}


void BackGround::Update()
{
	if (sceneManager->GetScene() == SceneManager::stateResult) {
		DeleteGO(this);
	}

	//アニメーション更新
	animation.Update(1.0f / 30.0f);
	skinModel.Update(CVector3(50.0f, 0.0f, 10.0f), View, CVector3(50.0f, 50.0f, 50.0f));
}

void BackGround::Render(CRenderContext& renderContext)
{
	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	sprite.Draw(renderContext);	
	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
	
}

void BackGround::SetPosition(CVector3 pos)
{
	characterController.SetPosition(pos);
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = pos;
}