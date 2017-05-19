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

private:
	CSpringCamera			camera;			//カメラ
	CVector3				toPosition;		//注視点から視点へのベクトル。
	CCameraCollisionSolver	cameraCollisionSolver;
	bool					ChengeTrigger;	//カメラの視点変更を決定するフラグ
	bool					ChengeCamera;	//カメラの視点を変えるフラグ
};

