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

	CSprite		m_colon;	//�R����
	CTexture	m_colonTex;	//�R�����̃e�N�X�`��

	CSprite		m_Str;		//����
	CTexture	m_StrTex;	//�����̃e�N�X�`��

	Number*		num[4];	//����

	CSoundSource* bgm;
};

