/*
	リザルト画面
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
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ
	CSoundSource* bgm;

	CSprite		m_colon;
	CTexture	m_colonTex;

	CSprite		 m_Str;		//HPバーの背景。
	CTexture	m_StrTex;		//HPバーの背景のテクスチャ

	Number*		num[4];
};

