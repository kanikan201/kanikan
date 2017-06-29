#pragma once

class Rock : public IGameObject
{
public:
	Rock();
	~Rock();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();
	bool GetRockHit() {
		return RockHit;
	}
	void SetRockHit(bool flg) {
		RockHit = flg;
	}
	CVector3 GetPosition() {
		return position;
	}
	int GetRockidx() {
		return Rockidx;
	}
	bool GetDeleteflg() {
		return Deleteflg;
	}
private:
	CSkinModel					skinModel;		//スキンモデル
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ

	CVector3					DownPos = { 0.0f,0.0f,-1.0f };	//下方向のベクトル
	CVector3					UpPos = { 0.0f,0.0f,1.0f };	//上方向のベクトル
	CVector3					move = CVector3::Zero;
	CVector3					position;
	CQuaternion					rotation;
	float						timer = 0.0f;
	bool						RockHit = false;
	bool						RockChenge = false;
	int							Rockidx;
	bool						Deleteflg = false;
};

extern Rock* rock[2];