#include "AladinState.h"
#include <math.h>

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
	case ALADIN_ANI_CLIMB_THE_LADDER:
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
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_CLIMB_THE_LADDER:
	case ALADIN_ANI_IDLE:
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
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_RUN:
	{
		aladin->SetState(aladin->GetAttackState());
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->setIsAttack(true);
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
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_SIT_DOWN:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
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
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
	{
		aladin->SetState(aladin->GetThrowCherryWhenStandState());
		Cherry *cherry = new Cherry();
		aladin->AddToCherryList(cherry);
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->setIsAttack(true);
	}
	break;
	}
}
void AladinState::Climb()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	case ALADIN_ANI_ACTION_WHEN_STAND:
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	case ALADIN_ANI_RUN:
	case ALADIN_ANI_IDLE:
	{
		aladin->SetState(aladin->GetClimbTheLadderState());
		
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
void AladinState::Update(DWORD dt)
{
	
	setDelta(dt);
	
	int state = this->states;//Lấy ra trạng thái nhân vật hiện tại

	switch (state)
	{
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS://Nhân vật nhảy
	{
		if (aladin->IsGrounded())//Nếu nhân vật trên mặt đất
		{
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
	if (aladin->GetCherryList().size() > 0)
	{
		for (auto o : aladin->GetCherryList())
		{
			if (o->GetState() == CHERRY_EXPLOSION)
			{
				aladin->DestroyCherryList();
			}
			
		}
	}
	aladin->CheckMapCollision(objects, coEvents);
	

	if(coEvents.size()>0) //xảy ra đụng độ
	{
		float min_tx, min_ty, nx = 0, ny;

		aladin->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		 if (coEventsResult[0]->collisionID == 2)//stair
		{
			aladin->Climb();
			aladin->SetSpeedY(0);
		}
		float moveX = min_tx * aladin->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * aladin->GetSpeedY() * dt + ny * 0.4;

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
		
		else if (coEventsResult[0]->collisionID == 3|| 
			coEventsResult[0]->collisionID == 4|| coEventsResult[0]->collisionID == 5)//item
		{
			coEventsResult[0]->coO->SetIsActive (false);
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
		spriteData.y = aladin->GetPositionY()-ALADIN_SPRITE_HEIGHT -4;
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
	}
	break;
	case ALADIN_ANI_RUN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_RUN]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_STOP:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_STOP]->Render(spriteData);

	}
	break;
	case ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_FALLING_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_FALLING_DOWN]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_ATTACK:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_ACTION_WHEN_STAND:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ACTION_WHEN_STAND]->Render(spriteData);
	}
	break;
	
	case ALADIN_ANI_SIT_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_SIT_DOWN]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_ATTACK_WHEN_SIT_DOWN:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_THROW_CHERRY_WHEN_STANDING:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_THROW_CHERRY_WHEN_STANDING]->Render(spriteData);
		
	}
	break;
	case ALADIN_ANI_CLIMB_THE_LADDER:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_CLIMB_THE_LADDER]->Render(spriteData);

	}
	break;
	case ALADIN_ANI_PLAY_WITH_CHERRY:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_PLAY_WITH_CHERRY]->Render(spriteData);

	}
	break;
	}
	
	
}

