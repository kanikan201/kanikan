#include "stdafx.h"
#include "MapChip.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


MapChip::MapChip()
{
}


MapChip::~MapChip()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
	//剛体を削除
	PhysicsWorld().RemoveRigidBody(&rigidBody);
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	//ファイルパス作成
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);

	//モデルデータをロード
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	//メッシュコライダー作成
	meshColloder.CreateFromSkinModel(&skinModel, skinModelData.GetRootBoneWorldMatrix());

	RigidBodyInfo rbInfo;				//剛体の作成
	rbInfo.collider = &meshColloder;	//剛体のコライダーを渡す

	rbInfo.mass = 0.0f;		//剛体の質量(0.0だと動かないオブジェクト)
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);

	//作成した剛体を物理ワールドに追加
	PhysicsWorld().AddRigidBody(&rigidBody);
}

void MapChip::Update()
{
	//何もしない

	//テスト用
	if (sceneManager->GetScene()!=SceneManager::stateGame) {
		//自分を削除
		DeleteGO(this);
		return;
	}
}

void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}