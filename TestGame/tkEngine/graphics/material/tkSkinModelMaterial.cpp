/*!
 *@brief	�X�L�����f���}�e���A���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/material/tkSkinModelMaterial.h"

#include "tkEngine/graphics/material/node/tkSkinModelMaterialNode.h"


namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CSkinModelMaterial::CSkinModelMaterial()
	{
		memset(m_textures, 0, sizeof(m_textures));
		for (auto& m : m_matrices) {
			m = CMatrix::Identity;
		}
		for (auto& v : m_fVector) {
			v = CVector3::Zero;
		}
		for (auto& v : m_iVector) {
			v.x = 0;
			v.y = 0;
			v.z = 0;
			v.w = 0;
		}
		memset(m_int, 0, sizeof(m_int));
	}
	CSkinModelMaterial::~CSkinModelMaterial()
	{

	}
	void CSkinModelMaterial::Init(const char* tecName, const char* matName)
	{
		m_pEffect = EffectManager().LoadEffect("Assets/presetShader/skinModel.fx");
		m_materialName = matName;
		InitShaderHandles(tecName);
	}
	void CSkinModelMaterial::InitShaderHandles(const char* tecName)
	{
		if (m_pEffect) {
			ID3DXEffect* effectDx = m_pEffect->GetD3DXEffect();
			//�e�N�X�`���̃V�F�[�_�[�n���h���B
			m_hTexShaderHandle[enTextureShaderHandle_DiffuseMap] = effectDx->GetParameterByName(NULL, "g_diffuseTexture");
			m_hTexShaderHandle[enTextureShaderHandle_NormalMap] = effectDx->GetParameterByName(NULL, "g_normalTexture");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_0] = effectDx->GetParameterByName(NULL, "g_shadowMap_0");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_1] = effectDx->GetParameterByName(NULL, "g_shadowMap_1");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_2] = effectDx->GetParameterByName(NULL, "g_shadowMap_2");
			m_hTexShaderHandle[enTextureShaderHandle_SpecularMap] = effectDx->GetParameterByName(NULL, "g_speculerMap");
			m_hTexShaderHandle[enTextureShaderHandle_SkyCubeMap] = effectDx->GetParameterByName(NULL, "g_skyCubeMap");
			m_hTexShaderHandle[enTextureShaderHandle_SplatMap] = effectDx->GetParameterByName(NULL, "g_splatMap");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainTex0] = effectDx->GetParameterByName(NULL, "g_terrainTex0");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainTex1] = effectDx->GetParameterByName(NULL, "g_terrainTex1");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainTex2] = effectDx->GetParameterByName(NULL, "g_terrainTex2");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainTex3] = effectDx->GetParameterByName(NULL, "g_terrainTex3");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainNormalMap0] = effectDx->GetParameterByName(NULL, "g_terrainNormalMap0");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainNormalMap1] = effectDx->GetParameterByName(NULL, "g_terrainNormalMap1");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainNormalMap2] = effectDx->GetParameterByName(NULL, "g_terrainNormalMap2");
			m_hTexShaderHandle[enTextureShaderHandle_TerrainNormalMap3] = effectDx->GetParameterByName(NULL, "g_terrainNormalMap3");

			//�s��̃V�F�[�_�[�n���h���B
			m_hMatrixShaderHandle[enMatrixShaderHandle_LastFrameViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProjLastFrame");
			m_hMatrixShaderHandle[enMatrixShaderHandle_ViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProj");
			m_hMatrixShaderHandle[enMatrixShaderHandle_LVP] = effectDx->GetParameterByName(NULL, "g_mLVP");
			m_hMatrixShaderHandle[enMatrixShaderHandle_WorldMatrix] = effectDx->GetParameterByName(NULL, "g_worldMatrix");
			//���������x�N�g���̃V�F�[�_�[�n���h���B
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraPos] = effectDx->GetParameterByName(NULL, "g_cameraPos");
			m_hFVectorShaderHandle[enFVectorShaderHandle_FogParam] = effectDx->GetParameterByName(NULL, "g_fogParam");
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraDir] = effectDx->GetParameterByName(NULL, "g_cameraDir");
			m_hFVectorShaderHandle[enFVectorShaderHandle_TerrainRect] = effectDx->GetParameterByName(NULL, "g_terrainRect");

			//�����x�N�g���̃V�F�[�_�[�n���h���B
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags] = effectDx->GetParameterByName(NULL, "g_flags");
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags2] = effectDx->GetParameterByName(NULL, "g_flags2");
			//�����̃V�F�[�_�[�n���h���B
			m_hIntShaderHandle[enIntShaderHandle_NumBone] = effectDx->GetParameterByName(NULL, "g_numBone");
			m_hIntShaderHandle[enIntshaderHandle_CurNumBone] = effectDx->GetParameterByName(NULL, "CurNumBones");
			//��C�����̃V�F�[�_�[�n���h���B
			m_hAtmosShaderHandle = effectDx->GetParameterByName(NULL, "g_atmosParam");
			//���C�g�̃V�F�[�_�[�n���h���B
			m_hLightShaderHandle = effectDx->GetParameterByName(NULL, "g_light");
			//�V���h�E���V�[�o�[�p�����[�^�n���h���B
			m_hShadowRecieverParamShaderHandle = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");
			//�{�[���s��̃V�F�[�_�[�n���h���B
			m_hBoneMatrixArrayShaderHandle = effectDx->GetParameterByName(NULL, "g_mWorldMatrixArray");

			//�V�F�[�_�[�e�N�j�b�N�B
			m_hTechniqueHandle[enTecShaderHandle_SkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("SkinModelInstancingRenderToShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_SkinModelInstancing] = effectDx->GetTechniqueByName("SkinModelInstancing");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("NoSkinModelInstancingRenderToShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelInstancing] = effectDx->GetTechniqueByName("NoSkinModelInstancing");
			m_hTechniqueHandle[enTecShaderHandle_SkinModelRenderShadowMap] = effectDx->GetTechniqueByName("SkinModelRenderShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_SkinModel] = effectDx->GetTechniqueByName("SkinModel");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelRenderShadowMap] = effectDx->GetTechniqueByName("NoSkinModelRenderShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModel] = effectDx->GetTechniqueByName("NoSkinModel");
			m_hTechniqueHandle[enTecShaderHandle_Sky] = effectDx->GetTechniqueByName("Sky");
			m_hTechniqueHandle[enTecShaderHandle_Terrain] = effectDx->GetTechniqueByName("Terrain");
			m_hTechniqueHandle[enTecShaderHandle_Toon] = effectDx->GetTechniqueByName("Toon");
			m_hTechniqueHandle[enTecShaderHandle_ToonNonSkin] = effectDx->GetTechniqueByName("ToonNonSkin");
			//����������Standard�}�e���A�����\�z����B
			Build(enTypeStandard);
		}
	}
	/*!
	 *@brief	�}�e���A�����\�z�B
	 */
	void CSkinModelMaterial::Build(EnType type)
	{
		m_materialNodes.clear();
		switch(type){
		case enTypeToonNonSkin:
			//�s��B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLastFrameViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLVP(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendWorldMatrix(this)));
			//�e�N�X�`���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendDiffuseMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_0(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_1(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_2(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendNormalMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendSpecularMap(this)));
			//���������_�x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraPos(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFogParam(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraDir(this)));

			//�����x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags2(this)));

			//�����B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_NumBone(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_CurNumBone(this)));
			SetTechnique(enTecShaderHandle_ToonNonSkin);
			break;
		case enTypeToon:
			//�s��B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLastFrameViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLVP(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendWorldMatrix(this)));
			//�e�N�X�`���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendDiffuseMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_0(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_1(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_2(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendNormalMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendSpecularMap(this)));
			//���������_�x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraPos(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFogParam(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraDir(this)));

			//�����x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags2(this)));

			//�����B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_NumBone(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_CurNumBone(this)));

			SetTechnique(enTecShaderHandle_Toon);
			break;
		case enTypeStandard:
			//�X�^���_�[�h�B
			//�s��B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLastFrameViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLVP(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendWorldMatrix(this)));
			//�e�N�X�`���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendDiffuseMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_0(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_1(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendShadowMap_2(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendNormalMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendSpecularMap(this)));
			//���������_�x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraPos(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFogParam(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraDir(this)));

			//�����x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags2(this)));

			//�����B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_NumBone(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_CurNumBone(this)));

			SetTechnique(enTecShaderHandle_SkinModel);
			break;
		case enTypeTerrain:
			//�n�`�B
			//�s��B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLastFrameViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLVP(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendWorldMatrix(this)));
			//�x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraPos(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainRect(this)));
			//�e�N�X�`���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendSplatMap(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainTex0(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainTex1(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainTex2(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainTex3(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainNormalMap0(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainNormalMap1(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainNormalMap2(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendTerrainNormalMap3(this)));
			//�����x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags2(this)));

			SetTechnique(enTecShaderHandle_Terrain);
			break;
		case enTypeSky:
			//��B
			//�s��B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLastFrameViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendViewProj(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendLVP(this)));
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendWorldMatrix(this)));
			//�e�N�X�`���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendSkyCubeMap(this)));
			//�x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendCameraPos(this)));
			//�����x�N�g���B
			m_materialNodes.push_back(ISkinModelMaterialNodePtr(new CSkinModelMaterialNode_SendFlags2(this)));
			SetTechnique(enTecShaderHandle_Sky);
			break;
		default:
			TK_ASSERT(false, "�s���ȃ}�e���A�����\�z���悤�Ƃ��Ă��܂��B");
			break;
		}
	}
	void CSkinModelMaterial::BeginDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(!m_isBeginDraw, "forgot call EndDraw!!!!");
		m_isBeginDraw = true;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->SetTechnique(m_hTec);
			effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			effect->BeginPass(0);
		}
	}
	void CSkinModelMaterial::SendMaterialParamToGPU()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
#endif
		if (m_pEffect) {
			m_pEffectRaw = m_pEffect->GetD3DXEffect();
			//���傢�K��

			m_pEffectRaw->SetValue(m_hLightShaderHandle, &m_light, sizeof(m_light));
			m_pEffectRaw->SetValue(m_hAtmosShaderHandle, &m_atmosParam, sizeof(m_atmosParam));
			m_pEffectRaw->SetValue(m_hShadowRecieverParamShaderHandle, &m_shadowRecParam, sizeof(m_shadowRecParam));
			m_pEffectRaw->SetMatrixArray(m_hBoneMatrixArrayShaderHandle, m_boneMatrixArray, m_boneMatrixArraySize);
			for (auto& node : m_materialNodes) {
				node->SendMaterialParamToGPU();
			}

			m_pEffectRaw->CommitChanges();
			m_pEffectRaw = nullptr;
		}
	}
	void CSkinModelMaterial::EndDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
		m_isBeginDraw = false;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->EndPass();
			effect->End();
		}
	}
}