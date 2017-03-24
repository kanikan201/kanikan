#include "stdafx.h"
#include "Number.h"


Number::Number()
{

}


Number::~Number()
{
}

//������(�|�W�V����,�T�C�Y)
void Number::Init(CVector2 numPos, CVector2 numSize)
{
	for (int i = 0; i < 10; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/sprite/num/%d.png", i);
		m_numberTex[i].Load(filePath);

		m_number[i].Init(&m_numberTex[i]);
		m_number[i].SetSize(numSize);
		m_number[i].SetPivot({ 0.5f, 0.5f });

		m_number[i].SetPosition(numPos);
	}
}

void Number::Update()
{

}

//�������Z�b�g(�\������������)
void Number::NumSet(int n)
{
	num = n;
}

void Number::PostRender(CRenderContext& renderContext)
{
	m_number[num].Draw(renderContext);
}