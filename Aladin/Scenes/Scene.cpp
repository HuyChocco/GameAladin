#include "Scene.h"

Scene::Scene(D3DCOLOR backgroundColor, Scene::SceneName name)
{
	this->_name = name;
	this->_backgroundColor = backgroundColor;
	LoadContent();
}

Scene::~Scene()
{
	if (viewport)
	{
		delete viewport;
		viewport = NULL;
	}

	if (tiledmap)
	{
		delete tiledmap;
		tiledmap = NULL;
	}
}

D3DCOLOR Scene::GetBackcolor()
{
	return _backgroundColor;
}

Grid * Scene::GetGrid()
{
	return grid;
}

Viewport* Scene::GetViewPort()
{
	return viewport;
}

void Scene::SetViewPort(Viewport* camera)
{
	this->viewport = camera;
}

TiledMap* Scene::GetTiledMap()
{
	return this->tiledmap;
}

void Scene::AddGameObjectToWeaponList(GameObject * gameObject)
{
	_listWeapon.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{

	if ((int)viewport != 0xDDDDDDDD)
		viewport->Update(deltaTime);
	grid->Update(deltaTime);
	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		//if (!_listWeapon[i]->IsVisible())
		//{
			//QuadTree::RemoveDynamicObject(_listWeapon[i]);
			//_listWeapon.erase(_listWeapon.begin() + i);
			//continue;
		//}
		//_listWeapon[i]->Update(deltaTime);
	}
}

void Scene::Draw()
{

	grid->Render();

}

Scene::SceneName Scene::GetSceneName()
{
	return _name;
}

