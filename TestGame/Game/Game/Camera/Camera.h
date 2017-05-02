#pragma once
class Camera:public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	void Reset();

//�Q�b�^�[
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
	CCamera		camera;			//�J����
	CVector3	toPosition;		//�����_���王�_�ւ̃x�N�g���B
};

