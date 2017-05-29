/*
	�^�C���\��
*/
#include "Number.h"
#pragma once
class DisplayTime : public IGameObject
{
public:
	DisplayTime();
	~DisplayTime();
	bool Start() override;
	void Update() override;
	void DeleteNum();
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_Str;		//����
	CTexture	m_StrTex;	//�����̃e�N�X�`��

	CSprite		m_colon;
	CTexture	m_colonTex;

	Number*		num[4];		//����
};

