/*!
 * @brief	�V�F�[�_�[�G�t�F�N�g�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CEffect::CEffect(LPD3DXEFFECT effect) :
		m_pEffect(effect)
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CEffect::~CEffect()
	{
		if (m_pEffect) {
			m_pEffect->Release();
			m_pEffect = nullptr;
		}
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (hFile != NULL) {
			CloseHandle(hFile);
		}
#endif
	}

	void CEffect::Update()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		m_isReloadTrigger = false;
		if (!hFile) {
			//�t�@�C�����J���B
			hFile = CreateFile(
				filePath.c_str(), 
				GENERIC_READ, 
				FILE_SHARE_READ| FILE_SHARE_WRITE| FILE_SHARE_DELETE,
				NULL, 
				OPEN_EXISTING, 
				FILE_ATTRIBUTE_NORMAL, 
				NULL
			);
			GetFileTime(hFile, NULL, NULL, &fLastWriteTime);
		}
		else {
			//�^�C���X�^���v���擾�B
			if (hFile) {
				FILETIME t;
				GetFileTime(hFile, NULL, NULL, &t);
				if (CompareFileTime(&t, &fLastWriteTime)) {
					fLastWriteTime = t;
					//�t�@�C�����X�V����Ă���̂ōēǍ��݁B
					LPD3DXBUFFER  compileErrorBuffer = nullptr;
					ID3DXEffect* newEffectFile;
					HRESULT hr = D3DXCreateEffectFromFile(
						CEngine::Instance().GetD3DDevice(),
						filePath.c_str(),
						NULL,
						NULL,
						D3DXSHADER_DEBUG,
						NULL,
						&newEffectFile,
						&compileErrorBuffer
						);
					if (FAILED(hr)) {
						//�ǂݍ��ݎ��s�B
						if (compileErrorBuffer) {
							TK_LOG(r_cast<char*>(compileErrorBuffer->GetBufferPointer()));
						}
					}
					else {
						//�����[�h�����B
						if (m_pEffect) {
							m_pEffect->Release();
						}
						m_pEffect = newEffectFile;
						//�����[�h�����B
						m_isReloadTrigger = true;
					}
				}
			}
		}
#endif
	}

}