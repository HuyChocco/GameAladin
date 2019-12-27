#pragma once
#include "d3d9.h"

class Captain;
class State
{
protected:
	DWORD dt;
public:
	State();
	void setDelta(DWORD dt) { this->dt = dt; }
	virtual void Idle();
	virtual void Walk();
	virtual void Stop();
	virtual void Jump();
	virtual void JumpWhenPressing();
	virtual void Attack();
	virtual void AttackWhenSitDown();
	virtual void Falling();
	virtual void ActionWhenStand();
	virtual void SitDown();
	virtual void ThrowCherryInTheAir();
	virtual void ThrowCherryWhenStand();
	virtual void Climb();
	virtual void PlayWhenStand();
	virtual void Hurt();
	virtual void Update(DWORD dt);
	virtual void Render();
};