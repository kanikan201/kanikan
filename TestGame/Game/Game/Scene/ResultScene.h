/*
	リザルト画面
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
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ
	CSoundSource* bgm;
};

