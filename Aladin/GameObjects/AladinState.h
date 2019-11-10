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
public:
	AladinState(Aladin *aladin, int states);
	~AladinState();

	void Jump() override;
	void Idle() override;
	void Walk() override;
	void Stop() override;
	void Crouch() override;
	void ThrowShield() override;
	void Roll() override;
	void Kick() override;
	void StandHit() override;
	void CrouchHit() override;
	void SitOnShield() override;
	void Swing() override;
	void Wade() override;
	void ShieldUp() override;
	void GetHurt() override;
	void Dead() override;

	void Update(DWORD dt) override;
	void Render() override;
};
