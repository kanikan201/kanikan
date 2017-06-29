/*
�X�v���C�g�\���p�N���X
*/

#pragma once

class ShowSprite : public IGameObject
{
public:
	ShowSprite();
	~ShowSprite();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite				sprite;			//�X�v���C�g
	CTexture			texture;		//�e�N�X�`��
	float timer;
};

