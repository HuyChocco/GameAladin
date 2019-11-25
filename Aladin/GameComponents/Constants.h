#pragma once


//Tên ứng dụng
#define WINDOW_CLASS_NAME L"Aladin"
#define MAIN_WINDOW_TITLE L"Aladin"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

//Framerate tối đa
#define MAX_FRAME_RATE 90

//
enum Stage {
	STAGE_1,
	STAGE_2,
	STAGE_BOSS_1,
	STAGE_BOSS_2
};
enum ObjectType
{
	DEFAULT,
	GROUND,
	APPLE,
	ON_BUTTON,
	RIVER,
	SWING
};
//TiledMap
//
// MAP
//#define BACKGROUND_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_1 L"Resources\\TiledMap\\SultansDungeonBackGround1.png"
#define BACKGROUND_2 L"Resources\\TiledMap\\SultansDungeonBackGround2.png"
#define BACKGROUND_BOSS_1 L"Resources\\TiledMap\\Map-Boss1.png"
#define BACKGROUND_BOSS_2 L"Resources\\TiledMap\\Map-Boss2.png"
// TILE
#define TILES_MATRIX_STAGE_1 L"Resources\\TiledMap\\map-copy.txt"
#define TILES_MATRIX_STAGE_2 L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_1 L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_2 L"Resources\\TiledMap\\Map-Boss2-Matrix.txt"

#define TILES_MATRIX_DELIMITER ","
#define TILES_WIDTH_PER_TILE	16
#define TILES_HEIGHT_PER_TILE	16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

#define GRID_SIZE 64
#define GRID_MAX_X 48
#define GRID_MAX_Y 5

//Giá trị tốc độ đi, tốc độ nhảy, trọng lực
#define ALADIN_WALK_SPEED		0.25f
#define ALADIN_JUMP_SPEED_Y		0.8f
#define ALADIN_GRAVITY			0.025f

//Animation của aladin
#define ALADIN_ANI_IDLE				0
#define ALADIN_ANI_WALK				1
#define ALADIN_ANI_STOP				2
#define ALADIN_ANI_JUMP_NO_KEY		3
#define ALADIN_ANI_JUMP_WITH_KEY 	4
#define ALADIN_ANI_FALLING_DOWN 	5
#define ALADIN_ANI_ATTACK			6
#define ALADIN_ANI_ACTION_WHEN_STAND 15



#define ALADIN_TEXTURE_LOCATION L"Resources\\Aladin\\aladin.png"
#define ALADIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(255, 0, 255)
#define ALADIN_SPRITE_WIDTH 44
#define ALADIN_SPRITE_HEIGHT 50

#define ANIMBRICK_TEXTURE_LOCATION L"Resources\\GameItem\\animbrick.png"
#define ANIMBRICK_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(163, 73, 164)
#define ANIMBRICK_SPRITE_WIDTH 44
#define ANIMBRICK_SPRITE_HEIGHT 50

#define ANIMBALL_TEXTURE_LOCATION L"Resources\\GameItem\\animball.png"
#define ANIMBALL_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(163, 73, 164)
#define ANIMBALL_SPRITE_WIDTH 44
#define ANIMBALL_SPRITE_HEIGHT 50

//Animation của Shield
#define SHIELD_SIDE 0
#define SHIELD_CENTER 1
#define SHIELD_UP 2
#define SHIELD_DOWN 3

#define SHIELD_WIDTH 16
#define SHIELD_HEIGHT 16
#define SHIELD_SPEED 0.125f