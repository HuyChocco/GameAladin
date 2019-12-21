#pragma once
#include "HubObject.h"
#define Distance 10				

class Text : public HudObject
{
public:
	// distance : khoản cách giữa các chữ
	Text(float x, float y, int distance, string fontName, string str, float scale = 1.0);
	~Text();
	void SetPosition(float x, float y);
	virtual void Init();
	virtual void Update(DWORD dt);
	virtual void Render();
	
	

	string getFrameName(string fontName, char c);

	void setText(string text);

	void clearText();

	
private:
	vector<Sprite*> _listChars;

	float _x, _y;
	int _distance;
	string _fontName;
	string _text;
	float _scale;

};
