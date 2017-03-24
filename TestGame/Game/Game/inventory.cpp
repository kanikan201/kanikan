#include "stdafx.h"
#include "inventory.h"

namespace {
	const CVector2 frameSize = { 650.0f, 120.0f }; //�g�̃T�C�Y(��)
	const CVector2 framePos = { -300.0f,-280.0f };		//�g�̈ʒu(��)
}

inventory::inventory()
{
}


inventory::~inventory()
{
}

bool inventory::Start()
{
	texture.Load("Assets/sprite/inventory.png");

	sprite.Init(&texture);
	sprite.SetSize(frameSize);
	sprite.SetPosition(framePos);

	return true;
}
void inventory::Update()
{
}
void inventory::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}
