#include"Grid.h"
#include "Game.h"

Grid *Grid::__instance = NULL;

Grid::Grid()
{
	curTiles.clear();

	//Luu viewport
	this->viewport = Viewport::GetInstance();

	//Lưu aladin
	this->aladin = Aladin::GetInstance();

	

}
void Grid::AddStaticObjectsToGrid(vector<GameObject*> &staticObjects)
{
	listStaticObject.assign( staticObjects.begin(), staticObjects.end());
	
}
void Grid::AddEnemyObjectsToGrid(vector<GameObject*> &objects)
{
	listEnemyObject.assign(objects.begin(), objects.end());
	
}
void Grid::AddScoreObjectsToGrid(vector<GameObject*> &objects)
{
	listScoreObject.assign(objects.begin(), objects.end());
	
}
void Grid::AddItemObjectsToGrid(vector<GameObject*> &objects)
{
	listItemObject.assign(objects.begin(), objects.end());

}
void Grid::AddObjectsToGrid(vector<GameObject*> &staticObjects,
	vector<GameObject*> &enemyObjects,
	vector<GameObject*> &itemObjects,
	vector<GameObject*> &scoreObjects)
{
	listStaticObject.assign(staticObjects.begin(), staticObjects.end());
	listEnemyObject.assign(enemyObjects.begin(), enemyObjects.end());
	listScoreObject.assign(scoreObjects.begin(), scoreObjects.end());
	listItemObject.assign(itemObjects.begin(), itemObjects.end());
	LoadCells();
}
void Grid::LoadCells()
{
	this->width = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() / 64) + 2;//Chiều rộng của Grid
	this->height = (int)(Game::GetInstance()->GetTiledMap()->GetHeight() / 64) + 2;//Chiều dài của Grid

	for (int i = 0; i < height; i++)
	{
		CellRow curRow;//1 hàng của Grid=vector các GridCell
		for (int j = 0; j < width; j++)
		{
			GridCell *curCell = new GridCell(j, i);
			curRow.push_back(curCell);
		}
		cells.push_back(curRow);//Thêm hàng trên vào ma trận Grid
	}
	
	for (auto obj : listStaticObject)
	{
		int cellX = POSXTOCELL((int)obj->GetPositionX());

		int cellY = POSYTOCELL((int)(obj->GetPositionY()));

		cells[cellY][cellX]->AddObject(obj);
	}
	for (auto obj : listEnemyObject)
	{
		int cellX = POSXTOCELL((int)obj->GetPositionX());

		int cellY = POSYTOCELL((int)(obj->GetPositionY()));

		cells[cellY][cellX]->AddObject(obj);
	}
	for (auto obj : listItemObject)
	{
		int cellX = POSXTOCELL((int)obj->GetPositionX());

		int cellY = POSYTOCELL((int)(obj->GetPositionY()));

		cells[cellY][cellX]->AddObject(obj);
	}
	for (auto obj : listScoreObject)
	{
		int cellX = POSXTOCELL((int)obj->GetPositionX());

		int cellY = POSYTOCELL((int)(obj->GetPositionY()));

		cells[cellY][cellX]->AddObject(obj);
	}
}

void Grid::GetAladinPosOnGrid(int &l, int &r, int &t, int &b)
{
	RECT rect = aladin->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}

void Grid::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = viewport->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}
//Hàm update của grid
void Grid::Update(DWORD dt)
{
	
	
	

	for (size_t i = 0; i < cells.size(); i++)
	{
		for (size_t j = 0; j < cells[i].size(); j++)
		{
			//cells[i][j]->clear();
		}
	}

	

	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);


	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{

			GridCell* cell = cells[i][j];
			if (cell->GetObjects().size() > 0)

			{
				
				cell->InsertObjects(curObjects);
				
			}

		}
	}
	for (auto obj : listItemObject)
	{
		if (viewport->IsObjectInCamera(obj))
		{
			obj->Update(dt);
		}
	}
	for (auto obj : listEnemyObject)
	{
		if (viewport->IsObjectInCamera(obj))
		{
			obj->Update(dt);
		}
		
	}
	for (auto obj : listScoreObject)
	{
		if (viewport->IsObjectInCamera(obj))
		{
			obj->Update(dt);
		}

	}
	
}

//Hàm render của Grid
void Grid::Render()
{
	
	
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);
	

	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{

			GridCell* cell = cells[i][j];
			if (cell->GetObjects().size() > 0)

			{
				for (auto obj : cell->GetObjects())
				{
					obj->Render();
				}
			}

		}
	}
	for (auto obj : listItemObject)
	{
		obj->Render();
	}
	for (auto obj : listEnemyObject)
	{
		obj->Render();
	}
	for (auto obj : listScoreObject)
	{
		obj->Render();
	}
	
}

Grid *Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}
