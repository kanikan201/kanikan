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
//ゲッター
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
	CSpringCamera			camera;			//カメラ
	CVector3				toPosition;		//注視点から視点へのベクトル。
	CCameraCollisionSolver	cameraCollisionSolver;
	bool					ChengeCamera;	//カメラの視点を変えるフラグ
	float					timer;			//上視点のタイマー
	int						ChengeCount;	//カメラの視点変更回数
	bool					ChengeIn;		//カメラ変更中フラグ
};

