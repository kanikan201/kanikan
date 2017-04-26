/*!
*@brief	タイトルシーン。
*/

#pragma once
#include "stdafx.h"

class TitleScene : public IGameObject
{
public:
	TitleScene();
	~TitleScene();
	bool Start() override;
	void Update() override;
	void PostRender( CRenderContext& renderContext ) override;
private:
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ
	CSoundSource* bgm;
};

