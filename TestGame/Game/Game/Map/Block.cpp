#include "stdafx.h"
#include "Block.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"
#include "Route\RouteJudge.h"

Block* block;

Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModelを初期化
	skinModelData.LoadModelData("Assets/modelData/block.x", NULL);
	skinModel.Init(skinModelData.GetBody());

	//デフォルトライト設定
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	characterController.Init(5.0f, 5.0f, position);	//キャラクタコントローラの初期化。
	characterController.SetMoveSpeed(move);

	//ワールド行列を作成
	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });

	this->position = position;		//位置を記録
	this->rotation = rotation;		//回転を記録
}

void Block::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		//自分を削除
		DeleteGO(this);
		return;
	}

	//通常時しか処理しない
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	if (g_gameScene->getJudge()->GetBlockflg() == true) {
		Move();
	}

	if (position.y > 20.0f) {
		position.y = 20.0f;
		Upflg = false;
	}

	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });
}

void Block::Move()
{
	
	if (position.y <= 2.0f && Upflg == false) {
		move = UpPos;
		Upflg = true;
	}
	else {
		if (Upflg == false) {
			move = DownPos;
		}
	}
	characterController.SetMoveSpeed(move);		//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
}

void Block::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}