/*!
 * @brief	�o�l�J����
 */

#pragma once

#include "tkEngine/graphics/tkCamera.h"

namespace tkEngine{
	/*!
	 * @brief	�o�l�J�����B
	 * @details
	 *  �o�l�Ɉ���������悤�ȃJ�����̋�������������N���X�ł��B</br>
	 *  SetTarTarget�֐���SetTarPosition�֐����g�p����</br>
	 *  �J�����̖ڕW�ƂȂ钍���_�Ǝ��_��ݒ肵�Ă��������B</br>
	 *  Update�֐������s���邱�ƂŁA�J�������ݒ肳�ꂽ�ڕW���W�ɒǏ]���Ă����܂��B</br>
	 * @code
	 *		CSpringCamera springCamera;
			//�������B
	 		void Init()
	 		{
				springCamera.Init(
					CVector3(0.0f, 0.0f, 0.0f),			
					CVector3(0.0f, 0.0f, 100.0f), 
					100.0f
				);
	 		}
			//�X�V�B
			void Update()
			{
					�E
					�E
					�E
				//�J�����̒����_��ݒ肷��B
				springCamera.SetTarTarget(target);
				springCamera.SetTarPosition(position);

				//�J�����𓮂����B
				springCamera.Update();
			}
	 * @endcode 
	 */
	class CSpringCamera{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSpringCamera();
		/*!
		 * @brief	�f�X�g���N�^
		 */
		~CSpringCamera();
		/*!
		* @brief	�������B
		*/
		void Init( const CVector3& target, const CVector3& position, float maxMoveSpeed);
		/*!
		 * @brief	�ڕW�ƂȂ钍���_��ݒ�B
		 */
		void SetTarTarget( const CVector3& target )
		{
			m_target = target;
		}
		/*!
		 * @brief	�ڕW�ƂȂ鎋�_��ݒ�B
		 */
		void SetTarPosition( const CVector3 position )
		{
			m_position = position ;
		}
		/*!
		* @brief	�����_��ݒ�B
		*/
		void SetTarget(const CVector3& target)
		{
			m_camera.SetTarget(target);
		}
		/*!
		* @brief	���_��ݒ�B
		*/
		void SetPosition(const CVector3 position)
		{
			m_camera.SetPosition(position);
		}
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetFar(float _far)
		{
			m_camera.SetFar(_far);
		}
		/*!
		* @brief	�J�����̉�]�s����擾�B
		*/
		const CMatrix& GetCameraRotation() const
		{
			return m_camera.GetCameraRotation();
		}
		/*!
		* @brief	�����_���擾�B
		*/
		const CVector3& GetTarget() const
		{
			return m_camera.GetTarget();

		}
		/*!
		* @brief	���_���擾�B
		*/
		const CVector3& GetPosition() const
		{
			return m_camera.GetPosition();
		}
		
		/*!
		 * @brief	�X�V�B
		 */
		void Update();
		/*!
		 * @brief	�J�������擾�B
		 */
		const CCamera* GetCamera() const
		{
			return &m_camera;
		}
		/*!
		* @brief	�o�l�̌�������ݒ�B
		*@detail
		* �l���傫���قǃJ�������x��ĕt���Ă��܂��B
		*/
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}
		/*!
		* @brief	�J�������擾�B
		*/
		CCamera* GetCamera() 
		{
			return &m_camera;
		}
		void SetViewAngle(float angle)
		{
			m_camera.SetViewAngle(angle);
		}
		float GetViewAngle() const
		{
			return m_camera.GetViewAngle();
		}

		/*!
		* @brief	�ڕW�ƂȂ钍���_���擾�B
		*/
		const CVector3& GetTarTarget() const
		{
			return m_target;
		}
		/*!
		* @brief	�ڕW�ƂȂ鎋�_���擾�B
		*/
		const CVector3& GetTarPosition() const
		{
			return m_position;
		}
		/*!
		* @brief	�o�l�J�����p�̃p�����[�^���N���A�B
		*/
		void ClearSpringParame()
		{
			m_targetMoveSpeed = CVector3::Zero;
			m_positionMoveSpeed = CVector3::Zero;

		}
		/*!
		* @brief	�o�l�J�����̍X�V�����B
		* @details
		*  Update�֐�����Ă΂�Ă��܂��B</br>
		*  �o�l�J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
		*/
		void UpdateSpringCamera();
		/*!
		* @brief	�J�����̍X�V�B
		* @details
		*  Update�֐�����Ă΂�Ă��܂��B</br>
		*  �J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
		*/
		void UpdateCamera()
		{
			m_camera.Update();
		}
	private:
		CCamera		m_camera;						//!<�J�����B
		CVector3	m_target = CVector3::Zero;		//!<�ڕW�ƂȂ钍���_�B
		CVector3	m_position = CVector3::Zero;	//!<�ڕW�ƂȂ鎋�_�B
		CVector3	m_targetMoveSpeed = CVector3::Zero;		//!<�����_�̈ړ����x�B
		CVector3	m_positionMoveSpeed = CVector3::Zero;	//!<���_�̈ړ����x�B
		float		m_maxMoveSpeed = 0.0f;					//!<�ō��ړ����x�B
		float		m_targetDampingRate = 1.0f;				//!<�������B�l���傫���قǃJ�������x��t���Ă���B
		float		m_dampingRate = 1.0f;					//!<�������B
		float		m_dampingRateVel = 0.0f;
	};
}