/*
	ゲームシーン関数
*/

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera.h"
#include "Map/Map.h"

class GameScene :
	public IGameObject
{
public:

	GameScene();

	~GameScene();
	bool Start() override;
	/*!
	 *@brief	更新関数。
	 */
	void Update() override;
	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);

	//解放
	void Release();

	//ライト取得
	CLight& getLight() {
		return light;
	}

	//カメラ取得
	Camera* getCamera(){
		return camera;
	}

	//プレイヤー取得
	Player* getPlayer() {
		return player;
	}

private:
	Camera*				camera;				//カメラ
	CLight				light;				//ライト
	Player*				player;				//プレイヤー
	Map*				map;				//マップ
};

extern GameScene* g_gameScene;
