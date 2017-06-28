#include "stdafx.h"
#include "Player.h"
#include "../Enemy/TestEnemy.h"
#include "scene/GameScene.h"

#define SPEED 7.0f

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
	//モデル
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);

	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&g_gameScene->getLight());			//デフォルトライトを設定。

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//スケール・回転
	scale = { 2.5f,2.5f,2.5f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180.0f));

	CVector3 lightPos = CVector3(0.0f, 20.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);

	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	//モーション設定
	animation.SetAnimationEndTime(AnimationRun, 0.8);
	animation.SetAnimationLoopFlag(AnimationDown, false);
	animation.SetAnimationLoopFlag(AnimationKneelDown, false);
	animation.SetAnimationLoopFlag(AnimationSalute, false);

	//モーションをセット
	animation.PlayAnimation(AnimationStand);
	currentAnimSetNo = AnimationStand;
	prevAnim = currentAnimSetNo;

	//トーン設定
	darkTex.Load("Assets/modelData/utc_all2_dark.png");
	std::vector<CSkinModelMaterial*> matList;
	skinModelData.GetBody()->FindMaterials(matList, "utc_all2_light.png");
	static bool isChangeTec = false;
	if (isChangeTec == false) {
		//リストが空じゃない
		if (!matList.empty()) {
			for (size_t i = 0; i < matList.size(); i++)
			{
				if (matList[i]->GetTechnique() == CSkinModelMaterial::enTecShaderHandle_SkinModel) {
					matList[i]->Build(CSkinModelMaterial::enTypeToon);
				}
				else {
					matList[i]->Build(CSkinModelMaterial::enTypeToonNonSkin);
				}
			}
		}
		isChangeTec = true;
	}

	if (!matList.empty()) {
		for (size_t i = 0; i < matList.size(); i++)
		{
			matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DarkTex, darkTex);
		}
	}
	return true;
}

void Player::Update()
{

	skinModel.Update(position, rotation, scale);
	//アニメーション更新
	animation.Update(1.0f / 30.0f);

	//モーションが変わってたら変更する
	if (currentAnimSetNo != prevAnim) {
		animation.PlayAnimation(currentAnimSetNo, 0.3f);
	}

	//前のアニメーションを保存
	prevAnim = currentAnimSetNo;

	//切り替わり時は処理しない
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//移動
	characterController.SetMoveSpeed(Move());	//移動速度を設定
	characterController.Execute(GameTime().GetFrameDeltaTime());	//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果を受け取る

//移動してる
	if (!(g_gameScene->GetClear() || g_gameScene->getCamera()->GetChengeIn())
		&& (Pad(0).GetLStickXF()!=0.0f || Pad(0).GetLStickYF() != 0.0f))
	{
		//走りアニメーション
		currentAnimSetNo = AnimationRun;
		//向きを変更
		rotation.SetRotation(CVector3::AxisY, atan2f(dir.x, dir.z));

		if (!characterController.IsJump()) {
			timer += GameTime().GetFrameDeltaTime();

			if (timer > 0.4f) {
				//足音
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

	//挟まれたらスケールを小さくする(仮)
	if (Pad(0).IsTrigger(enButtonB)) {
		scale.x = 0.2;

		characterController.RemoveRigidBoby();
		characterController.Init(0.2f, 1.0f, position);
	}

	//影
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);
}

CVector3 Player::Move()
{

	//キャラクターの移動速度取得
	CVector3 move = characterController.GetMoveSpeed();
	if (g_gameScene->GetClear()|| g_gameScene->getCamera()->GetChengeIn()) {
		move.x = 0.0f;
		move.z = 0.0f;
		return move; 
	}

	//Bボタンでジャンプ
	/*if (Pad(0).IsTrigger(enButtonB) && !characterController.IsJump()) {
		move.y = 8.0f;
		characterController.Jump();
		CSoundSource* SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/V0001.wav");
		SE->Play(false);
	}*/

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

	if (characterController.IsJump()) {
		move.x = move.x * 2 / 3;
		move.z = move.z * 2 / 3;
	}

	return move;
}

void Player::Render(CRenderContext& renderContext)
{
	//エッジ設定
	std::vector<CSkinModelMaterial*> matList;
	skinModelData.GetBody()->FindMaterials(matList, "utc_all2_light.png");
	//リストが空じゃない
	if (!matList.empty()) {
		for (size_t i = 0; i < matList.size(); i++)
		{
			matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DepthTex, *Dof().GetDepthRenderTarget()->GetTexture());
			matList[i]->SetInt(CSkinModelMaterial::enIntShaderHandle_IsZPrepass, CEngine::Instance().isZPrepass());
		}
	}

	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}

//ポジションを設定
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

//リセット
void Player::Reset()
{
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180.0f));
	SetPosition({ 0.0f,0.0f,0.0f });
	currentAnimSetNo = AnimationStand;
	prevAnim = currentAnimSetNo;
	animation.PlayAnimation(AnimationStand);
	//アニメーション更新
	animation.Update(1.0f / 30.0f);
}

void Player::DownAnimation() 
{
	//敵と接触したときのアニメーション
	currentAnimSetNo = AnimationDown;
}

void Player::KneelDownAnimation()
{
	//同じマスを通ったときのアニメーション
	currentAnimSetNo = AnimationKneelDown;
}

void Player::SaluteAnimation()
{
	//クリア時ポーズアニメーション
	currentAnimSetNo = AnimationSalute;
}