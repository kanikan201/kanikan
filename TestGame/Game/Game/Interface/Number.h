/*
	数字表示クラス
*/

#pragma once

namespace {
	const CVector2 InfoNumSize = { 30.0f, 40.0f };	//IF上でのサイズ
	const CVector2 ResultNumSize = { 66.0f, 88.0f };	//リザルト画面での文字サイズ
}


class Number : public IGameObject
{
public:
	Number();
	~Number();
	void Init(CVector2 numPos, CVector2 numSize);
	void Update() override;
	void NumSet(int n);	//表示する数字を設定
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite		m_number[10];		//数字のスプライト
	CTexture	m_numberTex[10];	//数字のテクスチャ
	int			num=0;				//表示する数字
};