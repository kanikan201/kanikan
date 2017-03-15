/*!
 * @brief	�X�L�����f���f�[�^�̃n���h���N���X�B
 */
#pragma once

namespace tkEngine{
	class CSkinModel;
	typedef std::shared_ptr<CSkinModelData> CSkinModelDataPtr;
	/*!
	* @brief	CSkinModelData�̃n���h���N���X�B
	*@details
	* ���̃N���X���g�p����ƁA���łɃV�[���Ƀ��[�h�ς݂̃��f���f�[�^������ꍇ�ɂ��̃f�[�^���ė��p���܂��B</br>
	* ���̂���CSkinModelData�N���X���g�p��������قƂ�ǂ̃P�[�X�Ń��[�h���Ԃ̒Z�k�ƁA�������g�p�ʂ̍œK�����s���܂��B
	*/
	class CSkinModelDataHandle : Noncopyable{
		std::shared_ptr<CSkinModelData> m_originalSkinModelData;	//!<�I���W�i���̃X�L�����f���f�[�^�B
		std::unique_ptr<CSkinModelData> m_skinModelData;			//!<�X�L�����f���f�[�^�B
		bool							m_isLoadEnd = false;		//!<�ǂݍ��ݏI���t���O�B
	public:
		/*!
		* @brief	���[�h�B
		*@param[in]	modelPath			���f���̃t�@�C���p�X�B
		*@param[in]	anim				�A�j���[�V�����B
		*@param[in]	isInstancing		�C���X�^���V���O���f���H
		*@param[in]	numInstance			�C���X�^���X�̐��B
		*/
		void LoadModelData(
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing = false,
			int numInstance = 1
		);
		/*!
		* @brief	�񓯊����[�h�B
		* @details
		*  ���̊֐����g�p�����ꍇ��IsLoadEnd�֐����g�p���ē���������Ă��������B
		*@param[in]	modelPath			���f���̃t�@�C���p�X�B
		*@param[in]	anim				�A�j���[�V�����B
		*@param[in]	isInstancing		�C���X�^���V���O���f���H
		*@param[in]	numInstance			�C���X�^���X�̐��B
		*/
		void LoadModelDataAsync(
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing = false,
			int numInstance = 1
		);
		/*!
		* @brief	�ǂݍ��ݏI������B
		*/
		bool IsLoadEnd() const
		{
			return m_isLoadEnd;
		}
		/*!
		 * @brief	CSkinModelData�̐��|�C���^���擾�B
		 */
		CSkinModelData* GetBody()
		{
			if(m_skinModelData){
				return m_skinModelData.get();
			}
			return m_originalSkinModelData.get();
		}
		/*!
		 * @brief	�������B
		 *@details
		 * CSkinModelDataResources����Ă΂�܂��B���[�U�[�͎g�p���Ȃ��悤�ɁB
		 */
		void Init(const std::shared_ptr<CSkinModelData>& skinModelData, CAnimation* anim, bool isClone);
		void NotifyLoadEnd()
		{
			m_isLoadEnd = true;
		}
	};
}
