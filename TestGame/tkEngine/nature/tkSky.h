/*!
 * @brief	��B
 */
#pragma once
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAtmosphericScatteringParam.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	/*!
	 * @brief	��̃V�~�����[�V�����N���X�B
	 * @details
	 *  tkEngine::Sky().SetEnable���R�[�����邱�Ƃŋ�̃V�~�����[�V�������s����悤�ɂȂ�܂��B</br>
	 *  SetEnable�֐��̏ڍׂɂ��Ă͊֐��̐������Q�Ƃ��ĉ������B</br>
	 *  ��͑傫�ȋ��̂̃��f�����J�����̒����_�𒆐S�Ƃ��ĕ`�悳��܂��B</br>
	 *  ��ɓ\���Ă���e�N�X�`����Assets/modelData/sky.dds�ł��B</br>
	 *  ��̃e�N�X�`����ύX�������ꍇ�͂��̃e�N�X�`�����㏑�����Ă��������B</br>
	 *  �e�N�X�`���͋�ɓ��e����L���[�u�}�b�v�ɂȂ��Ă���K�v������̂Œ��ӂ��Ă��������B</br>
	 *  �܂��A���̃V�~�����[�V�����ōs���Ă��鏈���ł͋�̐F�̓e�N�X�`������T���v�����O���Ă���̂ł͂Ȃ��A</br>
     *  ��C�����̌v�Z���s���Č��肳��܂��B�e�N�X�`���͉_�̌`��������_�����O���邽�߂����Ɏg�p����Ă���̂Œ��ӂ��Ă��������B</br>
     * @todo
     *  �������̋@�\�Ƃ��āA�_�̌`��𒊏o���邽�߂�臒l�����ߑł��ɂȂ��Ă��邽�߁A�قȂ�e�N�X�`����</br>
     *  �g�p�����ꍇ�ɉ_���Y��ɕ\������Ȃ����Ƃ��z�肳��܂��B</br>
     *  ��肪�N�����ꍇ�͂���臒l�𒲐��ł���悤�ɂ���K�v������܂��B</br>
     *@code
     		void Init()
     		{
				//��̃V�~�����[�V������L���ɂ���B
				Sky().SetEnable( &camera, &light );
			}
     *@endcode
	 */
	class CSky : public IGameObject {
		enum InitStep {
			InitStep_Load,
			InitStep_Wait,
		};
		CSkinModelDataHandle	skinModelData;					//!<�X�L�����f���f�[�^�B
		CSkinModel				skinModel;						//!<�X�L�����f���B
		CAnimation				animation;						//!<�A�j���[�V�����B
		CLight					light;							//!<���C�g�B
		CTexture				normalMap;
		InitStep				initStep = InitStep_Load;
		SAtmosphericScatteringParam	atomosphereParam;			//!<��C�����p�����[�^�B
		CVector3				sunPosition = CVector3::Zero;	//!<���z�̈ʒu�B
		float					sunAngle = 0.0f;
		CLight					sunLight;						//!<���C�g�B
		CSkinModelDataHandle	sunModelData;					//!<���z�̃��f���f�[�^�B
		CSkinModel				sunModel;						//!<���z�̃��f���B
		CVector3				sunDir = CVector3::Zero;		//!<���z�̕����B
		float					deltaTimeMul = 1.0f;			//!<���^�C���ɏ�Z�����l�B
		const CCamera*			camera = nullptr;				//!<�J�����B
		CLight*					sceneLight = nullptr;								//!<�V�[�����C�g�B
		CVector3				dayAmbinetLight = CVector3(0.3f, 0.3f, 0.3f);		//!<�����̃A���r�G���g���C�g�B
		CVector3				nightAmbinetLight = CVector3(0.1f, 0.1f, 0.1f);		//!<��Ԃ̃A���r�G���g���C�g�B
	public:
		CSky();
		
		~CSky()
		{

		}
		bool Start() override;
		
		void Update() override;
		/*!
		 *@brief	��̃V�~�����[�V������L���ɂ���B
		 *@details
		 *  ��̃V�~�����[�V�������L���ɂȂ�܂��B��������_�����O���邽�߂ɃJ�����͕K���ݒ肵�Ă��������B</br>
		 *  ���C�g��ݒ肷��ƁA���z�̓����ɍ��킹�����C�g�̌v�Z���s���܂��B</br>
		 *  �f�B�t���[�Y���C�g�̈�{�ځA�������C�g�A�A���r�G���g���C�g���v�Z�����悤�ɂȂ�܂��B</br>
		 *  �Q�[�����ŏ�L�̃��C�g�̒l��ύX���邱�Ƃ͉\�ł����A�V�~�����[�V�����̌��ʂɕω����N����̂Œ��ӂ��Ă��������B</br>
		 *@param[in]	camera		�V�[���J�����B
		 *@param[in]	light		���C�g(NULL�̎w����\�B)
		 */
		void SetEnable( const CCamera* camera, CLight* light )
		{
			this->camera = camera;
			sceneLight = light;
			SetActiveFlag(true);
		}
		/*!
		 * @brief	��̃V�~�����[�V�����𖳌��ɂ���B
		 */
		void SetDisable()
		{
			SetActiveFlag(false);
		}
		/*!
		* @brief	���z�̖��邳��ݒ�B
		*/
		void SetLuminance(const CVector3& luminance)
		{
			sunLight.SetEmissionLightColor(luminance);
		}
		/*!
		 * @brief	�J������ݒ�B
		 */
		void SetCamera( const CCamera& camera )
		{
			this->camera = &camera;
		}
		/*!
		 * @brief	�Q�[���V�[���Ŏg�p���Ă��郉�C�g��ݒ�B
		 *@details
		 * ���̃��C�g��ݒ肷��ƃf�B�t���[�Y���C�g�̈�{�ڂƃ������C�g�A�A���r�G���g���C�g��
		 * ���z�̓�������v�Z�����悤�ɂȂ�܂��B
		 * �Q�[�����ŏ�L�̃��C�g�̒l��ύX���邱�Ƃ͂ł��܂����A
		 * ��C�V�~�����[�V�����ɕω����N����̂Œ��ӂ��Ă��������B
		 *@param[in]	light		���C�g�B
		 */
		void SetSceneLight( CLight& light )
		{
			sceneLight = &light;
		}
		/*!
		 * @brief	�����̃A���r�G���g���C�g��ݒ�B
		 */
		void SetDayAmbientLight( const CVector3& lig )
		{
			dayAmbinetLight = lig;
		}
		/*!
		 * @brief	��Ԃ̃A���r�G���g���C�g��ݒ�B
		 */
		void SetNightAmbientLight( const CVector3& lig )
		{
			nightAmbinetLight = lig;
		}
		//��C�����p�����[�^�[���擾�B
		const SAtmosphericScatteringParam& GetAtomosphereParam() const
		{
			return atomosphereParam;
		}
		void Render(CRenderContext& renderContext) override;
		/*!
		 * @brief	���z�̈ʒu��ݒ�B
		 */
		void SetSunPosition( const CVector3& position )
		{
			sunPosition = position;
		}
		/*!
		* @brief	���z�̍��W���擾�B
		*/
		const CVector3& GetSunPosition() const
		{
			return sunPosition;
		}
		/*!
		* @brief	���z�̕������擾�B
		* @details
		*  �f���̒��S���猩���ꍇ�̑��z�̕����ł��B
		*/
		const CVector3& GetSunDir() const
		{
			return sunDir;
		}
		/*!
		* @brief	���^�C���ɏ�Z�����l��ݒ�B
		*@param[in]	mul		�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�܂��B
		*/
		void SetFrameDeltaTimeMul(float mul)
		{
			deltaTimeMul = mul;
		}
		void Init();
	};
}
