#include "AladinState.h"
#include <math.h>
#include "Hub/BulletHub.h"
AladinState::AladinState(Aladin *aladin, int states)
{
	this->aladin = aladin;
	this->states = states;
	
}

AladinState::~AladinState()
{
	aladin->GetAnimationsList().clear();
}

void AladinState::Jump()
{
	int state = this->states;//lấy trạng thái hiện tại

	switch (state)
	{

	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
		break;
	case ALADIN_ANI_HURT:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_IDLE:
	{
		if (aladin->IsGrounded())//kiểm tra nhân vật có ở trên mặt đất không
		{
			aladin->SetIsGrounded(false);//đổi cờ trên mặt đất thành false
			aladin->SetSpeedY(ALADIN_JUMP_SPEED_Y);//set vy=0.6f
			aladin->SetState(aladin->GetJumpState());//thiết lập lại số trạng thái cho nhân vật aladin
													   // và trả về trạng thái jump
		}
		break;
	}


	}
}
void AladinState::JumpWhenPressing()
{
	int state = this->states;//lấy trạng thái hiện tại

	switch (state)
	{

	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_CLIMB_THE_ROPE:
	case ALADIN_ANI_RUN:
	{
		if (aladin->IsGrounded())//kiểm tra nhân vật có ở trên mặt đất không
		{
			aladin->SetIsGrounded(false);//đổi cờ trên mặt đất thành false
			aladin->SetSpeedY(ALADIN_JUMP_SPEED_Y);//set vy=0.6f
			aladin->SetState(aladin->GetJumpWhenPressingState());
		}
		break;
	}

	}
}
void AladinState::Idle()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_HURT:
	case ALADIN_ANI_THROW_CHERRY_WHEN_STANDING:
	{
		aladin->SetSpeedX(0);
		aladin->SetState(aladin->GetIdleState());
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR:
	case ALADIN_ANI_SIT_DOWN:
	{
		aladin->SetState(aladin->GetIdleState());
		break;
	}
	case ALADIN_ANI_IDLE:
		break;
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	case ALADIN_ANI_CLIMB_THE_ROPE:
	case ALADIN_ANI_STOP:
	{
		aladin->SetSpeedX(0);//cho nhân vật dừng lại
		aladin->SetState(aladin->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	case ALADIN_ANI_ATTACK_WHEN_SIT_DOWN:
	case ALADIN_ANI_ATTACK:
	{
		aladin->SetSpeedX(0);
		aladin->SetState(aladin->GetIdleState());
	}
	break;

	case ALADIN_ANI_RUN:
	{
		aladin->SetSpeedX(0);//cho nhân vật dừng lại
		aladin->SetState(aladin->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	}
}

void AladinState::Walk()
{
	int state = this->states;
	switch (state)
	{
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:

		break;
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_CLIMB_THE_ROPE:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_HURT:
	{
		aladin->SetSpeedX(ALADIN_WALK_SPEED * (aladin->IsLeft() ? -1 : 1));
		aladin->SetState(aladin->GetWalkState());
	}
	break;

	case ALADIN_ANI_RUN:
	{
		aladin->SetSpeedX(ALADIN_WALK_SPEED * (aladin->IsLeft() ? -1 : 1));
	}
	break;
	}
}
void AladinState::Stop()
{
	int state = this->states;
	switch (state)
	{

	case ALADIN_ANI_RUN:
	{
		aladin->SetState(aladin->GetStopState());
		aladin->GetAnimationsList()[ALADIN_ANI_STOP]->setIsStop(true);
		aladin->SetSpeedX(0);
	}
	break;
	}
}

void AladinState::Attack()
{
	int state = this->states;
	switch (state)
	{
	case ALADIN_ANI_ATTACK:
		break;
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_HURT:
	{
		aladin->SetState(aladin->GetAttackState());
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->setIsAttack(true);
		Sound::getInstance()->Play(S_LOW_SWORD);
	}
	break;

	}
}
void AladinState::AttackWhenSitDown()
{
	int state = this->states;
	switch (state)
	{
	case ALADIN_ANI_ATTACK:
	case ALADIN_ANI_SIT_DOWN:
	case ALADIN_ANI_HURT:
	{
		aladin->SetState(aladin->GetAttackWhenSitDownState());
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->setIsAttack(true);
	}
	break;
	}
}
void AladinState::Falling()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_HURT:
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_RUN:
	{
		aladin->SetState(aladin->GetFallingState());

	}
	break;
	}
}
void AladinState::ActionWhenStand()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_HURT:
	case ALADIN_ANI_IDLE:
	{
		aladin->SetState(aladin->GetActionWhenStandState());
		aladin->GetAnimationsList()[ALADIN_ANI_ACTION_WHEN_STAND]->setIsActionWhenStand(true);
	}
	break;
	}
}

void AladinState::SitDown()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_SIT_DOWN:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_HURT:
	{
		aladin->SetState(aladin->GetSitDownState());
		aladin->GetAnimationsList()[ALADIN_ANI_SIT_DOWN]->setIsSitDown(true);
	}
	break;
	}
}
void AladinState::ThrowCherryInTheAir()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
	{
		aladin->SetState(aladin->GetThrowCherryInTheAirState());
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR]->setIsAttack(true);
	}
	break;
	}
}
void AladinState::ThrowCherryWhenStand()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_STOP:
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
	{
		aladin->SetState(aladin->GetThrowCherryWhenStandState());
		if (aladin->bulletAppleNum > 0)
		{
			if (aladin->cherry == NULL)
			{
				aladin->cherry = new Cherry();
			}

			
			aladin->bulletAppleNum--;
			BulletHUD::GetInstance()->SetText(aladin->bulletAppleNum);
		}
		else if (aladin->bulletAppleNum <= 0)
		{
			aladin->bulletAppleNum = 0;
		}
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->setIsAttack(true);
		Sound::getInstance()->Play(S_OBJECT_THROW);
	}
	break;
	}
}
void AladinState::Climb()
{
	int state = this->states;

	switch (state)
	{

	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	{
		aladin->SetState(aladin->GetClimbTheRopeState());

	}
	break;
	}
}
int countTimeToTrans = 0;
void AladinState::PlayWhenStand()
{
	int state = this->states;

	switch (state)
	{

	case ALADIN_ANI_ACTION_WHEN_STAND:
	{
		aladin->SetState(aladin->GetPlayWhenStandState());

	}
	break;
	}
}
void AladinState::Hurt()
{
	aladin->SetState(aladin->GetHurtState());
	Sound::getInstance()->Play(S_ALADDIN_HURT);
}
void AladinState::Die()
{
	aladin->SetState(aladin->GetDieState());
	Sound::getInstance()->Play(S_ALADDIN_HURT);
}
void AladinState::Update(DWORD dt)
{


	if (aladin->bloodNum <= 0)
	{
		aladin->SetIsActive(false);
		aladin->Die();
	}
	if (aladin->lifeNum < 0)
	{
		aladin->SetIsActive(false);
	}
		
	if (aladin->GetIsHurting())
	{
		aladin->bloodNum--;
		aladin->Hurt();
		aladin->SetIsHurting(false);
	}
	setDelta(dt);

	int state = this->states;//Lấy ra trạng thái nhân vật hiện tại

	switch (state)
	{
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS://Nhân vật nhảy
	{
		if (aladin->IsGrounded())//Nếu nhân vật trên mặt đất
		{
			Sound::getInstance()->Play(S_OOOH);
			aladin->SetState(aladin->GetIdleState());
			aladin->SetSpeedX(0);
		}

	}
	break;
	case ALADIN_ANI_IDLE:
	{
		if (aladin->IsGrounded())//Nếu nhân vật trên mặt đất
		{
			if (aladin->GetTimeToTrans() == 0)
			{
				aladin->SetTimeToTrans(100);

			}
			else if (aladin->GetTimeToTrans() == countTimeToTrans)
			{
				aladin->ActionWhenStand();//chuyển sang trạng thái mới
				countTimeToTrans = 0;
			}
			else
				countTimeToTrans++;

		}
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_STANDING:
	{

	}
	break;
	default:
		break;
	}

	

#pragma region	Collide with map
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<GameObject* > enemyObjects;
	vector<GameObject* > mapObjects;
	vector<GameObject* > itemObjects;
	//vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();//Lấy ra danh sách các tiles hiện tại
	vector<GameObject *> objects = Grid::GetInstance()->GetCurObjects();

	//vy của nhân vật luôn bị trừ 0.025f
	aladin->SetSpeedY(aladin->GetSpeedY() - ALADIN_GRAVITY);
	coEvents.clear();
	if (dt >= 40)
		dt = 40;
	aladin->SetDt(dt);
	if (aladin->cherry != NULL)
	{
		aladin->cherry->Update(dt);
		if (aladin->cherry->GetState() == CHERRY_EXPLOSION)
		{
			delete aladin->cherry;
			aladin->cherry = NULL;
		}
	}

	aladin->CheckMapCollision(objects, coEvents);


	if (coEvents.size() > 0) //xảy ra đụng độ
	{
		float min_tx, min_ty, nx = 0, ny;

		aladin->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * aladin->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * aladin->GetSpeedY() * dt + ny * 0.4;
		if (coEventsResult[0]->collisionID == 2)//chain
		{
			aladin->SetPositionX(coEventsResult[0]->coO->GetPositionX());
			aladin->Climb();
			aladin->SetPositionY(aladin->GetPositionY());

			moveY = 0;
		}
		aladin->SetPositionX(aladin->GetPositionX() + moveX);
		aladin->SetPositionY(aladin->GetPositionY() + moveY);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				aladin->SetSpeedY(0);
				aladin->SetIsGrounded(true);//Cho aladin dứng trên mặt đất
			}
		}
		else if (coEventsResult[0]->collisionID == 8)//animball1,2
		{
			if (ny == 1)
			{
				aladin->SetSpeedY(0);
				aladin->SetIsGrounded(true);//Cho aladin dứng trên mặt đất
			}
			if (nx != 0)
			{
				AnimBall* animball = dynamic_cast<AnimBall*>(coEventsResult[0]->coO);
				if (animball->GetIsDamage() == true)
				{
					aladin->bloodNum--;
					aladin->Hurt();
				}
			}
		}
		else if (coEventsResult[0]->collisionID == 11)//animnail
		{
			if (ny == 1)
			{
				aladin->SetSpeedY(0);
				aladin->SetIsGrounded(true);//Cho aladin dứng trên mặt đất
			}
			if (nx != 0)
			{
				AnimNail* animnail = dynamic_cast<AnimNail*>(coEventsResult[0]->coO);
				if (animnail->GetIsDamage() == true)
				{
					aladin->bloodNum--;
					aladin->Hurt();
				}
			}
		}
		else if (coEventsResult[0]->collisionID == 3 )//apple
		{
			coEventsResult[0]->coO->SetIsActive(false);
			++aladin->bulletAppleNum;
			BulletHUD::GetInstance()->SetText(aladin->bulletAppleNum);
			Sound::getInstance()->PlayNew(S_APPLE_COLLECT);
		}
		else if (coEventsResult[0]->collisionID == 4 )//egg
		{
			++aladin->eggNum;
			coEventsResult[0]->coO->SetIsActive(false);
			Sound::getInstance()->PlayNew(S_APPLE_COLLECT);
		}
		else if (coEventsResult[0]->collisionID == 5)//bottle
		{
			coEventsResult[0]->coO->SetIsActive(false);
			//Sound::getInstance()->PlayNew(S_APPLE_COLLECT);
		}
	}
	else //trường hợp không xảy ra đụng độ
	{

		float moveX = trunc(aladin->GetSpeedX()* dt);
		float moveY = trunc(aladin->GetSpeedY()* dt);
		aladin->SetPositionX(aladin->GetPositionX() + moveX);//cộng một lượng vx*dt vào position x của aladin
		aladin->SetPositionY(aladin->GetPositionY() + moveY);//cộng một lượng vx*dt vào position y của aladin
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion


}

void AladinState::Render()
{
	int state = this->states;

	SpriteData spriteData;
	if (this->aladin != NULL)
	{
		spriteData.width = ALADIN_SPRITE_WIDTH;
		spriteData.height = ALADIN_SPRITE_HEIGHT;
		spriteData.x = aladin->GetPositionX();
		spriteData.y = aladin->GetPositionY() - ALADIN_SPRITE_HEIGHT - 4;
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = aladin->IsLeft();
		spriteData.isFlipped = aladin->IsFlipped();
	}

	switch (state)
	{
	case ALADIN_ANI_IDLE:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_IDLE]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_IDLE]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_IDLE]->spriteData.height);

	}
	break;
	case ALADIN_ANI_RUN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_RUN]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_RUN]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_RUN]->spriteData.height);
	}
	break;
	case ALADIN_ANI_STOP:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_STOP]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_STOP]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_STOP]->spriteData.height);

	}
	break;
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS]->spriteData.height);
	}
	break;
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW]->spriteData.height);
	}
	break;
	case ALADIN_ANI_FALLING_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_FALLING_DOWN]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_FALLING_DOWN]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_FALLING_DOWN]->spriteData.height);
	}
	break;
	case ALADIN_ANI_ATTACK:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->spriteData.height);
	}
	break;
	case ALADIN_ANI_ACTION_WHEN_STAND:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ACTION_WHEN_STAND]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_ACTION_WHEN_STAND]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_ACTION_WHEN_STAND]->spriteData.height);
	}
	break;

	case ALADIN_ANI_SIT_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_SIT_DOWN]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_SIT_DOWN]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_SIT_DOWN]->spriteData.height);
	}
	break;
	case ALADIN_ANI_ATTACK_WHEN_SIT_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->spriteData.height);
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR]->spriteData.height);
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_STANDING:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->spriteData.height);

	}
	break;
	case ALADIN_ANI_CLIMB_THE_ROPE:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_CLIMB_THE_ROPE]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_CLIMB_THE_ROPE]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_CLIMB_THE_ROPE]->spriteData.height);

	}
	break;
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_PLAY_WITH_CHERRY]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_PLAY_WITH_CHERRY]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_PLAY_WITH_CHERRY]->spriteData.height);

	}
	break;
	case ALADIN_ANI_HURT:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_HURT]->Render(spriteData);
		//aladin->SetWidth(aladin->GetAnimationsList()[ALADIN_ANI_HURT]->spriteData.width);
		//aladin->SetHeight(aladin->GetAnimationsList()[ALADIN_ANI_HURT]->spriteData.height);
		if (aladin->GetAnimationsList()[ALADIN_ANI_HURT]->IsDone() == true)
		{
			aladin->Idle();
			aladin->GetAnimationsList()[ALADIN_ANI_HURT]->SetIsDone(false);
		}

	}
	break;
	case ALADIN_ANI_DIE:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_DIE]->Render(spriteData);
		if (aladin->GetAnimationsList()[ALADIN_ANI_DIE]->IsDone())
		{
			aladin->lifeNum--;
			aladin->Reset();
		}
	}
	break;
	}
	if (aladin->cherry != NULL)
	{
		aladin->cherry->Render();
	}

}

