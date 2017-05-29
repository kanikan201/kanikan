#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/Sound/tkSoundSource.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Reset();
	void SetPosition(CVector3 pos);
	void Render(CRenderContext& renderContext);
	float Distance(CVector3& objectPos);	//プレイヤーとの距離を返す

//プレイヤーの位置を返す
	CVector3 GetPosition() {
		return position;
	}

//向き取得
	CVector3 GetMoveAngle() {
		return dir;
	}

//モーション
	enum AnimationNo {
		AnimationStand,		//立ち
		AnimationWalk,		//歩き
		AnimationRun,		//走り
		AnimationJump,		//ジャンプ
	};

private:
	CVector3 Move();

	CSkinModel					skinModel;					//スキンモデル
	CSkinModelDataHandle				skinModelData;				//スキンモデルデータ。
	CCharacterController		characterController;		//キャラクタ―コントローラー

	CVector3			position = CVector3::Zero;			//プレイヤーの座標
	CQuaternion			rotation = CQuaternion::Identity;	//回転
	CVector3			dir = { 0.0f,0.0f,1.0f };			//向き

	CVector3			toLightPos;

	CAnimation			animation;				//アニメーション。
	AnimationNo			currentAnimSetNo;		//今のモーション
	AnimationNo			prevAnim;				//変更前のモーション

	float				timer = 0.0f;		//タイマー。
};