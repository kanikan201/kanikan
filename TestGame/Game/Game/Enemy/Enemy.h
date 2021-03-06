/*
	敵の基本クラス
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Init(CVector3 FirstPosition);
	void Update();
	void Render(CRenderContext& renderContext);
	void Damage();
protected:
	virtual void Move();	//動き

	//モーション(仮)
	enum AnimationNo {
		AnimationStand,		//立ち
		AnimationWalk,		//歩き
		AnimationAttack,	//攻撃
		Waiting				//待機中
	};

	CAnimation			animation;			//アニメーション。
	AnimationNo			currentAnimSetNo;	//今のモーション
	AnimationNo			prevAnim;			//変更前のモーション

	enum EState {
		eState_Search,	//探索状態
		eState_Find,	//発見状態
	};

	EState		Estate = eState_Search;		//敵の状態

	char filePath[256];	//ファイルパス

	struct Status
	{
		int					hp;		//体力
		int					score;	//倒したときのスコア
	};

	CSkinModel				skinModel;					//スキンモデル
	CSkinModelDataHandle	skinModelData;				//スキンモデルデータ。
	CCharacterController	characterController;		//キャラクタ―コントローラー

	CVector3				position;					//敵の座標
	CVector3				centralPos;					//敵の中心の座標
	const CVector3			central = { 0.0f, 1.8f,0.0f };	//敵の中心の高さ

	CVector3				move = CVector3::Zero;
	CQuaternion				rotation = CQuaternion::Identity;	//回転

	//CAnimation		animation;			//アニメーション。
	//AnimationNo		currentAnimSetNo;	//今のモーション
	//AnimationNo		anim;				//変更前のモーション

	Status				state;	//敵のステータス

	float				length = 0.0f;	//プレイヤーとの距離
	float				m_timer = 0.0f;
	float				start;
	bool				isMoving = false;

	CTexture			darkTex;
	char				TexName[128];	//テクスチャのファイルパス
};