
#include "SceneLV2.h"
#include "../GameObjects/Land.h"
#include "../GameObjects/Ground.h"
#include "../GameObjects/Wall.h"
#include "../GameObjects/Wood.h"
#include "../GameObjects/Roof.h"
#include "../GameObjects/Chain.h"
#include "../GameObjects/Bowl.h"
#include "../GameObjects/Apple.h"
#include "../GameObjects/Enemy1.h"
#include "../GameObjects/Enemy2.h"
#include "../GameObjects/ScoreObject1.h"
#include "../GameObjects/ScoreObject2.h"
#include "../GameObjects/Stair.h"
#include "../GameObjects/Egg.h"
#include "../GameObjects/AnimNail.h"
#include "../GameObjects/Pole.h"
#include "../GameObjects/Enemy3.h"
#include "../GameObjects/Boss1.h"
#include "../GameObjects/Boss2.h"
//#include "../GameComponents/Sound.h"
Scene *SceneLV2::__instance = NULL;
SceneLV2::SceneLV2() :Scene(0x9090b0, Scene::SceneName::Market)
{
	this->mapWidth = 750;
	this->mapHeight = 400;
	LoadContent((char*)"Resources\\Map\\lv2.tmx");

}

SceneLV2::~SceneLV2()
{
	for (size_t i = 0; i < _backgroundTextures.size(); i++)
	{
		delete _backgroundTextures[i];
		_backgroundTextures[i] = NULL;
	}
	_backgroundTextures.clear();
	for (size_t i = 0; i < _listStaticObject.size(); i++)
	{
		delete _listStaticObject[i];
		_listStaticObject[i] = NULL;
	}
	_listStaticObject.clear();
	for (size_t i = 0; i < _listEnemyObject.size(); i++)
	{
		delete _listEnemyObject[i];
		_listEnemyObject[i] = NULL;
	}
	_listEnemyObject.clear();
	for (size_t i = 0; i < _listScoreObject.size(); i++)
	{
		delete _listScoreObject[i];
		_listScoreObject[i] = NULL;
	}
	_listScoreObject.clear();
}

void SceneLV2::LoadContent(char* filePath)
{
	Sprite *sprite;
	Sprite *background_sprite_2;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 2000;
	sourceRect.top = 0;
	sourceRect.bottom = 800;

	SpriteData spriteData;

	spriteData.width = 2000;
	spriteData.height = 800;
	spriteData.x = 0;
	spriteData.y = 800;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = true;
	sprite = new Sprite(BACKGROUND_BOSS_2, sourceRect, NULL);

	sprite->SetData(spriteData);
	_backgroundTextures.push_back(sprite);
	//Tạo sprite background 2 cho game
	RECT backgroundRect2;

	backgroundRect2.left = 0;
	backgroundRect2.right = 750;
	backgroundRect2.top = 0;
	backgroundRect2.bottom = 400;

	SpriteData background_sprite_data_2;

	background_sprite_data_2.width = 750;
	background_sprite_data_2.height = 400;
	background_sprite_data_2.x = 0;
	background_sprite_data_2.y = 400;
	background_sprite_data_2.scale = 1;
	background_sprite_data_2.angle = 0;
	background_sprite_data_2.isLeft = true;
	background_sprite_2 = new Sprite(BACKGROUND_BOSS_1, backgroundRect2, D3DCOLOR_XRGB(255,255, 255));
	background_sprite_2->SetData(background_sprite_data_2);

	_backgroundTextures.push_back(background_sprite_2);

	////
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
				obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "land");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "ground")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Ground(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "ground");
				_listStaticObject.push_back(obj);
			}

		}
		
		else if (groupObject->GetName() == "wall")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Wall(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "wall");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "roof")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Roof(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "roof");
				_listStaticObject.push_back(obj);
			}

		}
		
		else if (groupObject->GetName() == "apple")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Apple(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "apple");
				_listItemObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "boss")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Boss1(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "boss");
				_listEnemyObject.push_back(obj);
			}

		}
		
	}
	aladin = Aladin::GetInstance();
	
	viewport = Viewport::GetInstance();
	tiledmap = TiledMap::GetInstance();
	grid = Grid::GetInstance();
	grid->AddObjectsToGrid(_listStaticObject, _listEnemyObject, _listItemObject, _listScoreObject);

}

void SceneLV2::Update(float dt)
{

	Scene::Update(dt);
	aladin->Update(dt);
	

}

void SceneLV2::Draw()
{
	Graphics::GetInstance()->Draw(_backgroundTextures[0]);
	
	Graphics::GetInstance()->Draw(_backgroundTextures[1]);
	Scene::Draw();//vẽ chính
	aladin->Render();
	
}

Scene* SceneLV2::GetInstance()
{
	if (__instance == NULL)
		__instance = new SceneLV2();
	return __instance;
}