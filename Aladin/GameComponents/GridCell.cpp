#include "GridCell.h"
#include "Grid.h"
//Hàm thêm các tiles vào vector tiles của GridCell
void GridCell::InsertTiles(vector<Tile *> &output)
{
	output.insert(output.end(), this->tiles.begin(), this->tiles.end());
}
void GridCell::InsertObjects(vector<GameObject *> &output)
{
	
	if (output.size() > 0)
	{
		for (int j = 0; j < this->objects.size(); j++)
		{
			for (int i = 0; i < output.size(); i++)
			{
				if (output[i] == this->objects[j])
					return;
			}

			output.push_back(this->objects[j]);
		}
	}
	else
		output.insert(output.end(), this->objects.begin(), this->objects.end());

	
}
void GridCell::Update(DWORD dt)
{
	return;
}
void GridCell::Render()
{
	
	for (int i = 0; i < objects.size(); i++)
	{
		TiledMap::GetInstance()->RenderObject(objects[i]);
	}
}

GridCell::~GridCell()
{
}
