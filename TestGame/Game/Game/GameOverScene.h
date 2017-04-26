/*
	�Q�[���I�[�o�[���
*/

#pragma once
class GameOverScene : public IGameObject
{
public:
	GameOverScene();
	~GameOverScene();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		sprite;		//�X�v���C�g
	CTexture	texture;	//�e�N�X�`��
};

