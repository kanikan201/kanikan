/*!
 * @brief	���[�V�����u���[�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkMotionBlur.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CMotionBlur::CMotionBlur()
	{
	}
	CMotionBlur::~CMotionBlur()
	{
	}
	void CMotionBlur::Create(const SGraphicsConfig& config)
	{
		if (config.motionBlurConfig.isEnable) {
			//DOF���L���B
			m_isEnable = config.motionBlurConfig.isEnable;
			//DOF�̓��C�������_�����O�^�[�Q�b�g�ɏ������ނƂ���MRT���g�p���ď������ނ̂ŁA
			//���C���Ɠ������ƍ����B
			int w = Engine().GetFrameBufferWidth();
			int h = Engine().GetFrameBufferHeight();
			//16bit�B
			m_velocityMapRT.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);
			m_effect = EffectManager().LoadEffect("Assets/presetShader/motionBlur.fx");
			m_isInited = true;
		}
	}
	void CMotionBlur::Render(CRenderContext& renderContext, CPostEffect* postEffect)
	{
		if (m_isEnable && m_isInited) {
			CPIXPerfTag tag(renderContext, L"CMotionBlur::Render");
			m_effect->SetTechnique(renderContext, "MotionBlur");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->SetTexture(renderContext, "g_velocityTexture", m_velocityMapRT.GetTexture());
			float texSize[] = {
				s_cast<float>(Engine().GetMainRenderTarget().GetWidth()),
				s_cast<float>(Engine().GetMainRenderTarget().GetHeight()),
			};
			m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
			m_effect->CommitChanges(renderContext);

			Engine().ToggleMainRenderTarget();
			renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());

			postEffect->RenderFullScreen(renderContext);

			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
		}
	}
}
