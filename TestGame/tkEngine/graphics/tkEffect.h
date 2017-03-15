/*!
 * @brief	�V�F�[�_�[�G�t�F�N�g�B
 */
 
#ifndef _TKEFFECT_H_
#define _TKEFFECT_H_

#include "tkEngine/graphics/tkTexture.h"

namespace tkEngine{
	/*!
	 * @brief	�V�F�[�_�[�G�t�F�N�g�B
	 */
	class CEffect{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CEffect(ID3DXEffect* effect);
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CEffect();
		/*!
		*@brief	�e�N�j�b�N��ݒ�B
		*@param[in]	parameterName	�p�����[�^�̖��O�B
		*@param[in]	pData			�ݒ肷��l�B
		*@param[in]	sizeInByte		�T�C�Y(�P�ʁF�o�C�g)
		*/
		void SetTechnique(tkEngine::CRenderContext& renderContext, const char* tecName)
		{
			TK_ASSERT(tecName != nullptr, "tecName is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectSetTechnique(renderContext, m_pEffect,tecName));
		}
		/*!
		 * @brief	�l��ݒ�B
		 *@param[in]	parameterName	�p�����[�^�̖��O�B
		 *@param[in]	pData			�ݒ肷��l�B
		 *@param[in]	sizeInByte		�T�C�Y(�P�ʁF�o�C�g)
		 */
		void SetValue(tkEngine::CRenderContext& renderContext, const char* parameterName, const void* pData, int sizeInByte )
		{
			TK_ASSERT( m_pEffect != nullptr, "effect is null" );
			renderContext.SetRenderCommand( CRenderCommand_EffectSetValue(renderContext, m_pEffect, parameterName, pData, sizeInByte ) );
		}
		void SetTexture(tkEngine::CRenderContext& renderContext, const char* parameterName, const CTexture* tex)
		{
			renderContext.SetRenderCommand(CRenderCommand_EffectSetTexture(renderContext, m_pEffect, parameterName, tex ));
		}
		/*!
		 * @brief	�e�N�j�b�N�̓K�p���J�n�B
		 */
		void Begin(tkEngine::CRenderContext& renderContext)
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectBegin(m_pEffect));
		}
		/*!
		 * @brief	�e�N�j�b�N�̓K�p���I���B
		 */
		void End(tkEngine::CRenderContext& renderContext)
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectEnd(m_pEffect));
		}
		/*!
		 * @brief	�g�p����e�N�j�b�N�̃p�X��ݒ肵�ĕ`��J�n�B
		 */
		void BeginPass(tkEngine::CRenderContext& renderContext, int pass )
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectBeginPass(m_pEffect, pass));
		}
		/*!
		 * @brief	�`��I���B
		 */
		void EndPass(tkEngine::CRenderContext& renderContext)
		{
			renderContext.SetRenderCommand(CRenderCommand_EffectEndPass(m_pEffect));
		}
		/*!
		* @brief	ID3DXEffect::CommitChanges�Ɠ����B
		*/
		void CommitChanges(CRenderContext& renderContext)
		{
			renderContext.SetRenderCommand(CRenderCommand_EffectCommitChanges(m_pEffect));
		}
		ID3DXEffect* GetD3DXEffect()
		{
			return m_pEffect;
		}
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		/*!
		* @brief	�t�@�C���p�X��ݒ�B
		*/
		void SetFilePath(const char* filePath)
		{
			this->filePath = filePath;
		}
		
#endif
		void Update();
		/*!
		* @brief	�����[�h�����������H
		*/
		bool IsReloadTrigger() const
		{
			return m_isReloadTrigger;
		}
	private:
		bool			m_isReloadTrigger = false;	//!<�����[�h�����������H
		ID3DXEffect*	m_pEffect;		//!<D3D�G�t�F�N�g
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		std::string filePath;			//���̃G�t�F�N�g�t�@�C���̃t�@�C�c�p�X�B
		FILETIME fLastWriteTime;		//�ŏI�������ݎ��ԁB
		HANDLE	 hFile = NULL;			//�t�@�C���n���h���B
#endif
	};
}

#endif 
