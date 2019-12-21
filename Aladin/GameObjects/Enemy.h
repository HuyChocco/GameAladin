#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Constants.h"

class Enemy : public GameObject
{
protected:
	eEnemyState eState;

	std::vector<Animation *> animations;

	EnemyType Type;

	int ID;

	int bloodCount;
	int bloodNum;


	int maxHealth;

	int currentHealth;

	

	bool isRender = true;

	int countRender = 0;

	int startPositionX;
	int startPositionY;
public:
	Enemy();
	void LoadResource();
	void SetState(eEnemyState state);

	eEnemyState GetEnumState() { return this->eState; }
	void SetEnumState(eEnemyState estate) { this->eState = estate; }

	int GetID() { return this->ID; }
	void SetID(int id) { this->ID = id; }
	
	int GetCurrentHealth() { return this->currentHealth; }
	void ResetHealth() { this->currentHealth = maxHealth; }

	void Reset();
	EnemyType GetType() { return this->Type; }

	vector<Animation *> GetAnimationList() { return this->animations; }

	
	bool isDead = false;

	
	void DisposeBoudingBox();

	bool IsFlipHorizontal() { return isFlipHorizontal ? true : false; }

	virtual void Update(DWORD dt);
	virtual void Render();
};