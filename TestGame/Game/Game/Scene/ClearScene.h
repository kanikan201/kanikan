#pragma once
class ClearScene : public IGameObject
{
public:
	ClearScene();
	~ClearScene();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite			sprite;		//スプライト
	CTexture		texture;	//テクスチャ
};

