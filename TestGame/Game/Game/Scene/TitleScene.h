/*!
*@brief	�^�C�g���V�[���B
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
	CSprite		sprite;		//�X�v���C�g
	CTexture	texture;	//�e�N�X�`��
	CSoundSource* bgm;
};

