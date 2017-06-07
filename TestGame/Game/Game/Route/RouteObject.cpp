#include "stdafx.h"
#include "RouteObject.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"

RouteObject* routeObject[20][20];

RouteObject::RouteObject()
{
	SetActiveFlag(false);
}


RouteObject::~RouteObject()
{
	DeleteGO(perticle);
}

void RouteObject::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModelを初期化
	skinModelData.LoadModelData("Assets/modelData/route.x", NULL);
	skinModel.Init(skinModelData.GetBody());

	//デフォルトライト設定
	CVector3 ambientLight = { 0.0f, 0.59f , 0.85f  };
	ambientLight.Scale(2.8f);
	light.SetAmbinetLight(ambientLight);
	skinModel.SetLight(&light);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(90.0f));
	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//位置を記録
	this->rotation = rotation;		//回転を記録
}

void RouteObject::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		//自分を削除
		DeleteGO(this);
		return;
	}

	if (g_gameScene->getJudge()->isDelete()) {
		SetActiveFlag(false);
		DeleteGO(perticle);
	}
}

void RouteObject::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}

void RouteObject::Perticle()
{
	//return;

	perticle = NewGO<CParticleEmitter>(0);

	perticle->Init(g_random, g_gameScene->getCamera()->GetCamera(),
	{
		"Assets/sprite/Light.png",			//!<テクスチャのファイルパス。
		{ 0.0f,0.0f,0.0f },					//!<初速度。
		0.3f,								//!<寿命。単位は秒。
		0.03f,								//!<発生時間。単位は秒。
		3.0f,								//!<パーティクルの幅。
		3.0f,								//!<パーティクルの高さ。
		{ 3.0f,5.0f,3.0f },					//!<初期位置のランダム幅。
		{ 0.0f,0.0f,0.0f },					//!<初速度のランダム幅。
		{ 0.0f,0.0f,0.0f },					//!<速度の積分のときのランダム幅。
		{
			{ 0.0f,0.0f,1.0f,1.0f },			//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			{ 0.0f,0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f,0.0f }
		},
		1,									//!<UVテーブルのサイズ。
		{ 0.0f,-2.0f,0.0f },					//!<重力。
		true,								//!<死ぬときにフェードアウトする？
		0.3f,								//!<フェードする時間。
		1.0f,								//!<初期アルファ値。
		true,								//!<ビルボード？
		0.0f,								//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,									//!<0半透明合成、1加算合成。
		{ 1.0f,1.0f,1.0f },					//!<乗算カラー。
	},
		position);							//パーティクルの位置
}