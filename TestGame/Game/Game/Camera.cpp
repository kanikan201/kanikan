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
	//�J�����ƃv���C���[�Ƃ̋���?
	playerDist.Set(0.0f, 4.0f, 12.0f);

	camera.SetPosition(playerDist);
	camera.SetTarget(CVector3::Zero);
	toPosition.Subtract(camera.GetPosition(), camera.GetTarget());
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));
	camera.Update();

	return true;
}

void Camera::Update()
{
	//�J��������]������B
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]���v�Z�B
		//��
		CMatrix mRot;
		mRot.MakeRotationY(SPEED * rStick_x);
		mRot.Mul(toPosition);
	}
	if (fabsf(rStick_y) > 0.0f) {
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toPosition);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, SPEED * rStick_y);
		CVector3 toPositionOld = toPosition;
		mRot.Mul(toPosition);
		CVector3 toPosDir = toPosition;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//�J����������������邩��~�߂�
			toPosition = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������邩��~�߂�
			toPosition = toPositionOld;
		}
	}

	CVector3 target = g_gameScene->getPlayer()->GetPosition();

	//�^�[�Q�b�g������
	target.y += 2.0f;

	//���_�ݒ�
	camera.SetTarget(target);

	CVector3 cameraPos;
	cameraPos = target;
	//cameraPos.Add(target, playerDist);

	cameraPos.Add(toPosition);
	camera.SetPosition(cameraPos);

	camera.Update();
}