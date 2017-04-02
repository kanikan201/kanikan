#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Camera.h"
#include "scene/GameScene.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	characterController.RemoveRigidBoby();
}

void Enemy::Init(CVector3 pos)
{
	skinModelData.LoadModelData("Assets/modelData/D_Unity.X", &animation);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_gameScene->getLight());			//デフォルトライトを設定。
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = pos;
	centralPos.Add(position, central);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f));

	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	/*
	//HPが0になった
	if (scene->isDelete() || state.hp <= 0) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	length = g_player->Distance(centralPos);
	if (!workFlag) {
		if (length > Limit) { return; }
		workFlag = true;
	}

	//プレイヤーと接触
	if (length <= 3.0f) {
		g_player->Damage(centralPos);
	}

	this->Damage();
	*/

	move = characterController.GetMoveSpeed();

	//動き
	Move();

	characterController.SetMoveSpeed(move);		//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());					//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, CVector3::One);
}

//動き
void Enemy::Move()
{

}

//ダメージを受ける
void Enemy::Damage()
{
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}