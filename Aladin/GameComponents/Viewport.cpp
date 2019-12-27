﻿#include "Viewport.h"
#include "Game.h"
#include "Debug.h"

Viewport *Viewport::__instance = NULL;

Viewport::Viewport()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	x = 0;
	y = 300;
}


Viewport::~Viewport()
{

}

RECT Viewport::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = (y - height);
	return rect;
}


Viewport *Viewport::GetInstance()
{
	if (__instance == NULL)
		__instance = new Viewport();
	return __instance;
}
void Viewport::Reset()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	x = 0;
	y = 300;
}
//Hàm cập nhật viewport theo nhân vật chính
void Viewport::Update(DWORD dt)
{
	Aladin * aladin = Aladin::GetInstance();
	/*int right = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() - SCREEN_WIDTH / 2);
	int left = (int)SCREEN_WIDTH / 2;
	int bottom = (int)(Game::GetInstance()->GetTiledMap()->GetHeight() - SCREEN_HEIGHT / 2 - 1);
	int top = (int)SCREEN_HEIGHT / 2;
	if (aladin->GetPositionX() > left && aladin->GetPositionX() < right)
	{
		this->x = aladin->GetPositionX() - left;
	}
	if (aladin->GetPositionY() > top && aladin->GetPositionY() < bottom)
	{
		this->y = aladin->GetPositionY() + top;
	}*/
	if (aladin->GetPositionX() > (int)SCREEN_WIDTH / 2 && aladin->GetPositionX() < (int)(Game::GetInstance()->GetTiledMap()->GetWidth() - SCREEN_WIDTH / 2))
	{
		this->x = aladin->GetPositionX() -(int) SCREEN_WIDTH / 2;
	}
	if (aladin->GetPositionY() > (int)SCREEN_HEIGHT / 2 && aladin->GetPositionY() <(int) (Game::GetInstance()->GetTiledMap()->GetHeight() - SCREEN_HEIGHT / 2-1))
	{
		this->y = aladin->GetPositionY()+  (int)SCREEN_HEIGHT / 2;
	}
}
//Hàm kiểm tra xem gameobject có trong viewport không
bool Viewport::IsObjectInCamera(GameObject *gameobject)
{
	RECT rec = GetRect();

	float GameObjectPosX = gameobject->GetPositionX();
	float GameObjectPosY = gameobject->GetPositionY();
	if (GameObjectPosX >= rec.left && GameObjectPosX <= rec.right && GameObjectPosY >= rec.bottom && GameObjectPosY <= rec.top)
		return true;
	return false;
}

void Viewport::SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1;
	mt._41 = -this->x;
	mt._42 = this->y;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;
	D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);
	D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}