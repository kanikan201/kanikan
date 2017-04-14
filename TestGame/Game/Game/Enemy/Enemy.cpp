#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Camera.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


Enemy::Enemy()
{
	CRandom rand;
	rand.Init((unsigned long)time(NULL));
	start = rand.GetRandDouble;
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

	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		//自分を削除
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
		return;
	}

	//プレイヤーと自身の距離
	float dist = g_gameScene->getPlayer()->Distance(position);
	if (dist < 1.0f) {
		g_gameScene->getPlayer()->SetPosition({ 0.0f,0.0f,0.0f });
	}

	m_timer += GameTime().GetFrameDeltaTime();
	if (!isMoving && m_timer > start) {
		isMoving = true;
		m_timer = 0.0f;
	}

	move = characterController.GetMoveSpeed();

	//動き
	Move();

	characterController.SetMoveSpeed(move);		//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, { 2.5f, 2.5f, 2.5f });
}

//動き
void Enemy::Move()
{
	if (!isMoving) { return; }

	if (m_timer > 2.0f) {
		dir *= -1.0f;
		m_timer = 0.0f;
		rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f*dir));
	}
	move.x = dir*5.0f;
}

//ダメージを受ける
void Enemy::Damage()
{
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}