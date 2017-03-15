#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Player/Player.h"
#include "Camera.h"
#include "Map/Map.h"

/*!
 *@brief	ゲームシーン。
 */
class GameScene :
	public IGameObject
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();
	/*!
	 *@brief	開始関数。
	 *@details
	 * 初期化などをこの関数に実装してください。</br>
	 * この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	 * そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	 *@return	trueが帰ってきたら初期化完了。
	 */
	bool Start() override;
	/*!
	 *@brief	更新関数。
	 */
	void Update() override;
	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);

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
	Camera*				camera;						//!<カメラ。
	CLight					light;								//!<ライト。
	CSoundSource*		bgmSource;					//!<BGMソース。
	Player*					player;							//プレイヤー
	Map*					map;
};

extern GameScene* g_gameScene;
