/*!
*@brief	画面のフェードアウト/イン
*/

#pragma once

class Fade : public IGameObject {
public:
	Fade();
	~Fade();
	
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

	//フェードアウト中か?
	bool IsExecute() const
	{
		return m_isExecute;
	}

	//フェードアウト開始
	void StartFadeOut()
	{
		m_timer = 0.0f;
		SetActiveFlag(true);
		m_isExecute = true;
		m_state = eFadeOut;
	}

	//フェードイン開始
	void StartFadeIn()
	{
		if (m_sprite.GetAlpha() > 0.0f) {
			m_timer = 0.0f;
			SetActiveFlag(true);
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}
private:
	//状態。
	enum EnState {
		eFadeOut,	//フェードアウト
		eFadeIn,	//フェードイン
	};
	const float		FADE_TIME = 0.2f;		//フェード時間(単位：秒)
	CSprite			m_sprite;				//フェードするスプライト
	CTexture		m_texture;				//フェードするテクスチャ
	EnState			m_state = eFadeIn;		//状態
	bool			m_isExecute = false;	//フェード実行中か
	float			m_timer = 1.0f;			//タイマ(単位：秒)
};
extern Fade* g_fade;