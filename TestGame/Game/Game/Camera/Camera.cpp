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
	camera.SetPosition({ 0.0f, 4.0f, 12.0f /*0.0f, 100.0f, -24.0f*/ });
	camera.SetTarget(CVector3::Zero);
	toPosition.Subtract(camera.GetPosition(), camera.GetTarget());

	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//画角
	camera.Update();

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
	camera.SetTarget(target);

	CVector3 cameraPos;
	cameraPos = target;

	//カメラ位置セット
	cameraPos.Add(toPosition);
	camera.SetPosition(cameraPos);

	camera.Update();
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