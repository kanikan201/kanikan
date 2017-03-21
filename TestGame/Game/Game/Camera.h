#pragma once
class Camera:public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();

	const CMatrix& GetViewMatrix() const 
	{
		return camera.GetViewMatrix();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}

private:
	CCamera		camera;			//カメラ
	CVector3	playerDist;		//カメラとプレイヤーの距離みたいなの
	CVector3	toPosition;		//注視点から視点へのベクトル。
};

