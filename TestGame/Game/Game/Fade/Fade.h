/*!
*@brief	��ʂ̃t�F�[�h�A�E�g/�C��
*/

#pragma once

class Fade : public IGameObject {
public:
	Fade();
	~Fade();
	
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

	//�t�F�[�h�A�E�g����?
	bool IsExecute() const
	{
		return m_isExecute;
	}

	//�t�F�[�h�A�E�g�J�n
	void StartFadeOut()
	{
		m_timer = 0.0f;
		SetActiveFlag(true);
		m_isExecute = true;
		m_state = eFadeOut;
	}

	//�t�F�[�h�C���J�n
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
	//��ԁB
	enum EnState {
		eFadeOut,	//�t�F�[�h�A�E�g
		eFadeIn,	//�t�F�[�h�C��
	};
	const float		FADE_TIME = 0.15f;		//�t�F�[�h����(�P�ʁF�b)
	CSprite			m_sprite;				//�t�F�[�h����X�v���C�g
	CTexture		m_texture;				//�t�F�[�h����e�N�X�`��
	EnState			m_state = eFadeIn;		//���
	bool			m_isExecute = false;	//�t�F�[�h���s����
	float			m_timer = 1.0f;			//�^�C�}(�P�ʁF�b)
};
extern Fade* g_fade;