/*!
 * @brief	���m�N���t�B���^�[�B
 */

#pragma once

namespace tkEngine{
	class CPostEffect;
	typedef void(*DrawSkinModelMaskFunc)(CRenderContext& renderContext);
	/*!
	 * @brief	���m�N���t�B���^
	 */
	class CMonochromeFilter{
	public:
		CMonochromeFilter();
		~CMonochromeFilter();
		void Render( CRenderContext& renderContext, CPostEffect* postEffect );
		void Create(const SGraphicsConfig& config );
		void SetEnalbe(bool flag) {
			m_isEnable = flag;
		}
		void SetBlendRate(float rate)
		{
			m_blendRate = rate;
		}
		float GetBlendRate() const
		{
			return m_blendRate;
		}
		void RegistMaskSkinModel(DrawSkinModelMaskFunc pFunc)
		{
			maskModelsFunc.push_back(pFunc);
		}
	private:
		CEffect*	m_effect = nullptr;
		bool		m_isEnable = false;
		float		m_blendRate = 0.0f;	//�u�����h���B1.0�Ŋ��S�Ƀ��m�N���ɂȂ�܂��B
		std::vector<DrawSkinModelMaskFunc>	maskModelsFunc;		//�}�X�N���f���B
		CRenderTarget m_clearRenderTarget;
	};
}
