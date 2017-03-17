#include "stdafx.h"
#include "Fade.h"


Fade::Fade(){}
Fade::~Fade(){}

bool Fade::Start()
{
	//テクスチャロード
	m_texture.Load("Assets/sprite/loding.png");
	m_sprite.Init(&m_texture);

	//サイズ設定
	m_sprite.SetSize({
		static_cast<float>(Engine().GetFrameBufferWidth()),
		static_cast<float>(Engine().GetFrameBufferHeight()) });
	SetActiveFlag(false);	//動かない
	return true;
}
void Fade::Update()
{
	//フェード実行中
	if (m_isExecute) {
		switch (m_state) {

		//フェードアウト中
		case eFadeOut: {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				//透明度
				m_sprite.SetAlpha(min(t, 1.0f));
			}
			else {
				m_isExecute = false;
				m_sprite.SetAlpha(1.0f);
			}
		}break;

		//フェードイン中
		case eFadeIn:
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//透明になったので非アクティブにする。
				m_sprite.SetAlpha(0.0f);
				SetActiveFlag(false);
				m_timer = FADE_TIME;
				m_isExecute = false;
			}
			break;
		}
	}
}
void Fade::PostRender(CRenderContext& renderContext)
{
	m_sprite.Draw(renderContext);
}
