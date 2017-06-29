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
	CSkinModel					skinModel;		//�X�L�����f��
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^

	CVector3					DownPos = { 0.0f,0.0f,-1.0f };	//�������̃x�N�g��
	CVector3					UpPos = { 0.0f,0.0f,1.0f };	//������̃x�N�g��
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