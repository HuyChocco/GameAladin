#include "Enemy.h"

Enemy::Enemy()
{
	LoadResource();
}

void Enemy::LoadResource()
{

}

void Enemy::Reset()
{
	this->currentHealth = this->maxHealth;
	this->SetPositionX(this->startPositionX);
	this->SetPositionY(this->startPositionY);
	
}

void Enemy::SetState(eEnemyState state)
{
	this->eState = state;
}

void Enemy::Update(DWORD dt)
{

}

void Enemy::Render()
{

}

void Enemy::DisposeBoudingBox()
{
	BoundingBox tempBox;
	tempBox.x = tempBox.y = tempBox.width = tempBox.height = tempBox.vx = tempBox.vy = 0;
	this->SetBoundingBox(tempBox);
}
