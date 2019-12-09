#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../GameComponents/Grid.h"
#include "../GameComponents/TiledMap.h"
class Scene;
class Grid;
class Viewport;
class TiledMap;

class Scene
{

private:
	//static Scene *__instance;// thành viên tĩnh
public:
	
	enum SceneName
	{
		None,
		Jafar,
		Market,
		CompleteScene,
		SelectScene
	};

	Scene(D3DCOLOR backgroundColor = 0x000000, Scene::SceneName name = None);
	virtual ~Scene();

	D3DCOLOR GetBackcolor();
	Grid* GetGrid();

	Viewport* GetViewPort();
	void SetViewPort(Viewport* camera);

	TiledMap* GetTiledMap();

	void AddGameObjectToWeaponList(GameObject*gameObject);

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LoadContent() {};
	int GetMapWidth() { return mapWidth; }
	int GetMapHeight() { return mapHeight; }
	void SetMapWidth(int width) { mapWidth = width; }
	void SetMapHeight(int height) { mapHeight = height; }
	Scene::SceneName GetSceneName();
	//static Scene *GetInstance();
protected:
	D3DCOLOR _backgroundColor;
	Grid* grid;
	int mapWidth;
	int mapHeight;
	Viewport* viewport;
	TiledMap* tiledmap;
	vector<GameObject*>_listStaticObject;
	vector<GameObject*> _listEnemyObject;
	vector<GameObject*> _listScoreObject;
	vector<GameObject*> _listItemObject;
	/*
	list gameObject phát sinh trong game. Vd: AppleWeapon
	thêm vào list đê gọi hàm Update
	*/
	std::vector<GameObject*> _listWeapon;

	Scene::SceneName _name;
};

