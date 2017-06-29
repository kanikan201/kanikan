#pragma once

#include "tkEngine/character/tkCharacterController.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start() override;
	void Update() override;
	void SetPosition(CVector3 pos);

	void Render(CRenderContext& renderContext) override;

private:
	CSprite			sprite;		//スプライト
	CTexture		texture;	//テクスチャ

	CSkinModel					skinModel;					//スキンモデル
	CSkinModelDataHandle		skinModelData;				//スキンモデルデータ。
	CCharacterController		characterController;		//キャラクタ―コントローラー

	CVector3			position = CVector3::Zero;			//プレイヤーの座標
	CQuaternion			rotation = CQuaternion::Identity;	//回転

	CQuaternion			qRotX, qRotY, View;
	CVector3			toLightPos;
	CAnimation			animation;				//アニメーション。
	int					Run = 2;				//アニメーションナンバー。2は走るモーション。

	CCamera				camera;					//ユニティちゃんカメラ。
};

