#include "AladinState.h"
#include <math.h>

AladinState::AladinState(Aladin *aladin, int states)
{
	this->aladin = aladin;
	this->states = states;
}

AladinState::~AladinState()
{

}

void AladinState::Jump()
{
	int state = this->states;//lấy trạng thái hiện tại

	switch (state)
	{
	case ALADIN_ANI_CROUCH:
	case ALADIN_ANI_JUMP:
		break;
	case ALADIN_ANI_IDLE:
	case ALADIN_ANI_WALK:
	{
		if (aladin->IsGrounded())//kiểm tra nhân vật có ở trên mặt đất không
		{
			aladin->SetIsGrounded(false);//đổi cờ trên mặt đất thành false
			aladin->SetSpeedY(ALADIN_JUMP_SPEED_Y);//set vy=0.6f
			aladin->SetState(aladin->GetJumpState());//thiết lập lại số trạng thái cho nhân vật aladin
													   // và trả về trạng thái jump
		}
	}
	break;
	}
}

void AladinState::Idle()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_IDLE:
		break;
	case ALADIN_ANI_CROUCH:
	{
		aladin->SetIsCrouching(false);//Thay đổi cờ iscrounching
		aladin->SetState(aladin->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	case ALADIN_ANI_STOP:
	{
		aladin->SetSpeedX(0);//cho nhân vật dừng lại
		aladin->SetState(aladin->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	case ALADIN_ANI_WALK:
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
	case ALADIN_ANI_CROUCH:
	case ALADIN_ANI_JUMP:
		break;
	case ALADIN_ANI_IDLE:
	{
		aladin->SetSpeedX(ALADIN_WALK_SPEED * (aladin->IsLeft() ? -1 : 1));
		aladin->SetState(aladin->GetWalkState());
	}
	break;
	case ALADIN_ANI_WALK:
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

	case ALADIN_ANI_WALK:
	{
		aladin->SetState(aladin->GetStopState());
		aladin->GetAnimationsList()[ALADIN_ANI_STOP]->setIsStop(true);
		aladin->SetSpeedX(aladin->GetSpeedX() / 2);
	}
	break;
	}
}
void AladinState::Crouch()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_CROUCH:
	case ALADIN_ANI_JUMP:
		break;
	case ALADIN_ANI_IDLE:
	{
		aladin->SetIsCrouching(true);
		aladin->SetState(aladin->GetCrouchState());
	}
	break;
	case ALADIN_ANI_WALK:
	{
		aladin->SetSpeedX(0);
		aladin->SetIsCrouching(true);
		aladin->SetState(aladin->GetCrouchState());
	}
	break;
	}
}

void AladinState::ThrowShield()
{
	int state = this->states;
}

void AladinState::Roll()
{
	int state = this->states;
}

void AladinState::Kick()
{
	int state = this->states;
}

void AladinState::StandHit()
{
	int state = this->states;
}

void AladinState::CrouchHit()
{
	int state = this->states;
}

void AladinState::SitOnShield()
{
	int state = this->states;
}

void AladinState::Swing()
{
	int state = this->states;
}

void AladinState::Wade()
{
	int state = this->states;
}

void AladinState::ShieldUp()
{
	int state = this->states;

	switch (state)
	{
	case ALADIN_ANI_SHIELD_UP:
	case ALADIN_ANI_JUMP:
		break;
	case ALADIN_ANI_IDLE:
	{
		aladin->SetIsShieldUp(true);
		aladin->SetState(aladin->GetShieldUpState());
	}
	break;
	case ALADIN_ANI_WALK:
	{
		aladin->SetSpeedX(0);
		aladin->SetIsShieldUp(true);
		aladin->SetState(aladin->GetShieldUpState());
	}
	break;
	}
}

void AladinState::GetHurt()
{
	int state = this->states;
}

void AladinState::Dead()
{
	int state = this->states;
}

void AladinState::Update(DWORD dt)
{
	setDelta(dt);
	int state = this->states;//Lấy ra trạng thái nhân vật hiện tại
	switch (state)
	{
	case ALADIN_ANI_JUMP://Nhân vật nhảy
	{
		if (aladin->IsGrounded())//Nếu nhân vật trên mặt đất
		{
			aladin->SetState(aladin->GetIdleState());
		}
		if (aladin->GetPositionY() >= TiledMap::GetInstance()->GetHeight() + 20)
		{
			aladin->SetSpeedY(aladin->GetSpeedY() - ALADIN_GRAVITY);
		}
	}
	break;
	default:
		break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

#pragma region	Collide with brick
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();//Lấy ra danh sách các tiles hiện tại

	aladin->SetSpeedY(aladin->GetSpeedY() - ALADIN_GRAVITY);//vy của nhân vật luôn bị trừ 0.025f

	coEvents.clear();
	aladin->SetDt(dt);
	aladin->CalcPotentialCollisions(tiles, coEvents);//Tính toán khả năng đụng độ giữa tiles hiện tại và aladin object

	if (coEvents.size() == 0)//trường hợp không xảy ra đụng độ
	{
		float moveX = trunc(aladin->GetSpeedX()* dt);
		float moveY = trunc(aladin->GetSpeedY()* dt);
		aladin->SetPositionX(aladin->GetPositionX() + moveX);//cộng một lượng vx*dt vào position x của aladin
		aladin->SetPositionY(aladin->GetPositionY() + moveY);//cộng một lượng vx*dt vào position y của aladin
	}
	else //xảy ra đụng độ
	{
		float min_tx, min_ty, nx = 0, ny;

		aladin->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * aladin->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * aladin->GetSpeedY() * dt + ny * 0.4;

		aladin->SetPositionX(aladin->GetPositionX() + moveX);
		aladin->SetPositionY(aladin->GetPositionY() + moveY);


		if (nx != 0) aladin->SetSpeedX(0);
		if (ny != 0) aladin->SetSpeedY(0);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				aladin->SetIsGrounded(true);//Cho aladin dứng trên mặt đất
			}
		}
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
		spriteData.y = aladin->GetPositionY();
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
	case ALADIN_ANI_WALK:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_WALK]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_STOP:
	{
		aladin->GetAnimationsList()[ALADIN_ANI_STOP]->Render(spriteData);

	}
	break;
	/*case ALADIN_ANI_CROUCH:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_CROUCH]->Render(spriteData);
	}
	break;

	case ALADIN_ANI_JUMP:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_JUMP]->Render(spriteData);
	}
	break;

	case ALADIN_ANI_THROW_SHIELD:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_THROW_SHIELD]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_ROLL:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_ROLL]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_KICK:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_KICK]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_STAND_HIT:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_STAND_HIT]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_CROUCH_HIT:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_CROUCH_HIT]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_SIT_ON_SHIELD:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_SIT_ON_SHIELD]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_SWING:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_SWING]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_WADE:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_WADE]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_SHIELD_UP:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_SHIELD_UP]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_GET_HURT:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_GET_HURT]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_DEAD:
	{
		ALADIN->GetAnimationsList()[ALADIN_ANI_DEAD]->Render(spriteData);
	}
	break;*/
	}
}

