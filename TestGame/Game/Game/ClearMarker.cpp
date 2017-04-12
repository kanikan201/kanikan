#include "stdafx.h"
#include "ClearMarker.h"
#include "Camera.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
}

void ClearMarker::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModelを初期化
	skinModelData.LoadModelData("Assets/modelData/clearMarker.x", NULL);
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//位置を記録
	this->rotation = rotation;		//回転を記録

}

void ClearMarker::Update()
{
	//プレイヤーと自身の距離
	float dist = g_gameScene->getPlayer()->Distance(position);
	if (!flag && (dist < 1.0f) && Pad(0).IsTrigger(enButtonA)) {
		flag = true;
		g_gameScene->setClear(true);
	}

	if ((sceneManager->GetScene() != SceneManager::stateGame) || g_gameScene->isObjectDelete()) {
		//自分を削除
		DeleteGO(this);
		return;
	}
}

void ClearMarker::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}