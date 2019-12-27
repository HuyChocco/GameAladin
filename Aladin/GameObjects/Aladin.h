#pragma once
#include "../GameComponents/GameObject.h"
#include "State.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "AladinState.h"
#include "Cherry.h"
class Cherry;
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
	State *climbTheLadderState;
	State *climbTheRopeState;
	State *playWhenStandState;
	State *hurtState;
	State *dieState;
	int stateNumber;

	bool isGrounded = false;
	bool isCrouching = false;
	bool isShieldUp = false;
	bool isThrowing;

	static vector<Animation *> animations;
	DWORD lastFrameTime;
	//vector<Cherry *> cherryList;
	
	int timeToTrans = 0;
	bool isHurting = false;
public:
	void SetIsHurting(bool isHurting) { this->isHurting = isHurting; }
	bool GetIsHurting() { return this->isHurting; }
	float bloodNum;
	float lifeNum;
	float score;
	float bulletAppleNum;
	float eggNum;
	Cherry* cherry;
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
	State *GetClimbTheLadderState();
	State *GetClimbTheRopeState();
	State *GetPlayWhenStandState();
	State *GetHurtState();
	State *GetDieState();
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
	void Climb();
	void PlayWhenStand();
	void ActionWhenStand();
	void Hurt();
	void Die();
	//set width,height cho collider object captain
	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}
	//void AddToCherryList(Cherry* cherry) 
	//{ 
		//this->cherryList.push_back(cherry);
	//}
	//vector<Cherry*> GetCherryList() {
	//	return this->cherryList;
	//}
	//void DestroyCherryList()
	//{
	//	this->cherryList.clear();
	//}
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
	

	//Hàm thiết lập time chuyển state
	void SetTimeToTrans(int time) { this->timeToTrans = time; }
	int GetTimeToTrans() { return this->timeToTrans; }
};