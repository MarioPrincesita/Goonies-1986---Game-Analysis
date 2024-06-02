#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	laser = nullptr;
	img_tiles = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	if (laser != nullptr)
	{
		laser->Release();
		delete laser;
		laser = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

	dict_rect[(int)Tile::WATER_1] = { 9 * n,   0, n, n };
	dict_rect[(int)Tile::WATER_2] = { 10 * n,  0, n, n };

	dict_rect[(int)Tile::DIRT_0] = { 0,  0, n, n };
	dict_rect[(int)Tile::DIRT_1] = { n,  0, n, n };
	dict_rect[(int)Tile::ROOF_0] = { 0, n, n, n };
	dict_rect[(int)Tile::ROOF_1] = { n, n, n, n };
	dict_rect[(int)Tile::ROOF_2] = { 0, 2 * n, n, n };
	dict_rect[(int)Tile::ROOF_3] = { n, 2 * n, n, n };
	dict_rect[(int)Tile::ROOF_4] = { n, 2 * n, -n, n };
	dict_rect[(int)Tile::ROOF_5] = { 0, n, -n, n };
	dict_rect[(int)Tile::RIFT_UL] = { 2 * n, 0, n, n };
	dict_rect[(int)Tile::RIFT_UM] = { 3 * n, 0, n, n };
	dict_rect[(int)Tile::RIFT_UR] = { 2 * n, 0, -n, n };
	dict_rect[(int)Tile::RIFT_DL] = { 2 * n, n, n, n };
	dict_rect[(int)Tile::RIFT_DM] = { 3 * n, n, n, n };
	dict_rect[(int)Tile::RIFT_DR] = { 2 * n, n, -n, n };
	dict_rect[(int)Tile::WALL_U_0_L] = { 7 * n, 4 * n, n, n };
	dict_rect[(int)Tile::WALL_U_1_L] = { 7 * n, 3 * n, n, n };
	dict_rect[(int)Tile::WALL_U_2_L] = { 7 * n, 2 * n, n, n };
	dict_rect[(int)Tile::WALL_U_0_R] = { 7 * n, 4 * n, -n, n };
	dict_rect[(int)Tile::WALL_U_1_R] = { 7 * n, 3 * n, -n, n };
	dict_rect[(int)Tile::WALL_U_2_R] = { 7 * n, 2 * n, -n, n };
	dict_rect[(int)Tile::WALL_D_0_L] = { 7 * n, 7 * n, n, n };
	dict_rect[(int)Tile::WALL_D_1_L] = { 7 * n, 6 * n, n, n };
	dict_rect[(int)Tile::WALL_D_2_L] = { 7 * n, 5 * n, n, n };
	dict_rect[(int)Tile::WALL_D_0_R] = { 7 * n, 7 * n, -n, n };
	dict_rect[(int)Tile::WALL_D_1_R] = { 7 * n, 6 * n, -n, n };
	dict_rect[(int)Tile::WALL_D_2_R] = { 7 * n, 5 * n, -n, n };
	dict_rect[(int)Tile::LADDER_0] = { 4 * n, 4 * n, n, n };
	dict_rect[(int)Tile::LADDER_1] = { 4 * n, 3 * n, n, n };
	dict_rect[(int)Tile::LADDER_2] = { 4 * n, 2 * n, n, n };
	dict_rect[(int)Tile::GROUND_U_0] = { 4 * n, 5 * n, n, n };
	dict_rect[(int)Tile::GROUND_U_1] = { 5 * n, 0, n, n };
	dict_rect[(int)Tile::GROUND_U_2] = { 6 * n, 0, n, n };
	dict_rect[(int)Tile::GROUND_U_3] = { 7 * n, 0, n, n };
	dict_rect[(int)Tile::GROUND_U_4] = { 5 * n, 0, -n, n };
	dict_rect[(int)Tile::GROUND_D_0] = { 5 * n, n, n, n };
	dict_rect[(int)Tile::GROUND_D_1] = { 6 * n, n, n, n };
	dict_rect[(int)Tile::GROUND_D_2] = { 7 * n, n, n, n };
	dict_rect[(int)Tile::GROUND_D_3] = { 5 * n, n, n, n };

	dict_rect[(int)Tile::LETTER_A] = { n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_B] = { 2 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_C] = { 3 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_D] = { 4 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_E] = { 5 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_F] = { 6 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_G] = { 7 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_H] = { 8 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_I] = { 9 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_J] = { 10 * n, 9 * n, n, n };
	dict_rect[(int)Tile::LETTER_K] = { 0, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_L] = { n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_M] = { 2 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_N] = { 3 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_O] = { 4 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_P] = { 5 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_Q] = { 6 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_R] = { 7 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_S] = { 8 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_T] = { 9 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_U] = { 10 * n, 10 * n, n, n };
	dict_rect[(int)Tile::LETTER_V] = { 0, 11 * n, n, n };
	dict_rect[(int)Tile::LETTER_W] = { n, 11 * n, n, n };
	dict_rect[(int)Tile::LETTER_X] = { 2 * n, 11 * n, n, n };
	dict_rect[(int)Tile::LETTER_Y] = { 3 * n, 11 * n, n, n };
	dict_rect[(int)Tile::LETTER_Z] = { 4 * n, 11 * n, n, n };
	dict_rect[(int)Tile::SPECIAL_SIGN] = { 10 * n, 8 * n, n, n };
	dict_rect[(int)Tile::DASH] = { 0, 9 * n, n, n };
	dict_rect[(int)Tile::INTERROGATIVE] = { 5 * n, 11 * n, n, n };
	dict_rect[(int)Tile::EXCLAMATION] = { 6 * n, 11 * n, n, n };
	dict_rect[(int)Tile::DOT] = { 7 * n, 11 * n, n, n };

	dict_rect[(int)Tile::UP_DASH] = { 0, 7 * n, n, n };
	dict_rect[(int)Tile::CHARACTER_ICON] = { n, 7 * n, n, n };
	dict_rect[(int)Tile::UP_DOUBLE_DASH] = { 2 * n, 7 * n, n, n };
	dict_rect[(int)Tile::SPACE_EMPTY_DASH] = { 3 * n, 7 * n, n, n };
	dict_rect[(int)Tile::SPACE_EMPTY] = { 4 * n, 7 * n, n, n };
	dict_rect[(int)Tile::LIFE_DASH_R] = { 5 * n, 7 * n, -n, n };
	dict_rect[(int)Tile::LIFE_DASH_L] = { 5 * n, 7 * n, n, n };
	dict_rect[(int)Tile::LIFE_DASH_M] = { 6 * n, 7 * n, n, n };

	dict_rect[(int)Tile::NUMBER_0] = { 0, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_1] = { n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_2] = { 2 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_3] = { 3 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_4] = { 4 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_5] = { 5 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_6] = { 6 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_7] = { 7 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_8] = { 8 * n, 8 * n, n, n };
	dict_rect[(int)Tile::NUMBER_9] = { 9 * n, 8 * n, n, n };

	//NEW TILES - ALPHA
	dict_rect[(int)Tile::DOORRED_1] = { 0, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_2] = { n, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_3] = { 2 * n, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_4] = { 3 * n, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_5] = { 4 * n, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_6] = { 5 * n, 12 * n, n, n };
	dict_rect[(int)Tile::DOORRED_7] = { 6 * n, 12 * n, n, n };

	dict_rect[(int)Tile::DOORGREEN_1] = { 0, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_2] = { n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_3] = { 2 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_4] = { 3 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_5] = { 4 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_6] = { 5 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_7] = { 6 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_8] = { 7 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_9] = { 8 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_10] = { 9 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_11] = { 10 * n, 13 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_12] = { 0, 14 * n, n, n };

	dict_rect[(int)Tile::DOORSKULL_1] = { n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_2] = { 2 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_3] = { 3 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_4] = { 4 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_5] = { 5 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_6] = { 6 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_7] = { 7 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_8] = { 8 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_9] = { 9 * n, 14 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_10] = { 10 * n, 14 * n, n, n };

	dict_rect[(int)Tile::ITEM_KEY] = { 10 * n, 2 * n, n, n };
	dict_rect[(int)Tile::ITEM_KEYHOLE] = { 10 * n, 3 * n, n, n };
	dict_rect[(int)Tile::POTION_GREEN] = { 10 * n, 4 * n, n, n };

	//blue levels
	dict_rect[(int)Tile::DIRT_BLUE_1] = { 0, 15 * n, n, n };
	dict_rect[(int)Tile::DIRT_BLUE_2] = { n, 15 * n, n, n };
	dict_rect[(int)Tile::ROOF_BLUE_1_TOP_R] = { 0, 16 * n, n, n };
	dict_rect[(int)Tile::ROOF_BLUE_1_TOP_L] = { 0, 16 * n, -n, n };
	dict_rect[(int)Tile::ROOF_BLUE_2] = { n, 16 * n, n, n };
	dict_rect[(int)Tile::ROOF_BLUE_3] = { 0, 17 * n, n, n };
	dict_rect[(int)Tile::ROOF_BLUE_4] = { n, 17 * n, n, n };

	dict_rect[(int)Tile::WALL_BLUE_LEFT_1] = { 7 * n, 17 * n, n, n };
	dict_rect[(int)Tile::WALL_BLUE_LEFT_2] = { 7 * n, 18 * n, n, n };
	dict_rect[(int)Tile::WALL_BLUE_LEFT_3] = { 7 * n, 19 * n, n, n };
	dict_rect[(int)Tile::WALL_BLUE_LEFT_4] = { 7 * n, 20 * n, n, n };
	dict_rect[(int)Tile::WALL_BLUE_LEFT_5] = { 7 * n, 21 * n, n, n };
	dict_rect[(int)Tile::WALL_BLUE_BOTTOM_LEFT_6] = { 7 * n, 22 * n, n, n };

	dict_rect[(int)Tile::WALL_BLUE_RIGHT_1] = { 7 * n, 17 * n, -n, n };
	dict_rect[(int)Tile::WALL_BLUE_RIGHT_2] = { 7 * n, 18 * n, -n, n };
	dict_rect[(int)Tile::WALL_BLUE_RIGHT_3] = { 7 * n, 19 * n, -n, n };
	dict_rect[(int)Tile::WALL_BLUE_RIGHT_4] = { 7 * n, 20 * n, -n, n };
	dict_rect[(int)Tile::WALL_BLUE_RIGHT_5] = { 7 * n, 21 * n, -n, n };
	dict_rect[(int)Tile::WALL_BLUE_BOTTOM_RIGHT_6] = { 7 * n, 22 * n, -n, n };

	dict_rect[(int)Tile::GROUND_BLUE] = { 4 * n, 20 * n, -n, n };
	dict_rect[(int)Tile::GROUND_BLUE_END_L] = { 5 * n, 15 * n, -n, n };
	dict_rect[(int)Tile::GROUND_BLUE_END_R] = { 5 * n, 15 * n, n, n };
	dict_rect[(int)Tile::SUB_GROUND_BLUE_END_L] = { 5 * n, 16 * n, -n, n };
	dict_rect[(int)Tile::SUB_GROUND_BLUE_END_R] = { 5 * n, 16 * n, n, n };

	dict_rect[(int)Tile::BRIDGE_BLUE] = { 7 * n, 15 * n, n, n };
	dict_rect[(int)Tile::BRIDGE_BLUE_IN] = { 6 * n, 15 * n, n, n };
	dict_rect[(int)Tile::BRIDGE_BLUE_SUB] = { 7 * n, 16 * n, n, n };
	dict_rect[(int)Tile::BRIDGE_BLUE_SUB_IN] = { 6 * n, 16 * n, n, n };

	dict_rect[(int)Tile::LADDER_BLUE] = { 4 * n, 18 * n, n, n };
	dict_rect[(int)Tile::LADDER_BLUE_UP] = { 4 * n, 17 * n, n, n };
	dict_rect[(int)Tile::LADDER_BLUE_DOWN] = { 4 * n, 19 * n, n, n };

	dict_rect[(int)Tile::LAVA_1] = { 0 * n, 19 * n, n, n };
	dict_rect[(int)Tile::LAVA_2] = { 1 * n, 19 * n, n, n };

	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_1] = { 0 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_2] = { 1 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_3] = { 2 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_4] = { 3 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_5] = { 4 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_6] = { 5 * n, 21 * n, n, n };
	dict_rect[(int)Tile::DOORRED_BLUEFLOOR_7] = { 6 * n, 21 * n, n, n };

	dict_rect[(int)Tile::DOORSKULL_BLUEFLOOR_1] = { 8 * n, 17 * n, n, n };
	dict_rect[(int)Tile::DOORSKULL_BLUEFLOOR_2] = { 9 * n, 17 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_BLUEFLOOR_1] = { 8 * n, 18 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_BLUEFLOOR_2] = { 9 * n, 18 * n, n, n };
	dict_rect[(int)Tile::DOORGREEN_BLUEFLOOR_3] = { 10 * n, 18 * n, n, n };

	//+3lvl extra tiles
	dict_rect[(int)Tile::WATER_NEW_1] = { 3 * n, 6 * n, n, n };
	dict_rect[(int)Tile::WATER_NEW_2] = { 4 * n, 6 * n, n, n };

	dict_rect[(int)Tile::PIPE_H] = { 8 * n, 20 * n, n, n };
	dict_rect[(int)Tile::PIPE_V] = { 9 * n, 20 * n, n, n };
	dict_rect[(int)Tile::PIPE_JOINT] = { 10 * n, 20 * n, n, n };
	dict_rect[(int)Tile::PIPE_TURN] = { 10 * n, 21 * n, n, n };
	dict_rect[(int)Tile::PIPE_FLOOR] = { 9 * n, 21 * n, n, n };
}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "images/tileset_0.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	laser = new Sprite(img_tiles);
	if (laser == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	laser->SetNumberAnimations(1);
	laser->SetAnimationDelay(0, ANIM_DELAY);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME0]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME1]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME2]);
	laser->SetAnimation(0);

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w * h;
	width = w;
	height = h;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
	laser->Update();
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y * width;
	if (idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
			return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST)  || 
		(Tile::SOLID_FIRST_1 <= tile && tile <= Tile::SOLID_LAST_1) || 
		(Tile::SOLID_FIRST_2 <= tile && tile <= Tile::SOLID_LAST_2) ||
		(Tile::SOLID_FIRST_3 <= tile && tile <= Tile::SOLID_LAST_3) ||
		(Tile::SOLID_FIRST_4 <= tile && tile <= Tile::SOLID_LAST_4) ||
		(Tile::SOLID_FIRST_5 <= tile && tile <= Tile::SOLID_LAST_5) ||
		(Tile::SOLID_FIRST_6 <= tile && tile <= Tile::SOLID_LAST_6) ||
		(Tile::SOLID_FIRST_7 <= tile && tile <= Tile::SOLID_LAST_7);
}
bool TileMap::IsTileLadderTop(Tile tile) const
{
	return tile == Tile::LADDER_2 || tile == Tile::LADDER_BLUE_UP;
}
bool TileMap::IsTileLadder(Tile tile) const
{
	return (tile == Tile::LADDER_0 || tile == Tile::LADDER_1) || (tile == Tile::LADDER_BLUE_DOWN || tile == Tile::LADDER_BLUE);
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int* py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE - 1;
		return true;
	}
	return false;
}
bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTileLadderTop(tile))
			return true;
	}
	return false;
}
bool TileMap::TestOnLadder(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;

	//Control points
	left = box.pos.x;
	right = box.pos.x;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadder(tile1) && IsTileLadder(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	return false;
}
bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;

	//Control points
	left = box.pos.x;
	right = box.pos.x;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadderTop(tile1) && IsTileLadderTop(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	return false;
}
int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
{
	int tx, ty;

	tx = pixel_x / TILE_SIZE;
	ty = pixel_y / TILE_SIZE;
	Tile tile = GetTileIndex(tx, ty);

	if ((tile == Tile::LADDER_0 || tile == Tile::LADDER_1 || tile == Tile::LADDER_2)|| (tile == Tile::LADDER_BLUE_DOWN || tile == Tile::LADDER_BLUE || tile == Tile::LADDER_BLUE_UP))		return tx * TILE_SIZE + TILE_SIZE;
	//else if (tile == Tile::LADDER_R || tile == Tile::LADDER_TOP_R)	return tx * TILE_SIZE;
	else
	{
		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
		return 0;
	}
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				if (tile != Tile::LASER)
				{
					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				}
				else if (tile == Tile::LASER)
				{
					laser->Draw((int)pos.x, (int)pos.y);
				}
			}
		}
	}
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_TILES);

	laser->Release();

	dict_rect.clear();
}