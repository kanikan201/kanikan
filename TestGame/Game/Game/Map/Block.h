#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class Block: public IGameObject
{
public:
	Block();
	~Block();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();

	bool GetPlayerHit()
	{
		return PlayerHit;
	}
	void SetPlayerHit(bool flg) {
		PlayerHit = flg;
	}
	CVector3 GetPosition() {
		return position;
	}
private:
	CSkinModel					skinModel;		//スキンモデル
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ

	CVector3					position;
	CQuaternion					rotation;
	CVector3					DownPos = { 0.0f,-2.0f,0.0f };	//下方向のベクトル
	CVector3					UpPos = { 0.0f,1.0f,0.0f };	//上方向のベクトル
	CVector3					move = CVector3::Zero;
	bool						Upflg = false;	//上に動かすフラグ
	bool						PlayerHit = false;	//プレイヤーとのヒットフラグ
	float						timer = 0.0f;	//タイマー
};

extern Block* block;