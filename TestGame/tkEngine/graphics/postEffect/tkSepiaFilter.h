/*!
 * @brief	�Z�s�A�t�B���^�[�B
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine{
	/*!
	 * @brief	�Z�s�A�t�B���^
	 */
	class CSepiaFilter : public IPostEffectFilter{
	public:
		CSepiaFilter();
		~CSepiaFilter();
		void Create(const SGraphicsConfig& config );
	};
}
