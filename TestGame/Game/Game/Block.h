#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/character/tkCharacterController.h"

class Block: public IGameObject
{
public:
	Block();
	~Block();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();
private:
	CSkinModel					skinModel;		//スキンモデル
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ
	CCharacterController		characterController;		//キャラクタ―コントローラー

	CVector3					position;
	CQuaternion					rotation;
	CVector3					DownPos = { 0.0f,-20.0f,0.0f };
	CVector3					UpPos = { 0.0f,20.0f,0.0f };
	CVector3					move = CVector3::Zero;
	bool						Upflg = false;
	float						timer = 0.0f;
};

extern Block* block;