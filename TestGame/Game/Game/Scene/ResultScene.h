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

	CSprite		m_colon;	//コロン
	CTexture	m_colonTex;	//コロンのテクスチャ

	CSprite		m_Str;		//文字
	CTexture	m_StrTex;	//文字のテクスチャ

	Number*		num[4];	//数字

	CSoundSource* bgm;
};

