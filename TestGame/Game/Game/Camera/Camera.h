#pragma once
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
		return camera.GetViewMatrix();
	}
	const CMatrix& GetViewMatrixInv() const
	{
		return camera.GetViewMatrixInv();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}
	const CCamera& GetCamera() const
	{
		return camera;
	}

private:
	CCamera		camera;			//カメラ
	CVector3	toPosition;		//注視点から視点へのベクトル。
};

