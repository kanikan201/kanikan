#include "stdafx.h"
#include "Block.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"

Block* block = nullptr;

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

	//ワールド行列を作成
	skinModel.Update(position, rotation, { 1.7f,3.0f,1.7f });

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

	//ブロックのマスに来たら動かす
	if (g_gameScene->getJudge()->GetBlockflg() == true) {
		timer += GameTime().GetFrameDeltaTime();
		Move();
	}

	if (position.y < 0.0f) {
		position.y = 0.0f;
	}

	if (position.y > 20.0f) {
		position.y = 20.0f;
		Upflg = false;
		g_gameScene->getJudge()->SetBlockflg(false);
	}

	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });
}

void Block::Move()
{
	if (position.y <= 0.0f && Upflg == false && timer >= 2.0f) {
		move = UpPos;
		Upflg = true;
	}
	else {
		if (Upflg == false) {
			move = DownPos;
		}
		//プレイヤーとブロックの距離が一定になったらヒット
		float Blocklength = g_gameScene->getPlayer()->Distance(position);
		if (Blocklength < 5.0f) {
			PlayerHit = true;
		}
		/*else {
			PlayerHit = false;
		}*/
	}
	position.Add(move);
}

void Block::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}