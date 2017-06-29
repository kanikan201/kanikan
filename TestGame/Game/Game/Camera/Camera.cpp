#include "stdafx.h"
#include "Camera.h"
#include "Scene/GameScene.h"
#include "Map/MapData.h"

#define SPEED 0.05f

Camera::Camera()
{

}


Camera::~Camera()
{
}

void Camera::Init(int count)
{
	ChengeCount = count;
	ChengeIn = false;
	Hidden = false;
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

	ChengeCamera = false;	//後ろ視点
	timer = 0.0f;

	return true;
}

void Camera::Update()
{
	if (Hidden == false && 
		g_gameScene->isStep() == GameScene::step_nomal && !g_gameScene->GetClear()) {
		//Xボタンが押されたら視点を変える
		if (Pad(0).IsTrigger(enButtonX)) {
			if (timer == 0.0f && ChengeCount > 0) {
				ChengeCamera = true/*!ChengeCamera*/;
				ChengeCount--;

				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init("Assets/sound/decision26.wav");
				se->Play(false);
			}
			else if (ChengeCount == 0) {
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init("Assets/sound/cancel6.wav");
				se->Play(false);
			}
		}
	}

	//隠し通路に入ったら
	if (g_gameScene->getMapData()->GetMapInfo
		(g_gameScene->getJudge()->GetCurrentGrid_x(),
		g_gameScene->getJudge()->GetCurrentGrid_y()) == 8)
	{
		Hidden = true;
	}
	else {
		Hidden = false;
	}

	Move();	//カメラを動かす

	CVector3 target = g_gameScene->getPlayer()->GetPosition();
	target.y += 2.0f;				//ターゲット微調整
	camera.SetTarTarget(target);	//視点設定

	//30秒か1分
	if (timer > 30.0f || Pad(0).IsTrigger(enButtonY)) {
		ChengeCamera = false/*!ChengeCamera*/;
		timer = 0.0f;
	}

	//上視点の状態
	if (ChengeCamera) {
		target.y += 100.0f;	//高さ調整
		timer += GameTime().GetFrameDeltaTime();
		ChengeIn = true;
		//カメラ位置セット
		target.Add(toPosition);
		camera.SetPosition(target);
	}
	else if (Hidden) {
		camera.SetTarget(target);
		target.y += 40.0f;

		target.Add(toPosition);
		camera.SetPosition(target);
	}
	//後ろ視点の状態
	else {
		//カメラ位置セット
		target.Add(toPosition);
		camera.SetPosition(target);
		ChengeIn = false;
	}
	if (Hidden == false) {
		//バネカメラ更新
		camera.UpdateSpringCamera();
	}
	//カメラコリジョン処理の実行。
	CVector3 newPos;
	if (!ChengeCamera && Hidden == false 
		&& cameraCollisionSolver.Execute(newPos, camera.GetPosition(), camera.GetTarget()))
	{
		camera.SetPosition(newPos);
		camera.ClearSpringParame();
	}

	//カメラ更新
	camera.UpdateCamera();
}

void Camera::Move()
{
	//切り替わり時は処理しない
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }
	if (g_gameScene->GetClear()) { return; }

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
}

void Camera::Reset()
{
	//カメラの位置設定
	camera.SetPosition({ 0.0f, 4.0f, 12.0f });
	camera.SetTarget(CVector3::Zero);
	toPosition.Subtract(camera.GetPosition(), camera.GetTarget());

	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//画角

	ChengeCamera = false;	//後ろ視点
	timer = 0.0f;
}