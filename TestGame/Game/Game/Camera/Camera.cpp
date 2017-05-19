#include "stdafx.h"
#include "Camera.h"
#include "Scene/GameScene.h"

#define SPEED 0.05f

Camera::Camera()
{

}


Camera::~Camera()
{
}

bool Camera::Start()
{
	//カメラの位置設定
	CVector3 initCamraPos = { 0.0f, 4.0f, 12.0f };
	toPosition = initCamraPos;
	camera.Init(CVector3::Zero, initCamraPos, 100.0f);
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//画角
	camera.Update();
	cameraCollisionSolver.Init(0.2f);

	ChengeTrigger = false;
	ChengeCamera = false;

	return true;
}

void Camera::Update()
{
	//カメラを回転させる。
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	if (fabsf(rStick_x) > 0.0f) {
		//Y軸周りの回転を計算
		CMatrix mRot;
		mRot.MakeRotationY(SPEED * rStick_x);
		mRot.Mul(toPosition);
	}
	if (fabsf(rStick_y) > 0.0f) {
		//X軸周りの回転を計算
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toPosition);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, SPEED * rStick_y);

		//前のポジション
		CVector3 toPositionOld = toPosition;

		mRot.Mul(toPosition);
		CVector3 toPosDir = toPosition;
		toPosDir.Normalize();

		if (toPosDir.y < -0.1f) {
			//カメラが上向きすぎるから止める
			toPosition = toPositionOld;
		}
		else if (toPosDir.y > 0.85f) {
			//カメラが下向きすぎるから止める
			toPosition = toPositionOld;
		}
	}

	CVector3 target = g_gameScene->getPlayer()->GetPosition();

	//ターゲット微調整
	target.y += 2.0f;

	//視点設定
	camera.SetTarTarget(target);

	CVector3	chengePos;
	chengePos = { target.x,target.y + 100.0f,target.z };

	//Aボタンが押されたら視点を変える
	if (Pad(0).IsTrigger(enButtonA)) {
		//上視点に変更
		if (ChengeTrigger == false) {
			chengePos.Add(toPosition);
			camera.SetPosition(chengePos);
			ChengeCamera = true;
			ChengeTrigger = true;
		}
		//後ろ視点に変更
		else {
			target.Add(toPosition);
			camera.SetPosition(target);
			ChengeCamera = false;
			ChengeTrigger = false;
		}
	}
	//ボタンが押されてない間
	else {
		//上視点の状態
		if (ChengeCamera == true) {
			//カメラ位置セット
			chengePos.Add(toPosition);
			camera.SetPosition(chengePos);
		}
		//後ろ視点の状態
		else {
			//カメラ位置セット
			target.Add(toPosition);
			camera.SetPosition(target);
		}
	}

	camera.UpdateSpringCamera();
	//カメラコリジョン処理の実行。
	CVector3 newPos;
	if (cameraCollisionSolver.Execute(newPos, camera.GetPosition(), camera.GetTarget())) {
		camera.SetPosition(newPos);
		camera.ClearSpringParame();
	}
	camera.UpdateCamera();
}

void Camera::Reset()
{
	//カメラの位置設定
	camera.SetPosition({ 0.0f, 4.0f, 12.0f });
	camera.SetTarget(CVector3::Zero);
	toPosition.Subtract(camera.GetPosition(), camera.GetTarget());

	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//画角
}