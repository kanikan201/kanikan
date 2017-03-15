/*!
 * @brief	�}�e���A���B
 */

#ifndef _TKMATERIAL_H_
#define _TKMATERIAL_H_

#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	class CEffect;
	/*!
	 *@brief	�}�e���A���B
	 */
	class CSkinModelMaterial{
	private:
		template<class T>
		struct SShaderParam {
			std::string paramName;		//�}�e���A���p�����[�^�̖��O�B�V�F�[�_�[�ŋL�q����Ă���ϐ����B
			T param;					//�p�����[�^�B
		};
		typedef SShaderParam<CTexture*>	SShaderTextureParam;
		typedef SShaderParam<CMatrix>	SShaderMatrixParam;
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSkinModelMaterial();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CSkinModelMaterial();
		/*!
		 *@brief	�e�N�X�`����ݒ�B
		 *@param[in]	paramName		�p�����[�^���B
		 *@param[in]	texture			�e�N�X�`���B
		 */
		void SetTexture( const char* paramName, CTexture* texture )
		{
			if (texture) {
				int hash = CUtil::MakeHash(paramName);
				auto it = textureMap.find(hash);
				if (it != textureMap.end()) {
					//���łɓo�^����Ă���
					it->second.param->SetTextureDX(texture->GetTextureDX());
				}
				else {
					textureMap.insert(std::pair<int, SShaderTextureParam>(hash, { paramName, texture }));
				}
				isDirty = true;
			}
		}
		/*!
		 *@brief	�}�e���A�������擾�B
		 */
		const char* GetMaterialName() const
		{
			return name.c_str();
		}
		/*!
		*@brief	�}�e���A������ݒ�B
		*/
		void SetMaterialName(const char* matName)
		{
			name = matName;
		}
		/*!
		*@brief	�}�e���A������GPU�ɓ]���B
		*@param[in]		effect		�G�t�F�N�g�B
		*/
		void SendMaterialParamToGPUImmidiate(ID3DXEffect* effect);
	private:
		ID3DXEffect*				effect = NULL;		//!<�G�t�F�N�g�B
		std::string					name;				//!<�}�e���A�����B
		std::map<int, SShaderTextureParam>	textureMap;	//!<�e�N�X�`���̃}�b�v�B
		std::vector<D3DXHANDLE>		shaderHandles;		//!<�V�F�[�_�[�n���h���̃��X�g�B
		bool						isDirty = false;	//!<�_�[�e�B�t���O�B
	};
}

#endif //_TKMATERIAL_H_