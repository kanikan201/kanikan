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
	animation.SetAnimationEndTime(Run, 0.8);
	animation.PlayAnimation(Run);

	//背景のユニティちゃん用のカメラの設定
	camera.SetPosition({0.0f, 0.0f, 1.6f});
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

	skinModel.Update(CVector3 (0.7f, -0.45f, 0.18f), CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));

}

void BackGround::Render(CRenderContext& renderContext)
{

	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	sprite.Draw(renderContext);
	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	if (g_gameScene->getCamera()->GetChengeIn() ) {
		renderContext.SetRenderTarget(1,NULL);
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