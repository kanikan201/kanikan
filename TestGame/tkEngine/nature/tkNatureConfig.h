/*!
 * @brief	���R���֌W�̃R���t�B�O�B
 */

#pragma once


namespace tkEngine{
	/*!
	 * @brief	��̃R���t�B�O�B
	 */
	struct SSkyConfig{
		bool isEnable = false;	//!<��̃V�~�����[�V�������G���W���ōs�����ǂ����̃t���O�B
		bool isUseSun = false;	//!<���z����H
		bool isSunMove = false;	//!<���z�����H
	};
	
	/*!
	 * @brief	���R���֌W�̃R���t�B�O�B
	 */
	struct SNatureConfig{
		SSkyConfig		skyConfig;		//!<��̃R���t�B�O�B
	};
}
