#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {

	// -1: area covered by an entity
	EMPTY = -1,
	//  0: air tile
	AIR = 0,

	// 0 < id < 90: static tiles
	DIRT_0 = 1, DIRT_1, ROOF_0, ROOF_1,
	ROOF_2, ROOF_3, ROOF_4, ROOF_5,
	RIFT_UL, RIFT_UM, RIFT_UR, RIFT_DL, RIFT_DM, RIFT_DR,
	WALL_U_0_L, WALL_U_1_L, WALL_U_2_L, WALL_U_0_R, WALL_U_1_R, WALL_U_2_R,
	WALL_D_0_L, WALL_D_1_L, WALL_D_2_L, WALL_D_0_R, WALL_D_1_R, WALL_D_2_R,

	GROUND_U_0 = 30, GROUND_U_1, GROUND_U_2, GROUND_U_3, GROUND_U_4,
	GROUND_D_0, GROUND_D_1, GROUND_D_2, GROUND_D_3,

	LADDER_0 = 27, LADDER_1, LADDER_2,

	WATER_1 = 40, WATER_2,

	//(new tiles - alpha)
	DOORRED_1 = 50, DOORRED_2, DOORRED_3, DOORRED_4, DOORRED_5, DOORRED_6, DOORRED_7,

	DOORGREEN_1 = 60, DOORGREEN_2, DOORGREEN_3, DOORGREEN_4, DOORGREEN_5, DOORGREEN_6,
	DOORGREEN_7, DOORGREEN_8, DOORGREEN_9, DOORGREEN_10, DOORGREEN_11, DOORGREEN_12,

	DOORSKULL_1 = 80, DOORSKULL_2, DOORSKULL_3, DOORSKULL_4, DOORSKULL_5, DOORSKULL_6,
	DOORSKULL_7, DOORSKULL_8, DOORSKULL_9, DOORSKULL_10,


	// 100 <= id < 200: special tiles
	ITEM_KEY = 100, ITEM_KEYHOLE,
	POTION_GREEN = 105, HELMET, BIG_HELMET,

	DOOR_ = 110,
	KEY_RED = 115, YELLOW_KEY, ITEM_APPLE, ITEM_CHILI,
	LASER = 120, LASER_FRAME0, LASER_FRAME1, LASER_FRAME2,

	// Letters 130 < 160
	LETTER_A = 130, LETTER_B, LETTER_C, LETTER_D, LETTER_E, LETTER_F,
	LETTER_G, LETTER_H, LETTER_I, LETTER_J, LETTER_K, LETTER_L,
	LETTER_M, LETTER_N, LETTER_O, LETTER_P, LETTER_Q, LETTER_R,
	LETTER_S, LETTER_T, LETTER_U, LETTER_V, LETTER_W, LETTER_X,
	LETTER_Y, LETTER_Z, SPECIAL_SIGN, DASH, INTERROGATIVE, EXCLAMATION, DOT,

	// Numbers 160 < 170
	NUMBER_0, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5,
	NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9,

	// Special Tiles 170 < 180
	UP_DASH, CHARACTER_ICON, SPACE_EMPTY_DASH, SPACE_EMPTY,
	LIFE_DASH_L, LIFE_DASH_R, LIFE_DASH_M, UP_DOUBLE_DASH,

	// id >= 100: entities' initial locations
	PLAYER = 200, SLOTH, GOONIE, FRATELLI, ENEMY_X, ENEMY_Y, DOOR,

	// new BLUE STATIC tiles id >= 300 -----------------------------------------------------------------------------------------
	DIRT_BLUE_1 = 300, DIRT_BLUE_2, ROOF_BLUE_1_TOP_R, ROOF_BLUE_1_TOP_L, ROOF_BLUE_2, ROOF_BLUE_3, ROOF_BLUE_4,

	WALL_BLUE_LEFT_1 = 310, WALL_BLUE_LEFT_2, WALL_BLUE_LEFT_3, WALL_BLUE_LEFT_4,
	WALL_BLUE_LEFT_5, WALL_BLUE_BOTTOM_LEFT_6,

	WALL_BLUE_RIGHT_1 = 316, WALL_BLUE_RIGHT_2, WALL_BLUE_RIGHT_3, WALL_BLUE_RIGHT_4,
	WALL_BLUE_RIGHT_5, WALL_BLUE_BOTTOM_RIGHT_6,

	GROUND_BLUE = 325, GROUND_BLUE_END_L, GROUND_BLUE_END_R, SUB_GROUND_BLUE_END_L, SUB_GROUND_BLUE_END_R,

	BRIDGE_BLUE = 330, BRIDGE_BLUE_IN, BRIDGE_BLUE_SUB, BRIDGE_BLUE_SUB_IN,

	LADDER_BLUE = 335, LADDER_BLUE_UP, LADDER_BLUE_DOWN,

	LAVA_1 = 340, LAVA_2,

	DOORRED_BLUEFLOOR_1 = 350, DOORRED_BLUEFLOOR_2, DOORRED_BLUEFLOOR_3, DOORRED_BLUEFLOOR_4, DOORRED_BLUEFLOOR_5,
	DOORRED_BLUEFLOOR_6, DOORRED_BLUEFLOOR_7,

	DOORSKULL_BLUEFLOOR_1 = 360, DOORSKULL_BLUEFLOOR_2, DOORGREEN_BLUEFLOOR_1, DOORGREEN_BLUEFLOOR_2, DOORGREEN_BLUEFLOOR_3,

	// stage 3+ new tiles id >= 400 --------------------------------------------------------------------------------------------
	WATER_NEW_1 = 400, WATER_NEW_2,

	PIPE_H = 405, PIPE_V, PIPE_JOINT, PIPE_TURN, PIPE_FLOOR,

	// -------------------------------------------------------------------------------------------------------------------------

	//Intervals
	STATIC_FIRST = DIRT_0,
	STATIC_LAST = WALL_D_2_R,
	SOLID_FIRST = DIRT_0,
	SOLID_LAST = WALL_D_2_R,
	SOLID_FIRST_1 = GROUND_D_1,
	SOLID_LAST_1 = GROUND_D_3,
	SOLID_FIRST_2 = DIRT_BLUE_1,
	SOLID_LAST_2 = WALL_BLUE_BOTTOM_RIGHT_6,
	SOLID_FIRST_3 = BRIDGE_BLUE_SUB,
	SOLID_LAST_3 = BRIDGE_BLUE_SUB_IN,
	SOLID_FIRST_4 = UP_DASH,
	SOLID_LAST_4 = UP_DASH,
	SOLID_FIRST_5 = WATER_NEW_1,
	SOLID_LAST_5 = WATER_NEW_2,
	SOLID_FIRST_6 = PIPE_H,
	SOLID_LAST_6 = PIPE_H,
	SOLID_FIRST_7 = PIPE_TURN,
	SOLID_LAST_7 = PIPE_TURN,
	SPECIAL_FIRST = DOOR,
	SPECIAL_LAST = LASER,
	ENTITY_FIRST = PLAYER,
	ENTITY_LAST = ENEMY_Y
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;

	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or tops.
	bool TestCollisionGround(const AABB& box, int* py) const;

	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;

	//Test if box is on ladder and update 'px' with the x-center position of the ladder
	bool TestOnLadder(const AABB& box, int* px) const;

	//Test if box is on ladder top and update 'px' with the x-center position of the ladder
	bool TestOnLadderTop(const AABB& box, int* px) const;

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool IsTileLadder(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;
	int GetLadderCenterPos(int pixel_x, int pixel_y) const;

	//Tile map
	Tile* map;

	//Size of the tile map
	int size, width, height;

	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite* laser;

	//Tile sheet
	const Texture2D* img_tiles;
};

