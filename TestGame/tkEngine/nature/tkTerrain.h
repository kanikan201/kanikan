/*!
 *@brief	�n�`�B
 */

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 *@brief	�n�`�B
	 *@detail
	 * �X�v���b�g�}�b�v���g�p�����n�`�����B�o�^�ł���e�N�X�`���̐��͂S��(���₷���Ƃ͉\�B)</br>
	 * �X�v���b�g�}�b�v��R������0�Ԗڂ̃e�N�X�`���AG�����͂P�Ԗڂ̃e�N�X�`���AB������2�Ԗڂ̃e�N�X�`��</br>
	 * ��������3�Ԗڂ̃e�N�X�`���̏d�݂ɂȂ�B</br>
	 * �Ⴆ�΁A�X�v���b�g�}�b�v�̃e�N�Z����RGBA(255,255,0,0)�̏ꍇ�́A</br>
	 * 0�Ԗڂ̃e�N�X�`���~0.5�{1�Ԗڂ̃e�N�X�`���~0.5�ƂȂ�B</br>
	 */
	class CTerrain : public IGameObject {
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CTerrain();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CTerrain();
		/*!
		 *@brief	�������B
		 *@param[in]	skinModelDataPath	�X�L�����f���f�[�^�̃p�X�B
		 *@param[in]	splatMapPath		�X�v���b�g�}�b�v�̃p�X�B
		 *@param[in]	texturePaths		�n�`�̃e�N�X�`���̃p�X�B�ő�MAX_TEXTURE�̐������w��ł���B�I�[�ɂ�NULL���w�肵�Ă��������B
		 *@param[in]	camera				�J�����B
		 *@param[in]	light				���C�g�B
		 */
		void Init( 
			const char* skinModelDataPath, 
			const char* splatMapPath, 
			const char* texturePaths[],
			const CCamera& camera,
			const CLight& light
		);
		bool Start() override;
		void Update() override;
		void Render(CRenderContext& renderContext) override;
		/*!
		 *@brief	���W��ݒ肷��B
		 *@param[in]	pos		���W�B
		 */
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/*!
		 *@brief	��]��ݒ肷��B
		 *@param[in]	rot		��]�B
		 */
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/*!
		 *@brief	�g�嗦��ݒ�B
		 */
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
	private:
		/*!
		*@brief	�n�`�̕��ƍ������v�Z�B
		*/
		void CalcWidthAndHeight();
	private:
		/*!
		 *@brief	�������X�e�b�v�B
		 */
		enum class InitStep{
			enStartLoad,	//!<���[�h�J�n�B
			enWatiLoad,		//!<���[�h�ҋ@�B
		};
		
		static const int MAX_TEXTURE = 4;							//!<�n�`�̃e�N�X�`���̍ő吔�B
		CSkinModelDataHandle	m_skinModelData;					//!<�X�L�����f���f�[�^�B
		InitStep				m_initStep = InitStep::enStartLoad;	//!<���[�h�J�n�X�e�b�v�B
		CSkinModel				m_skinModel;						//!<�X�L�����f���B
		const CLight*			m_light = nullptr;					//!<���C�g�B
		CTexture				m_splatMap;							//!<�X�v���b�g�}�b�v�B
		CTexture				m_textures[MAX_TEXTURE];			//!<�n�`�e�N�X�`���B
		CVector3				m_position = CVector3::Zero;		//!<���W�B
		CQuaternion				m_rotation = CQuaternion::Identity;	//!<��]�B
		CVector3				m_scale = CVector3::One;			//!<�g��B
		std::string				m_skinModelDataPath;				//!<�X�L�����f���f�[�^�p�X�B
		std::string				m_splatMapPath;						//!<�X�v���b�g�}�b�v�̃p�X�B
		std::string				m_texturePaths[MAX_TEXTURE];		//!<�n�`�̃e�N�X�`���̃p�X�B
		const CCamera*			m_camera = nullptr;					//!<�J�����B
		CMeshCollider			m_meshCollider;						//!<���b�V���R���C�_�[�B
		CRigidBody				m_rigidBody;						//!<���́B
		CVector4				m_terrainSize = {0.0f, 0.0f, 0.0f, 0.0f};	//!<�n�`�̃T�C�Y�B
	};
}