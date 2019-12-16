#pragma once
#include "../GameComponents/GameObject.h"
#include "State.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "AladinState.h"


class Aladin : public GameObject
{
	Aladin();//constructor của Captain
	~Aladin() { 
		delete __instance;
		__instance = NULL; 
	};
	static Aladin *__instance;//thành viên tĩnh captain

	State *idleState;//đứng yên
	State *walkState;//đi bộ
	State *jumpState;//nhảy
	State *stopState;
	State *attackState;
	State *state;
	State *fallingState;
	State *actionWhenStandState;
	State *jumpWhenPressingState;
	State *sitDownState;
	State *attackWhenSitDownState;
	State *throwCherryInTheAirState;
	State *throwCherryWhenStandState;

	int stateNumber;

	bool isGrounded = false;
	bool isCrouching = false;
	bool isShieldUp = false;
	bool isThrowing;

	static vector<Animation *> animations;
	DWORD lastFrameTime;
	//vector<Animation *> animations;
public:
	//Nạp các tài nguyên cho nhân vật
	void LoadResources();
	//Lấy thể hiện của đối tượng captain
	static Aladin *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }
	void SetIsShieldUp(bool isShieldUp) { this->isShieldUp = isShieldUp; }

	State *GetSate() { return this->state; }
	void SetState(State *state);
	//Lấy số trạng thái
	int GetStateNumber() { return this->stateNumber; }
	//Gán số trạng thái
	void SetStateNumber(int number) { this->stateNumber = number; }
	//Các hàm lấy trạng thái nhân vật và thiết lập số trạng thái nhân vật
	State *GetIdleState();
	State *GetWalkState();
	State *GetJumpState();
	State *GetStopState();
	State *GetAttackState();
	State *GetFallingState();
	State *GetActionWhenStandState();
	State *GetJumpWhenPressingState();
	State *GetSitDownState();
	State *GetAttackWhenSitDownState();
	State *GetThrowCherryInTheAirState();
	State *GetThrowCherryWhenStandState();
	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsShieldUp() { return isShieldUp; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
	bool IsThrowing() { return this->isThrowing; }
	//Hàm thiết lập trạng thái ném
	void SetThrowing(bool value) { this->isThrowing = value; }
	//Các hàm override từ lớp CaptainState
	void Idle();
	void Walk();
	void Stop();
	void Jump();
	void Attack();
	void Falling();
	void JumpWhenPressing();
	void SitDown();
	void AttackWhenSitDown();
	void ThrowCherryInTheAir();
	void ThrowCherryWhenStand();
	//set width,height cho collider object captain
	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	void Reset();
	//Hàm thiết lập trạng thái quay trái cho nhân vật
	void TurnLeft();
	//Hàm thiết lập trạng thái quay phải cho nhân vật
	void TurnRight();

	vector<Animation *> GetAnimationsList() { return animations; }
	//Hàm cập nhật captain
	void Update(DWORD dt) override;
	//Hàm render captain
	void Render() override;
	bool isHurting = false;
};