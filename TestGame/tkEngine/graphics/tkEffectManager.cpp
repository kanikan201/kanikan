/*!
 * @brief	�G�t�F�N�g�}�l�[�W��
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkEffectManager.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CEffectManager::CEffectManager()
	{
		
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CEffectManager::~CEffectManager()
	{
		Release();
	}
	/*!
	*@brief	�풓�G�t�F�N�g�t�@�C���̃��[�h�B
	*/
	void CEffectManager::LoadCommonEffect()
	{
		//�v���Z�b�g�V�F�[�_�[�͑S�čŏ��ɓǂݍ��ށB
		LoadEffect("Assets/presetShader/skinModel.fx");
		LoadEffect("Assets/presetShader/bloom.fx");
		LoadEffect("Assets/presetshader/idMap.fx");
		LoadEffect("Assets/presetShader/fxaa.fx");
		LoadEffect("Assets/presetShader/motionBlur.fx");
		LoadEffect("Assets/presetshader/shadowMap.fx");
		LoadEffect("Assets/presetShader/sprite.fx");
		LoadEffect("Assets/presetShader/TransformedPrim.fx");
		LoadEffect("Assets/presetShader/TransformedPrim.fx");
		LoadEffect("Assets/presetShader/ColorTexPrim.fx");
		LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
		LoadEffect("Assets/presetShader/TransformedPrim.fx");
	}
	/*!
	 *@brief	�G�t�F�N�g�̃��[�h�B
	 *@details
	 * �ǂݍ��ݍς݂̃G�t�F�N�g�̏ꍇ�̓��[�h�͍s��ꂸ�A</br>
	 * �����̃G�t�F�N�g���Ԃ��Ă��܂��B
	 *@param[in]	filePath	���[�h����G�t�F�N�g�̃t�@�C���p�X�B
	 *@return	���[�h�����G�t�F�N�g�t�@�C���B
	 */
	CEffect* CEffectManager::LoadEffect( const char* filePath )
	{
		
		CEffect* pEffect = nullptr;
		int hash = CUtil::MakeHash(filePath);
		
		auto it = m_effectDictinary.find(hash);
		if (it == m_effectDictinary.end()) {
			//�V�K�B
			LPD3DXEFFECT effect;
			LPD3DXBUFFER  compileErrorBuffer = nullptr;
			HRESULT hr = D3DXCreateEffectFromFile(
				CEngine::Instance().GetD3DDevice(),
				filePath,
				NULL,
				NULL,
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
				D3DXSHADER_DEBUG,
#else
				D3DXSHADER_SKIPVALIDATION,
#endif
				NULL,
				&effect,
				&compileErrorBuffer
				);
			if (FAILED(hr)) {
				MessageBox(nullptr, r_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
				TK_ASSERT(SUCCEEDED(hr), "error");
			}
			
			pEffect = new CEffect(effect);
			std::pair<int, CEffect*> node(hash, pEffect);
			m_effectDictinary.insert(node);
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			pEffect->SetFilePath(filePath);
#endif
		}
		else {
			//�o�^�ς݁B
			pEffect = it->second;
		}
		return pEffect;
	}
	/*!
	 * @brief	�����[�X�B
	 */
	void CEffectManager::Release()
	{
		for (auto p : m_effectDictinary) {
			delete p.second;
		}
		m_effectDictinary.clear();
	}
	/*!
	* @brief	�X�V�B
	*/
	void CEffectManager::Update()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		for (auto p : m_effectDictinary) {
			p.second->Update();
		}
#endif
	}
}