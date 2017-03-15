/*!
 * @brief	CSkinModelData�̃��\�[�X�Ǘ��B
 */
#pragma once

#include <mutex>
#include <queue>
#include "tkEngine/thread/tkCriticalSection.h"

namespace tkEngine{
	class CSkinModelDataHandle;
	class CSkinModel;
	typedef std::shared_ptr<CSkinModelData> CSkinModelDataPtr;
	/*!
	 * @brief	CSkinModelData�̃��\�[�X�Ǘ��B
	 */
	class CSkinModelDataResources{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSkinModelDataResources();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CSkinModelDataResources();
		/*!
		 * @brief	���[�h�B
		 *@param[out]	skinModelDataHandle	�X�L�����f���f�[�^�̃n���h���̊i�[��B
		 *@param[in]	modelPath			���f���̃t�@�C���p�X�B
		 *@param[in]	anim				�A�j���[�V�����B
		 *@param[in]	isInstancing		�C���X�^���V���O���f���H
		 *@param[in]	numInstance			�C���X�^���X�̐��B
		 */
		void Load(
			CSkinModelDataHandle& skinModelDataHandle,
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing ,
			int numInstance 
		);
		/*!
		* @brief	�񓯊��ǂݍ���
		* @details
		*  ���̊֐����g�p����ꍇ��CSkinModelDataHandle��IsLoadEnd�֐����g�p���ē���������Ă��������B
		*@param[out]	skinModelDataHandle	�X�L�����f���f�[�^�̃n���h���̊i�[��B
		*@param[in]	modelPath			���f���̃t�@�C���p�X�B
		*@param[in]	anim				�A�j���[�V�����B
		*@param[in]	isInstancing		�C���X�^���V���O���f���H
		*@param[in]	numInstance			�C���X�^���X�̐��B
		*/
		void LoadAsync(
			CSkinModelDataHandle& skinModelDataHandle,
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing,
			int numInstance
			)
		{
			
			m_asyncLoadReqeustQueueCS.Lock();
			//�񓯊��ǂݍ��݂̃��N�G�X�g���쐬���ăL���[�ɐςށB
			SAsyncLoadRequest req;
			req.skindModelDataHandle = &skinModelDataHandle;
			req.modelPath = modelPath;
			req.anim = anim;
			req.isInstancing = isInstancing;
			req.numInstance = numInstance;
			m_asyncLoadRequestQueue.push(req);
			//�L���[�ɐς܂ꂽ�̂ŐQ�Ă��郏�[�J�[�X���b�h���N�����B
			m_asyncLoadReqeustQueueCS.Unlock();
		}
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/*!
		* @brief	�񓯊��ǂݍ��݃X���b�h����Ă΂��X�V�֐��B
		*/
		void UpdateAsyncLoadThread();
		/*!
		* @brief	CSkinModelData�̃����[�X��j���B
		*/
		void Release()
		{
			m_cs.Lock();
			m_instancingModelDataList.clear();
			m_skinModelDataMap.clear();
			m_cs.Unlock();
		}
		/*!
		* @brief	�K�x�[�W�R���N�g�̎��s�B
		*@details
		* �Q�ƃJ�E���^���ɂȂ��Ă���CSkinModelData���������܂��B
		*/
		void GC();
	private:
		/*!
		 * @brief	�񓯊��ǂݍ��݃��N�G�X�g
		 */
		struct SAsyncLoadRequest{
			CSkinModelDataHandle*	skindModelDataHandle;
			std::string modelPath;
			CAnimation* anim;
			bool isInstancing;
			int numInstance;
		};
		typedef std::map<int, CSkinModelDataPtr >	CSkinModelDataMap;
		typedef std::list<CSkinModelDataPtr>		CSkinModelDataList;
		CSkinModelDataMap	m_skinModelDataMap;
		CSkinModelDataList	m_instancingModelDataList;
		std::queue<SAsyncLoadRequest> m_asyncLoadRequestQueue;	//!<�񓯊��ǂݍ��݃��N�G�X�g�̃L���[�B
		CCriticalSection m_asyncLoadReqeustQueueCS;				//!<�ǂݍ��݃��N�G�X�g�L���[�����N���e�B�J���Z�N�V�����B
		CCriticalSection m_cs;
		std::thread m_asyncLoadThread;							//!<�񓯊��ǂݍ��݃X���b�h�B
	};
}