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

	skinModel.SetLight(&g_gameScene->getPanelLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ライトを初期化
	light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	light.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	light.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });

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

	//ルートがリセット
	if (g_gameScene->getJudge()->isDelete()) {
		SetActiveFlag(false);

		LightReset();

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
		{ 3.0f,1.5f,3.0f },					//!<初期位置のランダム幅。
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

void RouteObject::LightReset()
{
	g_gameScene->PanelLightReset();
	skinModel.SetLight(&g_gameScene->getPanelLight());
	flag = false;
}

void RouteObject::SetWorp()
{
	SetActiveFlag(true);
	//ワープの色(仮)
	CVector3 aLight = { 0.30f, 0.30f , 0.00f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}

void RouteObject::SetResetLight() {
	SetActiveFlag(true);
	//リセットの色(仮)
	CVector3 aLight = { 0.30f, 0.30f , 0.30f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}

void RouteObject::SetTrap() {
	SetActiveFlag(true);
	//邪魔パネルの色(仮)
	CVector3 aLight = { 0.07f, 0.07f , 0.10f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}

void RouteObject::SetPressLight() {
	SetActiveFlag(true);
	//邪魔パネルの色(仮)
	CVector3 aLight = { 0.10f, 0.00f , 0.10f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}