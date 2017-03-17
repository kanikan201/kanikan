/*
	���U���g���
*/

#pragma once
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		sprite;		//�X�v���C�g
	CTexture	texture;	//�e�N�X�`��
};

