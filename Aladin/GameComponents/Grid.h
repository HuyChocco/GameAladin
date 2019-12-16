#pragma once
#include "GameObject.h"
#include "Constants.h" 
#include "GridCell.h"
#include "../GameObjects/Aladin.h"
#include "../GameObjects/Cherry.h"
#include <vector>

#include <fstream>
#include <string>

#define POSTOCELL(K) (int)(K/GRID_SIZE);
#define POSXTOCELL(K) (int)(K/GRID_SIZE);
#define POSYTOCELL(K) (int)(K % GRID_SIZE == 0 ? K/GRID_SIZE-1  : K/GRID_SIZE);

using namespace std;
class Aladin;
class Cherry;
class Cell;

typedef vector<GridCell *> CellRow;
typedef vector<CellRow> CellMatrix;
class Grid {
private:
	static Grid *__instance;// thành viên tĩnh
	int width, height;

	CellMatrix cells;

	vector<Tile *> curTiles;
	vector<GameObject *> curObjects;
	vector<GameObject *> curEnemyObjects;
	vector<Tile *> CollisionTiles;

	Viewport *viewport;
	Cherry * cherry;
	Aladin * aladin;
	vector<GameObject*> listStaticObject;
	vector<GameObject*> listEnemyObject;
	vector<GameObject*> listScoreObject;
	vector<GameObject*> listItemObject;
	Grid();

public:
	static Grid *GetInstance();
	Grid(int width, int height) { this->width = width; this->height = height; };
	void LoadCells();

	void GetCameraPosOnGrid(int &l, int &r, int &t, int &b);
	void GetAladinPosOnGrid(int &l, int &r, int &t, int &b);

	//vector<Tile *> GetCurTiles() { return this->curTiles; }
	vector<GameObject *> GetCurObjects() { return this->curObjects; }
	vector<GameObject *> GetCurEnemyObjects() { return this->curEnemyObjects; }
	vector<GameObject *> GetCurStaticObjects() { return this->listStaticObject; }
	//vector<Tile *> GetCollisionTiles() { return this->CollisionTiles; }
	void AddStaticObjectsToGrid(vector<GameObject*> &staticObjects);
	void AddEnemyObjectsToGrid(vector<GameObject*> &objects);
	void AddScoreObjectsToGrid(vector<GameObject*> &objects);
	void AddItemObjectsToGrid(vector<GameObject*> &objects);
	void AddObjectsToGrid(vector<GameObject*> &staticObjects, 
		vector<GameObject*> &enemyObjects, 
		vector<GameObject*> &itemObjects,
		vector<GameObject*> &scoreObjects);
	void Update(DWORD dt);
	void Render();

	CellMatrix GetTile() { return this->cells; }

	static void SetNewGrid()
	{
		__instance = NULL;
		__instance = new Grid();
	}
	~Grid() {
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				if (cells[i][j] != NULL)
					delete cells[i][j];
			}
	}
};