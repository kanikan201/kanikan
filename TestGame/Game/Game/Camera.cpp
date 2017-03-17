#include "stdafx.h"
#include "Camera.h"
#include "Scene/GameScene.h"

Camera::Camera()
{

}


Camera::~Camera()
{
}

bool Camera::Start()
{
	//カメラとプレイヤーとの距離?
	playerDist.Set(0.0f, 4.0f, 12.0f);

	camera.SetPosition(playerDist);
	camera.SetTarget(CVector3::Zero);
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));
	camera.Update();

	return true;
}

void Camera::Update()
{
	CVector3 target = g_gameScene->getPlayer()->GetPosition();

	//ターゲット微調整
	target.y += 2.0f;
	target.z -= 2.0f;

	//視点設定
	camera.SetTarget(target);

	CVector3 cameraPos;
	cameraPos.Add(target, playerDist);
	camera.SetPosition(cameraPos);
	camera.Update();
}