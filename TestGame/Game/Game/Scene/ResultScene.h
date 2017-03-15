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
	CSoundSource* bgmSource = NULL;

	CSprite sprite;
	CTexture texture;
};

