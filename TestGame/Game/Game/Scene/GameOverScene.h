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

	//選択状態
	enum State {
		enContinue,
		enEnd,
	};

	//選択決定したか
	bool GetChoice(){
		return isChoice;
	}

	//状態を取得
	State GetState() {
		return state;
	}

private:

	CSprite			sprite;		//スプライト
	CTexture		texture;	//テクスチャ

	CSprite			continue1;
	CSprite			continue2;
	CSprite			end1;
	CSprite			end2;

	CTexture		con1Tex;
	CTexture		con2Tex;
	CTexture		end1Tex;
	CTexture		end2Tex;

	CSoundSource*	bgmSource = nullptr;;
	bool			isChoice;
	State			state;
};

