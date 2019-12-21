#include "HubObject.h"
HudObject::HudObject(int id) 
{
	
}

HudObject::~HudObject()
{

}

void HudObject::init()
{
}

void HudObject::Update(DWORD dt)
{
	
}

void HudObject::Render()
{
	
}

RECT * HudObject::LoadRect(char * path)
{
	vector<RECT*> listRect;

	fstream f;

	f.open(path, ios::in);

	int number_of_rect;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_rect;

	RECT* arrayRect = new RECT[number_of_rect];
	for (int i = 0; i < number_of_rect; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		RECT* r = new RECT();
		stream_data >> r->left;
		stream_data >> r->top;
		stream_data >> r->right;
		stream_data >> r->bottom;


		RECT rect;
		rect.left = r->left;
		rect.right = r->right;
		rect.top = r->top;
		rect.bottom = r->bottom;


		arrayRect[i] = rect;
	}




	f.close();
	return arrayRect;
}