/*
	�A�C�e���C���x���g��
*/

#pragma once
class inventory : public IGameObject
{
public:
	inventory();
	~inventory();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		sprite;		//�X�v���C�g
	CTexture	texture;	//�e�N�X�`��
};

