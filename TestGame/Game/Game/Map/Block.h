#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class Block: public IGameObject
{
public:
	Block();
	~Block();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();

	bool GetPlayerHit()
	{
		return PlayerHit;
	}
	void SetPlayerHit(bool flg) {
		PlayerHit = flg;
	}
	CVector3 GetPosition() {
		return position;
	}
private:
	CSkinModel					skinModel;		//�X�L�����f��
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^

	CVector3					position;
	CQuaternion					rotation;
	CVector3					DownPos = { 0.0f,-2.0f,0.0f };	//�������̃x�N�g��
	CVector3					UpPos = { 0.0f,1.0f,0.0f };	//������̃x�N�g��
	CVector3					move = CVector3::Zero;
	bool						Upflg = false;	//��ɓ������t���O
	bool						PlayerHit = false;	//�v���C���[�Ƃ̃q�b�g�t���O
	float						timer = 0.0f;	//�^�C�}�[
};

extern Block* block;