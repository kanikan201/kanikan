/*
	タイム表示
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
	CSprite		 m_Str;		//文字
	CTexture	m_StrTex;	//文字のテクスチャ

	CSprite		m_colon;
	CTexture	m_colonTex;

	Number*		num[4];		//数字
};

