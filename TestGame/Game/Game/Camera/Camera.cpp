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
	//�J�����̈ʒu�ݒ�
	CVector3 initCamraPos = { 0.0f, 4.0f, 12.0f };
	toPosition = initCamraPos;
	camera.Init(CVector3::Zero, initCamraPos, 100.0f);
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//��p
	camera.Update();
	cameraCollisionSolver.Init(0.2f);

	ChengeCamera = false;	//��뎋�_
	timer = 0.0f;

	return true;
}

void Camera::Update()
{
	if (Hidden == false) {
		//X�{�^���������ꂽ�王�_��ς���
		if (Pad(0).IsTrigger(enButtonX)) {
			if (timer == 0.0f && ChengeCount > 0) {
				ChengeCamera = !ChengeCamera;
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

	//�B���ʘH�ɓ�������
	if (g_gameScene->getMapData()->GetMapInfo
		(g_gameScene->getJudge()->GetCurrentGrid_x(),
		g_gameScene->getJudge()->GetCurrentGrid_y()) == 8)
	{
		Hidden = true;
	}
	else {
		Hidden = false;
	}

	Move();	//�J�����𓮂���

	CVector3 target = g_gameScene->getPlayer()->GetPosition();
	target.y += 2.0f;				//�^�[�Q�b�g������
	camera.SetTarTarget(target);	//���_�ݒ�

	if (timer > 6.0f) {
		ChengeCamera = !ChengeCamera;
		timer = 0.0f;
	}

	//�㎋�_�̏��
	if (ChengeCamera) {
		target.y += 100.0f;	//��������

		//�J�����ʒu�Z�b�g
		target.Add(toPosition);
		camera.SetPosition(target);
		timer += GameTime().GetFrameDeltaTime();
		ChengeIn = true;
	}
	else if (Hidden) {
		target.y += 120.0f;

		target.Add(toPosition);
		camera.SetTarPosition(target);
	}
	//��뎋�_�̏��
	else {
		//�J�����ʒu�Z�b�g
		target.Add(toPosition);
		camera.SetPosition(target);
		ChengeIn = false;
	}

	//�o�l�J�����X�V
	camera.UpdateSpringCamera();

	//�J�����R���W���������̎��s�B
	CVector3 newPos;
	if (!ChengeCamera && cameraCollisionSolver.Execute(newPos, camera.GetPosition(), camera.GetTarget()))
	{
		camera.SetPosition(newPos);
		camera.ClearSpringParame();
	}

	//�J�����X�V
	camera.UpdateCamera();
}

void Camera::Move()
{
	//�؂�ւ�莞�͏������Ȃ�
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//�J��������]������B
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]���v�Z
		CMatrix mRot;
		mRot.MakeRotationY(SPEED * rStick_x);
		mRot.Mul(toPosition);
	}
	if (fabsf(rStick_y) > 0.0f) {
		//X������̉�]���v�Z
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toPosition);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, SPEED * rStick_y);

		//�O�̃|�W�V����
		CVector3 toPositionOld = toPosition;

		mRot.Mul(toPosition);
		CVector3 toPosDir = toPosition;
		toPosDir.Normalize();

		if (toPosDir.y < -0.1f) {
			//�J����������������邩��~�߂�
			toPosition = toPositionOld;
		}
		else if (toPosDir.y > 0.85f) {
			//�J�����������������邩��~�߂�
			toPosition = toPositionOld;
		}
	}
}

void Camera::Reset()
{
	//�J�����̈ʒu�ݒ�
	camera.SetPosition({ 0.0f, 4.0f, 12.0f });
	camera.SetTarget(CVector3::Zero);
	toPosition.Subtract(camera.GetPosition(), camera.GetTarget());

	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));	//��p

	ChengeCamera = false;	//��뎋�_
	timer = 0.0f;
}