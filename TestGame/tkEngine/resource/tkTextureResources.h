/*!
 *@brief	�e�N�X�`���̃��\�[�X�N���X�B
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	���\�[�X�N���X�B
	 */
	class CTextureResources {
	private:
		CTextureResources();
		~CTextureResources();
	public:
		/*!
		 *@brief	�e�N�X�`�������[�h�B
		 *@details
		 * ���łɃ��[�h�ς݂̃e�N�X�`���̏ꍇ�A���̃e�N�X�`�����ė��p����܂��B
		 *@param[in]	filePath		�t�@�C���p�X�B
		 *@param[in]	isCubeMap		�L���[�u�}�b�v�����[�h����ꍇ��true�ɐݒ肵�Ă��������B
		 */
		CTexture* Load( const char* filePath, bool isCubeMap = false );
		/*!
		*@brief	����B
		*/
		void Release();
	private:
		friend class CEngine;
		std::map<int, CTexture*>	textureMap;
	};
}
