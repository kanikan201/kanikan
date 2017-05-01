/*
	ゲームオーバー画面
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
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ
	CSoundSource* bgmsource;
};

