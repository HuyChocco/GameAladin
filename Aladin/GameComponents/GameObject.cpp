#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 0;
	collider.height = 0;
}
GameObject::GameObject(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = width;
	collider.height = height;
}

GameObject::~GameObject()
{
}

//Hàm cập nhật
void GameObject::Update(DWORD dt)
{

}
//Hàm render
void GameObject::Render()
{

}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float t, nx, ny;
	//Kiểm tra va chạm
	t = Game::SweptAABB(
		this->collider,
		coO->GetCollider(),
		nx,
		ny
	);

	LPCOLLISIONEVENT e = new CollisionEvent(t, nx, ny, coO);// sự kiện dụng độ
	return e;// Trả về con trỏ sự kiện va chạm
}
void GameObject::CheckEnemyCollision(vector<LPGAMEOBJECT>& enemies, vector<LPCOLLISIONEVENT>& coEvents)
{
	this->UpdateObjectCollider();
	LPGAMEOBJECT collisionEnemy;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive == true && enemies[i]->isDead == false)
		{
			collisionEnemy = enemies[i];


			LPCOLLISIONEVENT e = SweptAABBEx(collisionEnemy);
			e->collisionID = 1;

			if (e->t >= 0 && e->t < 1.0f && (e->ny == 1 ))
			{
				coEvents.push_back(e);
			}
			else
			{
				delete e;
			}
		}
	}
}

void GameObject::CheckMapCollision(
	vector<LPGAMEOBJECT> &coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	this->UpdateObjectCollider();
	LPGAMEOBJECT solidTileDummy;
	for (int i = 0; i < coObjects.size(); i++)
	{
		
		solidTileDummy = coObjects[i];
		

		
			LPCOLLISIONEVENT e = SweptAABBEx(solidTileDummy);//kiểm tra va chạm giữa gameobject mới và gameobject hiện tại
			
			if (solidTileDummy->GetType() == "stair")
			{
				if (e->t >= 0 && e->t < 1.0f )
				{
					e->collisionID = 2;
					coEvents.push_back(e);//va chạm thì thêm vào danh sách LPCOLLISIONEVENT
				}
				else
				{
					delete e;
				}
			}
			else
			{
				if (e->t >= 0 && e->t < 1.0f && (e->ny == 1 || e->nx == 1))
				{
					e->collisionID = 1;
					coEvents.push_back(e);//va chạm thì thêm vào danh sách LPCOLLISIONEVENT
				}
				else
				{
					delete e;
				}
			}
			
		
	}

}



void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) 
		{
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) 
		{
			min_ty = c->t; 
			ny = c->ny; 
			min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool GameObject::IsCollide(GameObject *CollisionObject)
{
	Collider MainObject = this->collider;
	RECT rec;
	rec.top = MainObject.y;
	rec.left = MainObject.x;
	rec.right = MainObject.x + MainObject.width;
	rec.bottom = MainObject.y - MainObject.height;

	Collider TargetObject = CollisionObject->collider;
	if (MainObject.direction == 1)
	{
		if (TargetObject.x > rec.left && TargetObject.x < rec.right )
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
		}
		else 
		{
			return false;
		}
	}
	else if (MainObject.direction == -1)
	{
		if (TargetObject.x + TargetObject.width > rec.left && TargetObject.x + TargetObject.width < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	return false;
}

void GameObject::UpdateObjectCollider()
{
	int direction = (isLeft == true) ? -1 : 1;
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.width = width;
	collider.height = height;
	collider.direction = direction;
}

void GameObject::UpdateTileCollider()
{
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	//collider.height = 8;
}
void GameObject::UpdateObjectBoundingBox()
{
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.vx = vx;
	boundingBox.vy = vy;
	boundingBox.dt = dt;
	boundingBox.width = width;
	boundingBox.height=height;
	if (isFlipped)
		boundingBox.direction = -1;
	else
		boundingBox.direction = 1;
}


RECT GameObject::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = y - height;
	return rect;
}