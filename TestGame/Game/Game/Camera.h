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
	CCamera		camera;			//ƒJƒƒ‰
	CVector3	playerDist;		//ƒJƒƒ‰‚ÌˆÊ’u
};

