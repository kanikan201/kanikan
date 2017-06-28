/*
スプライト表示用クラス
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
	CSprite				sprite;			//スプライト
	CTexture			texture;		//テクスチャ
	float timer;
};

