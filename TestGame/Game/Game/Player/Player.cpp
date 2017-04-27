#include "stdafx.h"
#include "Player.h"
#include "scene/GameScene.h"

#define SPEED 6.0f

Player::Player()
{
}

Player::~Player()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
	characterController.RemoveRigidBoby();
}

bool Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_gameScene->getLight());			//デフォルトライトを設定。

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	CVector3 lightPos = CVector3(0.0f, 20.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);

	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	animation.SetAnimationEndTime(AnimationRun, 0.8);
	animation.PlayAnimation(AnimationStand);

	return true;
}

void Player::Update()
{
	//切り替わり時は処理しない
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//前のアニメーションを保存
	prevAnim = currentAnimSetNo;

	Move();	//移動

//移動してる
	if (Pad(0).GetLStickXF()!=0.0f || Pad(0).GetLStickYF() != 0.0f)
	{
		//走りアニメーション
		currentAnimSetNo = AnimationRun;
		//向きを変更
		rotation.SetRotation(CVector3::AxisY, atan2f(dir.x, dir.z));
		if (!characterController.IsJump()) {

			timer += GameTime().GetFrameDeltaTime();

			if (timer > 0.4f) {
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init("Assets/sound/footstep.wav");
				se->Play(false);
				timer = 0.0f;
			}
		}
	}
//立ってるとき
	else 
	{

		//立ちアニメーション
		currentAnimSetNo = AnimationStand;
	}

//モーションが変わってたら変更する
	if (currentAnimSetNo != prevAnim) {
		animation.PlayAnimation(currentAnimSetNo,0.3f);
	}

	//アニメーション更新
	animation.Update(1.0f / 30.0f);
	skinModel.Update(position, rotation, {2.5f, 2.5f, 2.5f});

	//影
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);
}

void Player::Move()
{
	//キャラクターの移動速度取得
	CVector3 move = characterController.GetMoveSpeed();

	//Aボタンでジャンプ
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 8.0f;
		characterController.Jump();
	}

	//キャラの進行方向の計算
	CVector3 moveDirLocal;	//入力された方向
	moveDirLocal.y = 0.0f;
	moveDirLocal.x = Pad(0).GetLStickXF();
	moveDirLocal.z = Pad(0).GetLStickYF();

	const CMatrix& mViewInv = g_gameScene->getCamera()->GetViewMatrixInv();

	//カメラ空間から見た奥方向のベクトルを取得(Z)
	CVector3 cameraZ;
	cameraZ.x = mViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y軸はいらない
	cameraZ.z = mViewInv.m[2][2];
	cameraZ.Normalize();	//Y軸を打ち消しているので正規化する。

	//カメラから見た横方向のベクトルを取得(X)
	CVector3 cameraX;
	cameraX.x = mViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y軸はいらない
	cameraX.z = mViewInv.m[0][2];
	cameraX.Normalize();	//Y軸を打ち消しているので正規化する。

	//キャラの向きの計算
	dir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
	dir.y = 0.0f;	//Y方向は無い
	dir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

	move.x = dir.x * SPEED;
	move.z = dir.z * SPEED;

	characterController.SetMoveSpeed(move);	//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果を受け取る
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}

void Player::SetPosition(CVector3 pos) 
{
	characterController.SetPosition(pos);
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = pos;
	//影
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	skinModel.Update(position, rotation, { 2.5f, 2.5f, 2.5f });
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