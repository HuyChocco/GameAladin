#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "TiledMap.h"
#include "Grid.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/AnimBrick.h"
#include "../GameObjects/AnimBall.h"

#include "../GameObjects/Aladin.h"

#include <chrono>

class Graphics;
class Keyboard;
class Grid;
class Aladin;
class Scene;
class AnimBrick;
class AnimBall;
class Game
{
	bool initialized = false;

	static Game *__instance;
	static HINSTANCE hInstance;
	HWND hWnd;									
	
	Keyboard *keyboard;
	Graphics *graphics;

	Aladin *aladin;
	AnimBrick* animbrick;
	AnimBall* animball;
	TiledMap *tiledMap;
	Viewport *viewport;

	Grid *grid;

	Stage stage;
	Scene* scene;
public:
	Stage GetStage() { return this->stage; }
	void SetStage(int stage) { this->stage = (Stage)stage; }
	//Hàm khởi tạo game
	void Init();
	//Hàm tạo cửa sổ game
	HWND CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight);
	//Hàm xử lý các thông điệp
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//Hàm nạp các tài nguyên của game
	void LoadResources();

	//Hàm cập nhật game
	void Update(DWORD dt);
	//Hàm render game
	void Render();
	//Hàm run
	int Run();
	//Hàm lấy aladin
	Aladin *GetAladin();
	//Hàm lấy tiledmap
	TiledMap *GetTiledMap() { return tiledMap; }
	//Hàm lấy scene
	Scene *GetScene() { return scene; }

	void SetTileMap(TiledMap *tiledMap) {
		this->tiledMap = tiledMap;
	}

	void SetGrid(Grid *grid)
	{
		this->grid = grid;
	}
	//Hàm sweptAABB
	static float SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly);

	static Game *GetInstance();
	~Game();
};


