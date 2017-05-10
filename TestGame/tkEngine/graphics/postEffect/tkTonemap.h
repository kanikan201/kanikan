/*!
 *@brief	�g�[���}�b�v�B
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	�g�[���}�b�v�B
	 */
	class CTonemap{
	public:
		CTonemap();
		~CTonemap();
		/*!
		*@brief	�쐬�B
		*@param[in]		config		�O���t�B�b�N�ݒ�B
		*/
		void Create(const SGraphicsConfig& config);
		/*!
		 *@brief	���ϋP�x�̌v�Z�B
		 *@param[in]	renderContext		�����_�����O�R���e�L�X�g
		 */
		void CalcLuminanceAvarage(CRenderContext& renderContext, CPostEffect* postEffect);
		/*!
		 *@brief	�g�[���}�b�v�̎��s�B
		 *@details
		 * ���̊֐����ĂԑO��CalcLuminanceAvarage���R�[�����ĕ��ϋP�x�̌v�Z���s���Ă��������B
		 * ���ϋP�x�̌v�Z�̓|�X�g�G�t�F�N�g�̐퓬�ōs���Ă��������B
		 *@param[in]	renderContext		�����_�����O�R���e�L�X�g
		 */
		void Execute(CRenderContext& renderContext, CPostEffect* postEffect);
		/*!
		*@brief	�g�[���}�b�v�̏��������Z�b�g�B
		*@details
		*�@�P�x���傫���ς��V�[���؂�ւ��Ȃǂ���������ꍇ�Ȃǂɖ��Ï�������������������ꍇ������܂��B
		* ���̂悤�ȏꍇ�̓V�[���؂�ւ��̃^�C�~���O�Ń��Z�b�g���s���Ă݂Ă��������B
		*/
		void Reset()
		{
			m_isFirstWhenChangeScene = true;
		}
	private:
		static const int NUM_CALC_AVG_RT = 5;				//!<���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�̖����B
		CEffect*		m_effect = nullptr;					//!<�G�t�F�N�g�B
		bool			m_isEnable = false;					//!<�g�[���}�b�v�L���H
		CRenderTarget	m_calcAvgRT[NUM_CALC_AVG_RT];		//!<���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�B
		CRenderTarget   m_avgRT[2];							//!<���ϋP�x���i�[����郌���_�����O�^�[�Q�b�g�B
		int				m_currentAvgRT = 0;					//!<
		float			m_fMiddleGray = 0.22f;				//!<���̒l��傫������Ɩ��邭�Ȃ�B
		bool			m_isFirstWhenChangeScene = true;	//!<�V�[�����؂�ւ���ď���̕`�悩�ǂ����̃t���O�B
	};
}