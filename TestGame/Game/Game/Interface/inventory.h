/*
	アイテムインベントリ
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
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ
};

