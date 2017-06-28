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


	/*qRotX.SetRotation(CVector3(1.0f, 0.0f, 0.0f), CMath::DegToRad(-90.0f));
	qRotY.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(20.0f));
	View.Multiply(qRotX, qRotY);*/

	camera.SetPosition({0.0f, 0.0f, 1.2f});
	camera.SetTarget({0.0f, 0.0f, 0.0f});
	camera.Update();
	return true;
}


void BackGround::Update()
{
	if (sceneManager->GetScene() == SceneManager::stateResult) {
		DeleteGO(this);
	}

	//アニメーション更新
	animation.Update(1.0f / 30.0f);

	//ステージによって背景のユニティちゃんの位置を変更
	switch (g_gameScene->GetStage())
	{
	case 0: {
		static CVector3 pos = { 0.7f, -0.45f, 0.2f };
		skinModel.Update(pos, CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
	}break;
	case 1:
		skinModel.Update(CVector3(70.0f, 0.0f, -10.0f), View, CVector3(50.0f, 50.0f, 50.0f));
		break;
	case 2:
		skinModel.Update(CVector3(50.0f, 0.0f, 20.0f), View, CVector3(50.0f, 50.0f, 50.0f));
		break;
	default:
		break;
	}

}

void BackGround::Render(CRenderContext& renderContext)
{
	if (g_gameScene->getCamera()->GetChengeIn() ) {
		renderContext.SetRenderTarget(1,NULL);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		sprite.Draw(renderContext);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());

		renderContext.Clear(0, nullptr, D3DCLEAR_ZBUFFER,
			D3DCOLOR_RGBA(0, 0, 255, 0), 1.0f, 0);
		renderContext.SetRenderTarget(1, Dof().GetDepthRenderTarget());
		
	}
}

void BackGround::SetPosition(CVector3 pos)
{
	characterController.SetPosition(pos);
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = pos;
}