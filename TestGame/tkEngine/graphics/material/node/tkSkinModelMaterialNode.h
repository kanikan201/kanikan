/*!
 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
 */

#pragma once

#include "tkEngine/graphics/material/tkSkinModelMaterial.h"

namespace tkEngine{
	class CSkinModelMaterial;
	/*!
	 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
	 */
	class ISkinModelMaterialNode{
	protected:
		CSkinModelMaterial*		m_material = nullptr;		//!<�X�L�����f���}�e���A���B
	public:
		ISkinModelMaterialNode(CSkinModelMaterial* mat) :
			m_material(mat)
		{
		}
		virtual ~ISkinModelMaterialNode()
		{
		}
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		virtual void SendMaterialParamToGPU() = 0;
	};
	/*!
	 *@brief	�e�N�X�`���]���m�[�h�̃e���v���[�g�N���X�B
	 */
	template<CSkinModelMaterial::EnTextureShaderHandle TTex>
	class TSkinModelMaterialNode_SendTexture : public ISkinModelMaterialNode{
	public:
		TSkinModelMaterialNode_SendTexture(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		void SendMaterialParamToGPU() final
		{
			m_material->SendTextureTGPU(TTex);
		}
	};
	
	/*!
	*@brief	�s��]���m�[�h�̃e���v���[�g�N���X�B
	*/
	template<CSkinModelMaterial::EnMatrixShaderHandle TMatrix>
	class TSkinModelMaterialNode_SendMatrix : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendMatrix(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendMatrixToGPU(TMatrix);
		}
	};
	/*!
	*@brief	���������x�N�g���]���m�[�h�̃e���v���[�g�N���X�B
	*/
	template<CSkinModelMaterial::EnFVectorShaderHandle TVector>
	class TSkinModelMaterialNode_SendFVector : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendFVector(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendFVectorToGPU(TVector);
		}
	};
	/*!
	*@brief	�����x�N�g���]���m�[�h�̃e���v���[�g�N���X�B
	*/
	template<CSkinModelMaterial::EnIVectorShaderHandle TVector>
	class TSkinModelMaterialNode_SendIVector : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendIVector(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendIVectorToGPU(TVector);
		}
	};

	/*!
	*@brief	�����]���m�[�h�̃e���v���[�g�N���X�B
	*/
	template<CSkinModelMaterial::EnIntShaderHandle TInt>
	class TSkinModelMaterialNode_SendInt : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendInt(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendIntToGPU(TInt);
		}
	};

	//�f�B�t���[�Y�}�b�v�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DiffuseMap>
		CSkinModelMaterialNode_SendDiffuseMap;
	//dark�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DarkTex>
		CSkinModelMaterialNode_SendDarkTexrure;
	//depth texture �]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DepthTex>
		CSkinModelMaterialNode_SendDepthTexrure;
	//�V���h�E�}�b�v0�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
		CSkinModelMaterialNode_SendShadowMap_0;
	//�V���h�E�}�b�v1�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_1>
		CSkinModelMaterialNode_SendShadowMap_1;
	//�V���h�E�}�b�v2�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_2>
		CSkinModelMaterialNode_SendShadowMap_2;
	//�@���}�b�v�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_NormalMap>
		CSkinModelMaterialNode_SendNormalMap;
	//�X�y�L�����}�b�v�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SpecularMap>
		CSkinModelMaterialNode_SendSpecularMap;
	//�X�J�C�L���[�u�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SkyCubeMap>
		CSkinModelMaterialNode_SendSkyCubeMap;
	//�X�v���b�g�}�b�v�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SplatMap>
		CSkinModelMaterialNode_SendSplatMap;
	//�n�`�e�N�X�`��0�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex0>
		CSkinModelMaterialNode_SendTerrainTex0;
	//�n�`�e�N�X�`��1�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex1>
		CSkinModelMaterialNode_SendTerrainTex1;
	//�n�`�e�N�X�`��2�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex2>
		CSkinModelMaterialNode_SendTerrainTex2;
	//�n�`�e�N�X�`��3�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex3>
		CSkinModelMaterialNode_SendTerrainTex3;

	//�n�`�@���}�b�v0�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap0>
		CSkinModelMaterialNode_SendTerrainNormalMap0;
	//�n�`�@���}�b�v1�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap1>
		CSkinModelMaterialNode_SendTerrainNormalMap1;
	//�n�`�@���}�b�v2�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap2>
		CSkinModelMaterialNode_SendTerrainNormalMap2;
	//�n�`�@���}�b�v3�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap3>
		CSkinModelMaterialNode_SendTerrainNormalMap3;

	//1�t���[���O�̃r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LastFrameViewProj>
		CSkinModelMaterialNode_SendLastFrameViewProj;
	//�r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_ViewProj>
		CSkinModelMaterialNode_SendViewProj;
	//���C�g�r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LVP>
		CSkinModelMaterialNode_SendLVP;
	//���[���h�s��
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_WorldMatrix>
		CSkinModelMaterialNode_SendWorldMatrix;

	//�J�����̈ʒu�B
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_CameraPos>
		CSkinModelMaterialNode_SendCameraPos;
	//Fog�p�����[�^�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_FogParam>
		CSkinModelMaterialNode_SendFogParam;
	//�J�����̕����]���m�[�h�B
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_CameraDir>
		CSkinModelMaterialNode_SendCameraDir;
	//�n�`��XZ���ʏ�̃T�C�Y�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_TerrainRect>
		CSkinModelMaterialNode_SendTerrainRect;

	//!<�e��t���O�Bx�ɖ@���}�b�v�Ay�̓V���h�E���V�[�o�[�Az�̓������C�g�Aw�̓X�y�L�����}�b�v�B�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendIVector<CSkinModelMaterial::enIVectorShaderHandle_Flags>
		CSkinModelMaterialNode_SendFlags;

	//!<�e��t���O�Bx�ɑ��x�}�b�v�ւ̏������݁Ay�͑�C�����V�~�����[�V������ށB
	typedef TSkinModelMaterialNode_SendIVector<CSkinModelMaterial::enIVectorShaderHandle_Flags2>
		CSkinModelMaterialNode_SendFlags2;

	//!<�{�[���̐��B
	typedef TSkinModelMaterialNode_SendInt<CSkinModelMaterial::enIntShaderHandle_NumBone>
		CSkinModelMaterialNode_NumBone;	

	//!<�X�L�j���O���s���{�[���̐��B
	typedef TSkinModelMaterialNode_SendInt<CSkinModelMaterial::enIntshaderHandle_CurNumBone>
		CSkinModelMaterialNode_CurNumBone;
	//!<�X�L�j���O���s���{�[���̐��B
	typedef TSkinModelMaterialNode_SendInt<CSkinModelMaterial::enIntShaderHandle_IsZPrepass>
		CSkinModelMaterialNode_IsZPrepass;
}
