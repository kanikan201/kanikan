/*!
 * @brief	���m�N���t�B���^�[�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkMonochromeFilter.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CMonochromeFilter::CMonochromeFilter()
	{
		
	}
	CMonochromeFilter::~CMonochromeFilter()
	{
	}
	void CMonochromeFilter::Create(const SGraphicsConfig& config)
	{
		m_effect = EffectManager().LoadEffect("Assets/presetShader/monochromeFilter.fx");
	}
	void CMonochromeFilter::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		if(m_isEnable){
			
			//�����_�����O�^�[�Q�b�g��؂�ւ��B
			Engine().ToggleMainRenderTarget();
			//Z�o�b�t�@�����N���A���邽�߂̃����_�����O�^�[�Q�b�g���쐬�B
			m_clearRenderTarget.SetSurfaceDX(nullptr);
			m_clearRenderTarget.SetDepthSurfaceDX(Engine().GetMainRenderTarget().GetDepthSurfaceDx());
			renderContext.SetRenderTarget(0, &m_clearRenderTarget);
			//Z�o�b�t�@���N���A�B
			renderContext.Clear(0, nullptr, D3DCLEAR_ZBUFFER, 0, 0.0f, 0);
			renderContext.SetRenderState(RS_ZWRITEENABLE, TRUE);
			renderContext.SetRenderState(RS_ZENABLE, TRUE);
			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_GREATEREQUAL);
			//Z�}�X�N�������_�����O�B
			for (auto func : maskModelsFunc) {
				(*func)(renderContext);
			}
			maskModelsFunc.clear();

			CPIXPerfTag tag(renderContext, L"CMonochromeFilter::Render");
			float texSize[] = {
				s_cast<float>(Engine().GetMainRenderTarget().GetWidth()),
				s_cast<float>(Engine().GetMainRenderTarget().GetHeight())
			};
			m_effect->SetTechnique(renderContext, "Default");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
			m_effect->SetValue(renderContext, "g_blendRate", &m_blendRate, sizeof(m_blendRate));
			m_effect->CommitChanges(renderContext);

			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_EQUAL);
			renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
			postEffect->RenderFullScreen(renderContext);
			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_LESSEQUAL);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
		}
	}
	

}