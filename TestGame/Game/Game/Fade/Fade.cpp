#include "stdafx.h"
#include "Fade.h"


Fade::Fade(){}
Fade::~Fade(){}

bool Fade::Start()
{
	//�e�N�X�`�����[�h
	m_texture.Load("Assets/sprite/loding.png");
	m_sprite.Init(&m_texture);

	//�T�C�Y�ݒ�
	m_sprite.SetSize({
		static_cast<float>(Engine().GetFrameBufferWidth()),
		static_cast<float>(Engine().GetFrameBufferHeight()) });
	SetActiveFlag(false);	//�����Ȃ�
	return true;
}
void Fade::Update()
{
	//�t�F�[�h���s��
	if (m_isExecute) {
		switch (m_state) {

		//�t�F�[�h�A�E�g��
		case eFadeOut: {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				//�����x
				m_sprite.SetAlpha(min(t, 1.0f));
			}
			else {
				m_isExecute = false;
				m_sprite.SetAlpha(1.0f);
			}
		}break;

		//�t�F�[�h�C����
		case eFadeIn:
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//�����ɂȂ����̂Ŕ�A�N�e�B�u�ɂ���B
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
