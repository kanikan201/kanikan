/*!
 * @brief	���m�N���t�B���^�[�B
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine{
	/*!
	 * @brief	���m�N���t�B���^
	 */
	class CMonochromeFilter : public IPostEffectFilter{
	public:
		CMonochromeFilter();
		~CMonochromeFilter();
		void Create(const SGraphicsConfig& config );
	};
}
