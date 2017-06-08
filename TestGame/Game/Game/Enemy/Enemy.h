/*
	�G�̊�{�N���X
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Init(CVector3 FirstPosition);
	void Update();
	void Render(CRenderContext& renderContext);
	void Damage();

protected:
	virtual void Move();	//����

	//���[�V����(��)
	enum AnimationNo {
		AnimationStand,		//����
		AnimationWalk,		//����
		AnimationAttack,	//�U��
	};

	CAnimation			animation;			//�A�j���[�V�����B
	AnimationNo			currentAnimSetNo;	//���̃��[�V����
	AnimationNo			prevAnim;			//�ύX�O�̃��[�V����

	enum EState {
		eState_Search,	//�T�����
		eState_Find,	//�������
	};

	EState		Estate = eState_Search;		//�G�̏��

	char filePath[256];	//�t�@�C���p�X

	struct Status
	{
		int					hp;		//�̗�
		int					score;	//�|�����Ƃ��̃X�R�A
	};

	CSkinModel				skinModel;					//�X�L�����f��
	CSkinModelDataHandle	skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[

	CVector3				position;					//�G�̍��W
	CVector3				centralPos;					//�G�̒��S�̍��W
	const CVector3			central = { 0.0f, 1.8f,0.0f };	//�G�̒��S�̍���

	CVector3				move = CVector3::Zero;
	CQuaternion				rotation = CQuaternion::Identity;	//��]

	//CAnimation		animation;			//�A�j���[�V�����B
	//AnimationNo		currentAnimSetNo;	//���̃��[�V����
	//AnimationNo		anim;				//�ύX�O�̃��[�V����

	Status state;	//�G�̃X�e�[�^�X

	float		length = 0.0f;	//�v���C���[�Ƃ̋���
	float		m_timer = 0.0f;
	float		start;
	bool isMoving = false;
	CTexture	darkTex;
};