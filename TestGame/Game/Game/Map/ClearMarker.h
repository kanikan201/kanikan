/*
	クリアマーカー
*/

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class ClearMarker : public IGameObject
{
public:
	ClearMarker();
	~ClearMarker();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel					skinModel;		//スキンモデル
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ

	CVector3					position;		//マーカーの位置
	CQuaternion					rotation;
	bool						flag = false;	//クリアフラグ
};

