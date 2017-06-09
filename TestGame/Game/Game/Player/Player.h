#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/Sound/tkSoundSource.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Reset();
	void SetPosition(CVector3 pos);
	void Render(CRenderContext& renderContext);
	float Distance(CVector3& objectPos);	//�v���C���[�Ƃ̋�����Ԃ�

//�v���C���[�̈ʒu��Ԃ�
	CVector3 GetPosition() {
		return position;
	}

//�����擾
	CVector3 GetMoveAngle() {
		return dir;
	}

//���[�V����
	enum AnimationNo {
		AnimationStand,		//����
		AnimationWalk,		//����
		AnimationRun,		//����
		AnimationJump,		//�W�����v
	};

private:
	CVector3 Move();
	CTexture	darkTex;


	CSkinModel					skinModel;					//�X�L�����f��
	CSkinModelDataHandle		skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController		characterController;		//�L�����N�^�\�R���g���[���[

	CVector3			position = CVector3::Zero;			//�v���C���[�̍��W
	CQuaternion			rotation = CQuaternion::Identity;	//��]
	CVector3			dir = { 0.0f,0.0f,1.0f };			//����

	CVector3			toLightPos;

	CAnimation			animation;				//�A�j���[�V�����B
	AnimationNo			currentAnimSetNo;		//���̃��[�V����
	AnimationNo			prevAnim;				//�ύX�O�̃��[�V����

	float				timer = 0.0f;		//�^�C�}�[�B
};