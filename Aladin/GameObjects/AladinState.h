#pragma once
#include "State.h"
#include "../GameComponents/Constants.h"
#include "Aladin.h"
class Aladin;
class AladinState : public State
{
private:
	Aladin *aladin;
	int states;
	int prevState;
public:
	AladinState(Aladin *aladin, int states);
	~AladinState();

	void Jump() override;
	void JumpWhenPressing() override;
	void Idle() override;
	void Walk() override;
	void Stop() override;
	void Attack() override;
	void AttackWhenSitDown() override;
	void Falling() override;
	void ActionWhenStand() override;
	void SitDown() override;
	void ThrowCherryInTheAir() override;
	void ThrowCherryWhenStand() override;
	void Climb() override;
	void PlayWhenStand() override;

	void Update(DWORD dt) override;
	void Render() override;
	

};
