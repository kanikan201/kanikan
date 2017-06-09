/*
	アイテムインベントリ
*/

#pragma once
#include "Number.h"
class inventory : public IGameObject
{
public:
	inventory();
	~inventory();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
	void Delete();
	void Reset();
private:
	CSprite		sprite;		//スプライト
	CTexture	texture;	//テクスチャ

	Number*		num;
	
	int Num[6];
	int stageNum;
	int Count;

	bool flg = false;
};

