#pragma once
#include "../../GameComponents/GameObject.h"
#include "../Aladin.h"
class HudObject : public GameObject
{
public:
	HudObject() {};
	HudObject(int id);
	~HudObject();

	virtual void init();
	
	virtual void Update(DWORD dt);
	virtual void Render();
	RECT * LoadRect(char * path);
protected:
};
