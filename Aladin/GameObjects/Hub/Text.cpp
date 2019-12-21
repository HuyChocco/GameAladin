#include "Text.h"
Text::Text(float x, float y, int distance, string fontName, string str, float scale)
{
	_x = x;
	_y = y;
	_distance = distance;
	_fontName = fontName;
	_scale = scale;

	this->setText(str);
}
void Text::Init()
{

	
}
void Text::setText(string text)
{
	this->clearText();

	_text = text;
	vector<char> chars(_text.begin(), _text.end());

	int distanceSum = 0;
	for (char c : chars)
	{
		
	}
}

void Text::SetPosition(float x,float y)
{
	int i = 0;
	_x = x;
	_y = y;
	
	for (auto image : _listChars)
	{
		
		i++;
	}
}

Text::~Text()
{
}

void Text::Render()
{
	
	for (auto c : _listChars)
	{
		
	}
}

void Text::Update(DWORD dt)
{

	
}

void Text::clearText()
{
	_listChars.clear();
	_text = "";
}
