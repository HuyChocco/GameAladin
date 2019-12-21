
#include "SceneLV1.h"
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
//#include "../GameComponents/Sound.h"
Scene *SceneLV1::__instance = NULL;
SceneLV1::SceneLV1() :Scene(0x9090b0, Scene::SceneName::Market)
{
	this->mapWidth = 2270;
	this->mapHeight = 1127;
	LoadContent((char*)"Resources\\Map\\lv1.tmx");

}

SceneLV1::~SceneLV1()
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

void SceneLV1::LoadContent(char* filePath)
{
	lifeHUD = LifeHUD::GetInstance();
	bulletHUD = BulletHUD::GetInstance();
	Sprite *sprite;
	Sprite *background_sprite_2;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 2270;
	sourceRect.top = 0;
	sourceRect.bottom = 1127;

	SpriteData spriteData;

	spriteData.width = 2270;
	spriteData.height = 1127;
	spriteData.x = 0;
	spriteData.y = 1127;
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
	background_sprite_data_2.height = 1127;
	background_sprite_data_2.x = 0;
	background_sprite_data_2.y = 1127;
	background_sprite_data_2.scale = 1;
	background_sprite_data_2.angle = 0;
	background_sprite_data_2.isLeft = true;
	background_sprite_2 = new Sprite(BACKGROUND_2, backgroundRect2, D3DCOLOR_XRGB(255, 0, 255));
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
				obj = new Land(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(),"static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "ground")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Ground(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(),"static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "woods")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Wood(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(),"static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "wall")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Wall(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(),"static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "roof")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Roof(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "chain")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Chain(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "stair")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Stair(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "stair");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "egg")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Egg(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "egg");
				_listItemObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "bottle")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Bowl(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "bottle");
				_listItemObject.push_back(obj);
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
		
		else if (groupObject->GetName() == "enemy1")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				GameObject* obj = new Enemy1(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "enemy1");
				_listEnemyObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "enemy2")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				GameObject* obj = new Enemy2(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "enemy2");
				_listEnemyObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "scoreobject1")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new ScoreObject1(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "scoreobject");
				_listScoreObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "scoreobject2")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new ScoreObject2(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "scoreobject");
				_listScoreObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "animnail")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new AnimNail(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "animball")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new AnimBall(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "animbrick")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new AnimBrick(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "static");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "pole")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				obj = new Pole(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "pole");
				_listStaticObject.push_back(obj);
			}

		}
		else if (groupObject->GetName() == "enemy3")
		{
			for (size_t iObject = 0; iObject < groupObject->GetNumObjects(); iObject++)
			{
				auto outObj = groupObjectList[iObject];
				//obj = new Enemy3(outObj->GetX(), outObj->GetY(), outObj->GetWidth(), outObj->GetHeight(), "enemy3");
				//_listEnemyObject.push_back(obj);
			}

		}
	}
	aladin = Aladin::GetInstance();
	viewport = Viewport::GetInstance();
	tiledmap = TiledMap::GetInstance();
	grid = Grid::GetInstance();
	//grid->AddStaticObjectsToGrid(_listStaticObject);//them static object vao grid
	//grid->AddEnemyObjectsToGrid(_listEnemyObject);
	//grid->AddScoreObjectsToGrid(_listScoreObject);
	//grid->AddItemObjectsToGrid(_listItemObject);
	grid->AddObjectsToGrid(_listStaticObject, _listEnemyObject, _listItemObject, _listScoreObject);
	
}

void SceneLV1::Update(float dt)
{
	
	Scene::Update(dt);
	aladin->Update(dt);
	lifeHUD->Update(dt);
	bulletHUD->Update(dt);
}

void SceneLV1::Draw()
{
	Graphics::GetInstance()->Draw(_backgroundTextures[0]);
	Scene::Draw();//vẽ chính
	aladin->Render();
	Graphics::GetInstance()->Draw(_backgroundTextures[1]);
	lifeHUD->Render();
	bulletHUD->Render();
}

Scene* SceneLV1::GetInstance()
{
	if (__instance == NULL)
		__instance = new SceneLV1();
	return __instance;
}