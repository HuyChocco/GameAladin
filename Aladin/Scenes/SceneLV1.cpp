
#include "SceneLV1.h"

//#include "../GameComponents/Sound.h"

SceneLV1::SceneLV1() :Scene(0x9090b0, Scene::SceneName::Market)
{
	char* filePath = new char[1000]{"Resources\\Map\\lv1_object.tmx"};

	LoadContent(filePath);
}

SceneLV1::~SceneLV1()
{
	for (size_t i = 0; i < _backgroundTextures.size(); i++)
	{
		delete _backgroundTextures[i];
		_backgroundTextures[i] = NULL;
	}
	_backgroundTextures.clear();

	
}

void SceneLV1::LoadContent(char* filePath)
{
	Tmx::Map* mMap = new Tmx::Map();
	mMap->ParseFile(filePath);
	for (size_t iGroupObject = 0; iGroupObject < mMap->GetNumObjectGroups(); iGroupObject++)
	{
		const Tmx::ObjectGroup* groupObject = mMap->GetObjectGroup(iGroupObject);
		if (!groupObject->IsVisible())
			continue;
		auto groupObjectList = groupObject->GetObjects();			// danh sách object có trong group object
		GameObject* obj;												// dùng để trỏ
		if (groupObject->GetName() == "land")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				//obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), eDirection::TOP, eLandType::SAND);
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "ground")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				//obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), eDirection::TOP, eLandType::SAND);
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "woods")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				//obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), eDirection::TOP, eLandType::SAND);
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "wall")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				//obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), eDirection::TOP, eLandType::SAND);
				_listStaticObject.push_back(obj);
			}

		}
	}

	aladin = Aladin::GetInstance();
	Sprite *sprite;
	Sprite *background_sprite_2;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 2271;
	sourceRect.top = 0;
	sourceRect.bottom = 1135;

	SpriteData spriteData;

	spriteData.width = 2271;
	spriteData.height = 1135;
	spriteData.x = 0;
	spriteData.y = 1135;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = true;
	sprite = new Sprite(BACKGROUND_1, sourceRect, NULL);

	sprite->SetData(spriteData);
	_backgroundTextures.push_back(sprite);
	//Tạo sprite background 2 cho game
	RECT backgroundRect2;

	backgroundRect2.left = 0;
	backgroundRect2.right = 2270;
	backgroundRect2.top = 0;
	backgroundRect2.bottom = 1127;

	SpriteData background_sprite_data_2;

	background_sprite_data_2.width = 2270;
	background_sprite_data_2.height = 1135;
	background_sprite_data_2.x = 0;
	background_sprite_data_2.y = 1135;
	background_sprite_data_2.scale = 1;
	background_sprite_data_2.angle = 0;
	background_sprite_data_2.isLeft = true;
	background_sprite_2 = new Sprite(BACKGROUND_2, backgroundRect2, D3DCOLOR_XRGB(255, 0, 255));
	background_sprite_2->SetData(background_sprite_data_2);

	_backgroundTextures.push_back(background_sprite_2);

	

	grid = Grid::GetInstance();

	viewport = Viewport::GetInstance();

	
}

void SceneLV1::Update(float dt)
{
	Scene::Update(dt);

	

}

void SceneLV1::Draw()
{
	Graphics::GetInstance()->Draw(_backgroundTextures[0]);
	Scene::Draw();//vẽ chính
	Graphics::GetInstance()->Draw(_backgroundTextures[1]);
}
