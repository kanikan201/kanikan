#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "RouteJudge.h"
#include "Map\MapDate.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "Camera\Camera.h"

class RouteObject:public IGameObject
{
public:
	RouteObject();
	~RouteObject();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Perticle();
private:
	CSkinModel					skinModel;		//�X�L�����f��
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^

	CVector3					position;		//�ʒu
	CQuaternion					rotation;		//��]
	CParticleEmitter*			perticle;		//�p�[�e�B�N��
	CLight						light;
};

extern RouteObject* routeObject[20][20];