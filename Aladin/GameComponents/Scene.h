#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Grid.h"
#include "TiledMap.h"
class Grid;
class Scene;
class Viewport;
class TiledMap;
 class Scene
{


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

	Scene::SceneName GetSceneName();

protected:
	D3DCOLOR _backgroundColor;
	Grid* grid;

	Viewport* viewport;
	TiledMap* tiledmap;

	/*
	list gameObject phát sinh trong game. Vd: AppleWeapon
	thêm vào list đê gọi hàm Update
	*/
	std::vector<GameObject*> _listWeapon;

	Scene::SceneName _name;
};

