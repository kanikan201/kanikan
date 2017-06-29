#pragma once
#include "MapChip.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Create(SMapInfo* mapLocInfo, int numObject);	//�}�b�v�쐬
	void Update();
private:
	bool Rockflg = false;
};