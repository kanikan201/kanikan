/*
	数字表示クラス
*/

#pragma once

namespace {
	const CVector2 InfoNumSize = { 30.0f, 40.0f };	//数字のサイズ
	const CVector2 ResultNumSize = { 66.0f, 88.0f };	//数字のサイズ
}

enum texState {
	isResult,
	isInfo,
};

class Number : public IGameObject
{
public:
	Number();
	~Number();
	void Init(texState tex, CVector2 numPos, CVector2 numSize= InfoNumSize);
	void Update() override;
	void NumSet(int n);
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite		m_number[10];		//数字のスプライト
	CTexture	m_numberTex[10];	//数字のテクスチャ
	int			num=0;				//表示する数字
};