#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "RouteJudge.h"
#include "Map/MapData.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "Camera/Camera.h"

class RouteObject:public IGameObject
{
public:
	RouteObject();
	~RouteObject();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Perticle();	//パーティクル
private:
	CSkinModel					skinModel;		//スキンモデル
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ

	CVector3					position;		//位置
	CQuaternion					rotation;		//回転
	CParticleEmitter*			perticle;		//パーティクル
	CLight						light;			//ライト
};

extern RouteObject* routeObject[20][20];