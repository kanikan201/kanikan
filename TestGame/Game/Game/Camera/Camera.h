#pragma once
#include "tkEngine/camera/tkCameraCollisionSolver.h"

class Camera:public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	void Reset();
	void Move();
	void Init(int count);
//�Q�b�^�[
	const CMatrix& GetViewMatrix() const 
	{
		return camera.GetCamera()->GetViewMatrix();
	}
	const CMatrix& GetViewMatrixInv() const
	{
		return camera.GetCamera()->GetViewMatrixInv();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetCamera()->GetProjectionMatrix();
	}
	const CCamera& GetCamera() const
	{
		return *camera.GetCamera();
	}
	bool GetChengeIn() {
		return ChengeIn;
	}
private:
	CSpringCamera			camera;			//�J����
	CVector3				toPosition;		//�����_���王�_�ւ̃x�N�g���B
	CCameraCollisionSolver	cameraCollisionSolver;
	bool					ChengeCamera;	//�J�����̎��_��ς���t���O
	float					timer;			//�㎋�_�̃^�C�}�[
	int						ChengeCount;	//�J�����̎��_�ύX��
	bool					ChengeIn;		//�J�����ύX���t���O
};

