/*!
 * @brief	�e�N�X�`���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkTexture.h"

namespace tkEngine {
	/*!
	 * @brief	�e�N�X�`�������[�h�B
	 */
	bool CTexture::Load(const char* fileName, bool isCubeMap)
	{
		Release();
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if (!isCubeMap) {
			if (FAILED(D3DXCreateTextureFromFile(
				device,
				fileName,
				&m_tex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		else {
			if (FAILED(D3DXCreateCubeTextureFromFile(
				device,
				fileName,
				&m_cubeTex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		ComputeTexSize();
		return true;
	}
}