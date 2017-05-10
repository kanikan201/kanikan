/*!
 * @brief	�|�X�g�G�t�F�N�g
 */

#ifndef _TKPOSTEFFECT_H_
#define _TKPOSTEFFECT_H_

#include "tkEngine/graphics/postEffect/tkEdgeRender.h"
#include "tkEngine/graphics/postEffect/tkBloomRender.h"
#include "tkEngine/graphics/postEffect/tkDOF.h"
#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/postEffect/tkMotionBlur.h"
#include "tkEngine/graphics/postEffect/tkMonochromeFilter.h"
#include "tkEngine/graphics/postEffect/tkSepiaFilter.h"
#include "tkEngine/graphics/postEffect/tkTonemap.h"

namespace tkEngine{
	/*!
	 * @brief	�|�X�g�G�t�F�N�g�B
	 */
	class CPostEffect{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPostEffect();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPostEffect();
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		 * @brief
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		* @brief	�`��B
		*/
		void Render(CRenderContext& renderContext);
		/*!
		* @brief	�t���X�N���[���`��B
		*/
		void RenderFullScreen(CRenderContext& renderContext);
		/*!
		* @brief	DOF���擾�B
		*/
		CDof& GetDof()
		{
			return m_dof;
		}
		/*!
		* @brief	���[�V�����u���[���擾�B
		*/
		CMotionBlur& GetMotionBlur()
		{
			return m_motionBlur;
		}
		/*!
		* @brief	�g�[���}�b�v���擾�B
		*/
		CTonemap& GetTonemap()
		{
			return m_tonemap;
		}
		CMonochromeFilter& GetMonochromeFilter()
		{
			return m_monochromeFilter;
		}
		CSepiaFilter& GetSepiaFilter()
		{
			return m_sepiaFilter;
		}
	private:
		CEdgeRender			m_edgeRender;		//!<�G�b�W�`��B
		CBloomRender		m_bloomRender;		//!<Bloom�B
		CDof				m_dof;				//!<��ʊE�[�x
		CFxaa				m_fxaa;				//!<FXAA
		CMotionBlur			m_motionBlur;		//!<���[�V�����u���[�B
		CMonochromeFilter	m_monochromeFilter;	//!<���m�N���t�B���^�B
		CSepiaFilter		m_sepiaFilter;		//!<�Z�s�A�t�B���^�B
		CTonemap			m_tonemap;			//!<�g�[���}�b�v�B
		CPrimitive		m_fullscreenRenderPrim;	//!<�t���X�N���[���������_�����O���邽�߂̃v���~�e�B�u�B
	};
}

#endif // _TKPOSTEFFECT_H_
