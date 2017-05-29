/*!
 *@brief	�X�L�����f���}�e���A���B
 */

#pragma once

#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	class ISkinModelMaterialNode;
	/*!
	 *@brief	�X�L�����f���}�e���A���B
	 */
	class CSkinModelMaterial
	{
	public:
		/*!
		 *@brief	�}�e���A���̎�ށB
		 */
		enum EnType{
			enTypeStandard,		//!<�X�^���_�[�h�B
			enTypeTerrain,		//!<�n�`�B
			enTypeSky,			//!<��B
			enTypeToon,			//!<�g�D�[��
			enTypeToonNonSkin,
		};
		/*!
		*@brief	�e�N�X�`���̃V�F�[�_�[�n���h���B
		*/
		enum EnTextureShaderHandle {
			enTextureShaderHandle_DiffuseMap,	//!<�f�B�t���[�Y�}�b�v�B
			enTextureShaderHandle_ShadowMap_0,	//!<�V���h�E�}�b�v0
			enTextureShaderHandle_ShadowMap_1,	//!<�V���h�E�}�b�v1
			enTextureShaderHandle_ShadowMap_2,	//!<�V���h�E�}�b�v2
			enTextureShaderHandle_NormalMap,	//!<�@���}�b�v�B
			enTextureShaderHandle_SpecularMap,	//!<�X�y�L�����}�b�v�B
			enTextureShaderHandle_SkyCubeMap,	//!<�X�J�C�L���[�u�B
			enTextureShaderHandle_SplatMap,		//!<�X�v���b�g�}�b�v�B
			enTextureShaderHandle_TerrainTex0,	//!<�n�`�e�N�X�`��0
			enTextureShaderHandle_TerrainTex1,	//!<�n�`�e�N�X�`��1
			enTextureShaderHandle_TerrainTex2,	//!<�n�`�e�N�X�`��2
			enTextureShaderHandle_TerrainTex3,	//!<�n�`�e�N�X�`��3
			enTextureShaderHandle_TerrainNormalMap0,	//!<�n�`�̖@���}�b�v0�B
			enTextureShaderHandle_TerrainNormalMap1,	//!<�n�`�̖@���}�b�v1�B
			enTextureShaderHandle_TerrainNormalMap2,	//!<�n�`�̖@���}�b�v2�B
			enTextureShaderHandle_TerrainNormalMap3,	//!<�n�`�̖@���}�b�v3�B
			enTextureShaderHandle_Num,
		};
		/*!
		*@brief	�s��̃V�F�[�_�[�n���h���B
		*/
		enum EnMatrixShaderHandle {
			enMatrixShaderHandle_LastFrameViewProj,		//!<1�t���[���O�̃r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_ViewProj,				//!<�r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_LVP,					//!<���C�g�r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_WorldMatrix,			//!<���[���h�s��
			enMatrixShaderHandle_Num,
		};
		/*!
		*@brief	���������_�x�N�g���̃V�F�[�_�[�n���h���B
		*/
		enum EnFVectorShaderHandle {
			enFVectorShaderHandle_CameraPos,	//!<�J�����̈ʒu�B

			enFVectorShaderHandle_FogParam,		//!<Fog�p�����[�^�B
			enFVectorShaderHandle_CameraDir,	//!<�J�����̕����B
			enFVectorShaderHandle_TerrainRect,	//!<�n�`�̃T�C�Y�B
			enFVectorShaderHandle_Num,
		};
		/*!
		*@brief	�����x�N�g���̃V�F�[�_�[�n���h���B
		*/
		enum EnIVectorShaderHandle {
			enIVectorShaderHandle_Flags,		//!<�e��t���O�Bx�ɖ@���}�b�v�Ay�̓V���h�E���V�[�o�[�Az�̓������C�g�Aw�̓X�y�L�����}�b�v�B
			enIVectorShaderHandle_Flags2,		//!<�e��t���O�Bx�ɑ��x�}�b�v�ւ̏������݁Ay�͑�C�����V�~�����[�V������ށB
			enIVectorShaderHandle_Num,
		};
		/*!
		*@brief	�����̃V�F�[�_�[�n���h���B
		*/
		enum EnIntShaderHandle {
			enIntShaderHandle_NumBone,			//!<�{�[���̐��B
			enIntshaderHandle_CurNumBone,		//!<�X�L�j���O���s���{�[���̐��B
			enIntShaderHandle_Num,
		};
		
	
	public:
		/*!
		*@brief	�V�F�[�_�[�e�N�j�b�N�̃n���h���B
		*/
		enum EnShaderTechnique {
			enTecShaderHandle_SkinModelInstancingRenderToShadowMap,		//!<SkinModelInstancingRenderToShadowMap�e�N�j�b�N
			enTecShaderHandle_SkinModelInstancing,						//!<SkinModelInstancing�e�N�j�b�N�B
			enTecShaderHandle_NoSkinModelInstancingRenderToShadowMap,	//!<NoSkinModelInstancingRenderToShadowMap�e�N�j�b�N�B
			enTecShaderHandle_NoSkinModelInstancing,					//NoSkinModelInstancing�e�N�j�b�N�B
			enTecShaderHandle_SkinModelRenderShadowMap,					//!<SkinModelRenderShadowMap�e�N�j�b�N�B
			enTecShaderHandle_SkinModel,								//!<SkinModel�e�N�j�b�N�B
			enTecShaderHandle_NoSkinModelRenderShadowMap,				//!<NoSkinModelRenderShadowMap�e�N�j�b�N�B
			enTecShaderHandle_NoSkinModel,								//!<NoSkinModel�e�N�j�b�N�B
			enTecShaderHandle_Sky,										//!<Sky�e�N�j�b�N�B
			enTecShaderHandle_Terrain,									//!<Terrain�p�e�N�j�b�N�B
			enTecShaderHandle_Toon,
			enTecShaderHandle_ToonNonSkin,
			enTecShaderHandle_Num,
		};
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSkinModelMaterial();
		
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CSkinModelMaterial();
		
		/*!
		 *@brief	�}�e���A�����\�z�B
		 *@param[in]	type		�}�e���A���̃^�C�v�B
		 */
		void Build(EnType type);
		/*!
		 *@brief	�e�N�X�`����ݒ�B
		 */
		void SetTexture(EnTextureShaderHandle eTexHandle, const CTexture& tex)
		{
			TK_ASSERT(eTexHandle < enTextureShaderHandle_Num, "eTexHandle is invalid");
			m_textures[eTexHandle] = &tex;
		}
		/*!
		*@brief	�s���ݒ�B
		*/
		void SetMatrix(EnMatrixShaderHandle eMatrixHandle, const CMatrix& mat)
		{
			TK_ASSERT(eMatrixHandle < enMatrixShaderHandle_Num, "eMatrixHandle is invalid");
			m_matrices[eMatrixHandle] = mat;
		}
		/*!
		*@brief ���������x�N�g����ݒ�B
		*/
		template<class TVector>
		void SetFVector(EnFVectorShaderHandle eFVecHandle, const TVector& v)
		{
			TK_ASSERT(eFVecHandle < enFVectorShaderHandle_Num, "eFVecHandle is invalid");
			m_fVector[eFVecHandle].Set(v);
		}
		/*!
		*@brief �����x�N�g����ݒ�B
		*/
		void SetIVector(EnIVectorShaderHandle eIVecHandle, const CVector4i& v)
		{
			TK_ASSERT(eIVecHandle < enIVectorShaderHandle_Num, "eIVecHandle is invalid");
			m_iVector[eIVecHandle] = v;
		}
		/*!
		*@brief �����f�[�^��ݒ�B
		*/
		void SetInt(EnIntShaderHandle eIntHandle, int data)
		{
			TK_ASSERT(eIntHandle < enIntShaderHandle_Num, "eIntHandle is invalid");
			m_int[eIntHandle] = data;
		}
		/*!
		*@brief ��C�����p�����[�^��ݒ�B
		*/
		void SetAtmosphericScatteringParam(const SAtmosphericScatteringParam& param)
		{
			m_atmosParam = param;
		}
		/*!
		*@brief ���C�g��ݒ�B
		*/
		void SetLight(const CLight& light)
		{
			m_light = light;
		}
		/*!
		*@brief	�V���h�E���V�[�o�[�p�����[�^��ݒ�B
		*/
		void SetShadowRecieverParam(const CShadowMap::ShadowRecieverParam& shadowRecParam)
		{
			m_shadowRecParam = shadowRecParam;
		}
		/*!
		*@brief	�{�[���s��̃A�h���X��ݒ�B
		*/
		void SetBoneMatrixAddr(const D3DXMATRIX* boneMatrix, int arraySize)
		{
			m_boneMatrixArray = boneMatrix;
			m_boneMatrixArraySize = arraySize;
		}
		/*!
		*@brief	�e�N�j�b�N�n���h����ݒ�B
		*/
		void SetTechnique(EnShaderTechnique eTec)
		{
			m_hTec = m_hTechniqueHandle[eTec];
			m_eTec = eTec;
		}
		/*!
		*@brief	�V�F�[�_�[�e�N�j�b�N���擾�B
		*/
		EnShaderTechnique GetTechnique() const
		{
			return m_eTec;
		}
		
		/*!
		*@brief	�������B
		*@param[in]		tecName		�e�N�j�b�N���B
		*@param[in]		matName		�}�e���A�����B
		*/
		void Init(const char* tecName, const char* matName);
		/*!
		 *@brief	�`��J�n�B
		 */
		void BeginDraw();
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		void SendMaterialParamToGPU();
		/*!
		 *@brief	�`��I���B
		 */
		void EndDraw();
		/*!
		*@brief	�}�e���A�������擾�B
		*/
		const char* GetName() const
		{
			return m_materialName.c_str();
		}
		/*!
		*@brief	�e�N�X�`����GPU�ɓ]���B
		*@details
		* ���̊֐���ISkinModelMaterialNode�̔h���N���X�ł����g�p���Ȃ��悤�ɒ��ӂ��Ă��������B
		*/
		void SendTextureTGPU(EnTextureShaderHandle eTex)
		{
			TK_ASSERT(m_isBeginDraw, "Please call BeginDraw!!!!");
			if (m_pEffectRaw != nullptr) {
				if (m_textures[eTex] != nullptr) {
					if (m_textures[eTex]->IsCubeMap()) {
						m_pEffectRaw->SetTexture(m_hTexShaderHandle[eTex], m_textures[eTex]->GetCubeMapDX());
					}
					else {
						m_pEffectRaw->SetTexture(m_hTexShaderHandle[eTex], m_textures[eTex]->GetTextureDX());
					}
				}
			}
		}
		/*!
		*@brief	�s���GPU�ɓ]���B
		*@details
		* ���̊֐���ISkinModelMaterialNode�̔h���N���X�ł����g�p���Ȃ��悤�ɒ��ӂ��Ă��������B
		*/
		void SendMatrixToGPU(EnMatrixShaderHandle eMatrix)
		{
			TK_ASSERT(m_isBeginDraw, "Please call BeginDraw!!!!");
			if (m_pEffectRaw != nullptr) {
				m_pEffectRaw->SetMatrix(m_hMatrixShaderHandle[eMatrix], (D3DXMATRIX*)&m_matrices[eMatrix]);
			}
		}
		/*!
		*@brief	���������x�N�g����GPU�ɓ]���B
		*@details
		* ���̊֐���ISkinModelMaterialNode�̔h���N���X�ł����g�p���Ȃ��悤�ɒ��ӂ��Ă��������B
		*/
		void SendFVectorToGPU(EnFVectorShaderHandle eVector)
		{
			TK_ASSERT(m_isBeginDraw, "Please call BeginDraw!!!!");
			if (m_pEffectRaw != nullptr) {
				m_pEffectRaw->SetVector(m_hFVectorShaderHandle[eVector], (D3DXVECTOR4*)&m_fVector[eVector]);
			}
		}
		/*!
		*@brief	�����x�N�g����GPU�ɓ]���B
		*@details
		* ���̊֐���ISkinModelMaterialNode�̔h���N���X�ł����g�p���Ȃ��悤�ɒ��ӂ��Ă��������B
		*/
		void SendIVectorToGPU(EnIVectorShaderHandle eVector)
		{
			TK_ASSERT(m_isBeginDraw, "Please call BeginDraw!!!!");
			if (m_pEffectRaw != nullptr) {
				m_pEffectRaw->SetIntArray(m_hIVectorShaderHandle[eVector], (int*)&m_iVector[eVector], 4);
			}
		}
		/*!
		*@brief	������GPU�ɓ]���B
		*@details
		* ���̊֐���ISkinModelMaterialNode�̔h���N���X�ł����g�p���Ȃ��悤�ɒ��ӂ��Ă��������B
		*/
		void SendIntToGPU(EnIntShaderHandle eInt)
		{
			TK_ASSERT(m_isBeginDraw, "Please call BeginDraw!!!!");
			if (m_pEffectRaw != nullptr) {
				m_pEffectRaw->SetInt(m_hIntShaderHandle[eInt], m_int[eInt]);
			}
		}
	private:
		/*!
		*@brief	�V�F�[�_�[�n���h���̏������B
		*/
		void InitShaderHandles(const char* tecName);
	protected:
		const CTexture*	m_textures[enTextureShaderHandle_Num];	//!<�e�N�X�`���B
		CMatrix 	m_matrices[enMatrixShaderHandle_Num];	//!<�s��B
		CVector4 	m_fVector[enFVectorShaderHandle_Num];	//!<4�v�f�̕��������x�N�g���B
		CVector4i	m_iVector[enIVectorShaderHandle_Num];	//!<4�v�f�̐����x�N�g���B
		int			m_int[enIntShaderHandle_Num];			//!<�����B
		SAtmosphericScatteringParam m_atmosParam;			//!<��C�����p�����[�^�B
		CLight m_light;										//!<���C�g�B
		CShadowMap::ShadowRecieverParam m_shadowRecParam;	//!<�V���h�E���V�[�o�[�p�����[�^�B
	private:
		
		typedef std::unique_ptr<ISkinModelMaterialNode>	ISkinModelMaterialNodePtr;
		std::vector<ISkinModelMaterialNodePtr>	m_materialNodes;		//!<�}�e���A���̃m�[�h�B

		std::string m_materialName;										//!<�}�e���A�����B
		CEffect* m_pEffect = nullptr;									//!<�G�t�F�N�g�B
		ID3DXEffect* m_pEffectRaw = nullptr;
		D3DXHANDLE m_hTec;												//!<�e�N�j�b�N�n���h���B
		EnShaderTechnique m_eTec = enTecShaderHandle_SkinModel;			//!<���݂̃V�F�[�_�[�e�N�j�b�N�B
		D3DXHANDLE m_hTexShaderHandle[enTextureShaderHandle_Num];		//!<�e�N�X�`���V�F�[�_�[�n���h���B
		D3DXHANDLE m_hMatrixShaderHandle[enMatrixShaderHandle_Num];		//!<�s��̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hFVectorShaderHandle[enFVectorShaderHandle_Num];	//!<���������x�N�g���̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hIVectorShaderHandle[enIVectorShaderHandle_Num];	//!<�����x�N�g���̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hIntShaderHandle[enIntShaderHandle_Num];			//!<�����̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hAtmosShaderHandle;								//!<��C�����̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hLightShaderHandle;								//!<���C�g�p�̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hBoneMatrixArrayHandle;							//!<�{�[���s��̃n���h���B
		D3DXHANDLE m_hShadowRecieverParamShaderHandle;					//!<�V���h�E���V�[�o�[�p�����[�^�̃V�F�[�_�[�n���h���B						
		D3DXHANDLE m_hBoneMatrixArrayShaderHandle;						//!<�{�[���s��̔z��̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hTechniqueHandle[enTecShaderHandle_Num];			//!<�e�N�j�b�N�̃n���h���B
		
		const D3DXMATRIX* m_boneMatrixArray = nullptr;					//!<�{�[���s��ւ̃|�C���^�B
		int m_boneMatrixArraySize = 0;									//!<�{�[���s��̔z��̃T�C�Y�B
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		bool m_isBeginDraw = false;						//!<BeginDraw���Ă΂�Ă���H
#endif
	};
}