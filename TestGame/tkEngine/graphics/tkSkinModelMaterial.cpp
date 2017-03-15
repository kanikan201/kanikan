/*!
 * @brief	�}�e���A��
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CSkinModelMaterial::CSkinModelMaterial()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CSkinModelMaterial::~CSkinModelMaterial()
	{
	}
	/*!
	*@brief	�}�e���A������GPU�ɓ]���B
	*@param[in]		effect		�G�t�F�N�g�B
	*/
	void CSkinModelMaterial::SendMaterialParamToGPUImmidiate(ID3DXEffect* effect)
	{
		if (this->effect != effect) {
			//�G�t�F�N�g���ς�����B
			this->effect = effect;
			isDirty = true;
		}
		
		if (isDirty) {
			//�Ȃɂ��ύX���������Ă���̂ŁA�V�F�[�_�[�n���h���̃��X�g���X�V�B
			shaderHandles.clear();
			
			for (auto matParam : textureMap) {
				D3DXHANDLE handle = effect->GetParameterByName(NULL, matParam.second.paramName.c_str());
				shaderHandles.push_back(handle);
			}
			isDirty = false;
		}
		//�}�e���A���p�����[�^��]���B
		int i = 0;
		for (auto& p : textureMap) {
			if (p.second.param->IsCubeMap()) {
				effect->SetTexture(shaderHandles[i], p.second.param->GetCubeMapDX());
			}
			else {
				effect->SetTexture(shaderHandles[i], p.second.param->GetTextureDX());
			}
			i++;
		}
	}
}