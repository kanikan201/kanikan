#pragma once

#include "tkEngine/character/tkCharacterController.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start() override;
	void Update() override;
	void SetPosition(CVector3 pos);

	void Render(CRenderContext& renderContext) override;

private:
	CSprite			sprite;		//�X�v���C�g
	CTexture		texture;	//�e�N�X�`��

	CSkinModel					skinModel;					//�X�L�����f��
	CSkinModelDataHandle		skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController		characterController;		//�L�����N�^�\�R���g���[���[

	CVector3			position = CVector3::Zero;			//�v���C���[�̍��W
	CQuaternion			rotation = CQuaternion::Identity;	//��]

	CQuaternion			qRotX, qRotY, View;
	CVector3			toLightPos;
	CAnimation			animation;				//�A�j���[�V�����B
	int					Run = 2;				//�A�j���[�V�����i���o�[�B2�͑��郂�[�V�����B

	CCamera				camera;					//���j�e�B�����J�����B
};

