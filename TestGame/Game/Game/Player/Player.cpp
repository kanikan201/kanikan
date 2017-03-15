#include "stdafx.h"
#include "Player.h"
#include "scene/GameScene.h"

Player::Player()
{
}

Player::~Player()
{
	characterController.RemoveRigidBoby();
}

bool Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_gameScene->getLight());			//デフォルトライトを設定。
	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	animation.SetAnimationEndTime(AnimationRun, 0.8);
	animation.PlayAnimation(AnimationStand);

	return true;
}

void Player::Update()
{
	anim = currentAnimSetNo;

	//キャラクターの移動速度
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//Aボタンでジャンプ
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 8.0f;
		characterController.Jump();
	}

	characterController.SetMoveSpeed(move);	//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());			//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り

//走ってるとき
	if (move.x != 0.0f || move.z != 0.0f) 
	{
		currentAnimSetNo = AnimationRun;
		dir.x = -Pad(0).GetLStickXF();
		dir.z = -Pad(0).GetLStickYF();

		//向き変更
		rotation.SetRotation(CVector3::AxisY, atan2f(dir.x, dir.z));
	}
//立ってるとき
	else 
	{
		currentAnimSetNo = AnimationStand;
	}

//モーションが変わってたら変更する
	if (currentAnimSetNo != anim) {
		animation.PlayAnimation(currentAnimSetNo,0.3f);
	}

	//アニメーション更新
	animation.Update(1.0f / 30.0f);
	skinModel.Update(position, rotation, {2.5f, 2.5f, 2.5f});
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}


//プレイヤーと対象の距離を計算して返す
float Player::Distance(CVector3& objectPos)
{
	CVector3 diff;

	//プレイヤーの座標から敵の座標を減算
	diff.Subtract(position, objectPos);
	//敵とプレイヤーの距離を計算
	return diff.Length();
}