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

	enum State {
		enContinue,
		enEnd,
	};

	bool GetChoice() {
		return isChoice;
	}
	State GetState() {
		return state;
	}
private:
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ

	CSprite			continue1;
	CSprite			continue2;
	CSprite			end1;
	CSprite			end2;

	CTexture		con1Tex;
	CTexture		con2Tex;
	CTexture		end1Tex;
	CTexture		end2Tex;

	CSoundSource* bgm;
	bool			isChoice;
	State			state;
};

