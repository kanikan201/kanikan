/*
	���U���g���
*/

#pragma once
#include "Interface/Number.h"
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
	
	void Init();
private:
	CSprite		sprite;		//�X�v���C�g
	CTexture	texture;	//�e�N�X�`��
	CSoundSource* bgm;

	CSprite		m_colon;
	CTexture	m_colonTex;

	CSprite		 m_Str;		//HP�o�[�̔w�i�B
	CTexture	m_StrTex;		//HP�o�[�̔w�i�̃e�N�X�`��

	Number*		num[4];
};

