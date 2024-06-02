//#include "Enemy.h"
//#include "Sprite.h"
//
//Enemy::Enemy(const Point& p, int width, int height, int frame_width, int frame_height) :
//	Entity(p, width, height, frame_width, frame_height)
//{
//	look = Look::LEFT;
//}
//Enemy::~Enemy()
//{
//}

#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Enemy::Enemy(const Point& p, StateEnem s, LookEnem view) : Entity(p, ENEMY_WIDTH, ENEMY_PHYSICAL_HEIGHT, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
{
	//Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE, PLAYER_FRAME_SIZE)

	state = s;
	look = view;
	map = nullptr;

}
Enemy::~Enemy()
{
}
AppStatus Enemy::Initialise()
{
	int i;
	const int n = ENEMY_FRAME_SIZE;
	const int h = ENEMY_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ENEMY, "images/enemy.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_ENEMY));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for enemy sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

	// Idle animations
	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::IDLE_RIGHT, { 0, 0, n, h });

	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::IDLE_LEFT, { 0, 0, -n, h });

	// Walking animations
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 2; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { (float)i * n, 0, n, h });

	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 2; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float)i * n, 0, -n, h });

	sprite->SetAnimation((int)EnemyAnim::IDLE_RIGHT);


	return AppStatus::OK;
}
int Enemy::GetX()
{
	return pos.x;
}
int Enemy::GetY()
{
	return pos.y;
}
void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
bool Enemy::IsLookingRight() const
{
	return look == LookEnem::RIGHT;
}
bool Enemy::IsLookingLeft() const
{
	return look == LookEnem::LEFT;
}
void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
EnemyAnim Enemy::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (EnemyAnim)sprite->GetAnimation();
}
void Enemy::Stop()
{
	dir = { 0,0 };
	state = StateEnem::IDLE;
	if (IsLookingRight())
	{
		SetAnimation((int)EnemyAnim::IDLE_RIGHT);
	}
	else
	{
		SetAnimation((int)EnemyAnim::IDLE_LEFT);
	}
}
void Enemy::StartWalkingLeft()
{
	state = StateEnem::WALKING;
	look = LookEnem::LEFT;
	SetAnimation((int)EnemyAnim::WALKING_LEFT);
}
void Enemy::StartWalkingRight()
{
	state = StateEnem::WALKING;
	look = LookEnem::RIGHT;
	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}
void Enemy::ChangeAnimRight()
{
	look = LookEnem::RIGHT;
	switch (state)
	{
	case StateEnem::IDLE:
		SetAnimation((int)EnemyAnim::IDLE_RIGHT);
		break;
	case StateEnem::WALKING:
		SetAnimation((int)EnemyAnim::WALKING_RIGHT);
		break;
	}
}
void Enemy::ChangeAnimLeft()
{
	look = LookEnem::LEFT;
	switch (state)
	{
	case StateEnem::IDLE:
		SetAnimation((int)EnemyAnim::IDLE_LEFT);
		break;
	case StateEnem::WALKING:
		SetAnimation((int)EnemyAnim::WALKING_LEFT);
		break;
	}
}
void Enemy::Update()
{

	MoveX();
	/*MoveY();*/


	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Enemy::MoveX()
{
	AABB box;
	int prev_x = pos.x;


	if (IsLookingRight())
	{
		pos.x += ENEMY_SPEED;
		if (state == StateEnem::IDLE)
		{
			StartWalkingRight();

		}
		else
		{
			if (IsLookingLeft()) ChangeAnimLeft();
		}

		box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			if (state == StateEnem::WALKING)
			{
				StartWalkingLeft();
			}
		}
	}
	else if (IsLookingLeft())
	{
		pos.x += -ENEMY_SPEED;
		if (state == StateEnem::IDLE)
		{
			StartWalkingLeft();

		}
		else
		{
			if (IsLookingRight()) ChangeAnimRight();
		}

		box = GetHitbox();
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			if (state == StateEnem::WALKING)
			{
				StartWalkingRight();
			}
		}
	}

}
//void Enemy::MoveY()
//{
//	AABB box;
//
//	pos.y += ENEMY_SPEED;
//	box = GetHitbox();
//	if (map->TestCollisionGround(box, &pos.y))
//	{
//		if (state == State::FALLING) Stop();
//
//		if (IsKeyDown(KEY_UP))
//		{
//			box = GetHitbox();
//			if (map->TestOnLadder(box, &pos.x))
//				StartClimbingUp();
//			else
//			{
//				StartJumping();
//			}
//		}
//		else if (IsKeyDown(KEY_DOWN))
//		{
//			//To climb up the ladder, we need to check the control point (x, y)
//			//To climb down the ladder, we need to check pixel below (x, y+1) instead
//			box = GetHitbox();
//			box.pos.y++;
//			if (map->TestOnLadderTop(box, &pos.x))
//			{
//				StartClimbingDown();
//				pos.y += PLAYER_LADDER_SPEED;
//				pos.x -= PLAYER_LADDER_SPEED;
//			}
//			else
//			{
//				StartCrouching();
//			}
//
//		}
//		else if (IsKeyPressed(KEY_SPACE))
//		{
//			Attack();
//		}
//		else if (IsKeyPressed(KEY_L))
//		{
//			Death();
//		}
//	}
//}

void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	//TODO Change this so that the width and height are appropriate
	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), WINDOW_WIDTH - 90, 50, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_ENEMY);

	render->Release();
}
//#include "Enemy.h"
//#include "Sprite.h"
//#include "TileMap.h"
//#include "Globals.h"
//#include <raymath.h>
//
//Enemy::Enemy(const Point& p, StateEnem s, LookEnem view) :
//	Entity(p, ENEMY_WIDTH, ENEMY_PHYSICAL_HEIGHT, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
//{
//	state = s;
//	look = view;
//	jump_delay = ENEMY_JUMP_DELAY;
//	map = nullptr;
//	score = 0;
//}
//Enemy::~Enemy()
//{
//}
//AppStatus Enemy::Initialise()
//{
//	int i;
//	const int n = ENEMY_FRAME_SIZE;
//
//	ResourceManager& data = ResourceManager::Instance();
//	if (data.LoadTexture(Resource::IMG_ENEMY, "images/enemy.png") != AppStatus::OK)
//	{
//		return AppStatus::ERROR;
//	}
//
//	render = new Sprite(data.GetTexture(Resource::IMG_ENEMY));
//	if (render == nullptr)
//	{
//		LOG("Failed to allocate memory for player sprite");
//		return AppStatus::ERROR;
//	}
//
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);
//
//	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_RIGHT, ANIM_DELAY);
//	sprite->AddKeyFrame((int)EnemyAnim::IDLE_RIGHT, {  0, 0, n, n });
//
//	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_LEFT, ANIM_DELAY);
//	sprite->AddKeyFrame((int)EnemyAnim::IDLE_LEFT, { 0, 0, -n, n });
//
//	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
//	for (i = 0; i < 2; ++i)
//		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { (float)i * n, 0, n, n });
//	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
//	for (i = 0; i < 2; ++i)
//		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float)i * n, 0, -n, n });
//	sprite->SetAnimation((int)EnemyAnim::IDLE_RIGHT);
//	
//	return AppStatus::OK;
//}
//void Enemy::InitScore()
//{
//	score = 0;
//}
//void Enemy::IncrScore(int n)
//{
//	score += n;
//}
//int Enemy::GetScore()
//{
//	return score;
//}
//void Enemy::SetTileMap(TileMap* tilemap)
//{
//	map = tilemap;
//}
//bool Enemy::IsLookingRight() const
//{
//	return look == LookEnem::RIGHT;
//}
//bool Enemy::IsLookingLeft() const
//{
//	return look == LookEnem::LEFT;
//}
//bool Enemy::IsAscending() const
//{
//	return dir.y < -ENEMY_LEVITATING_SPEED;
//}
//bool Enemy::IsLevitating() const
//{
//	return abs(dir.y) <= ENEMY_LEVITATING_SPEED;
//}
//bool Enemy::IsDescending() const
//{
//	return dir.y > ENEMY_LEVITATING_SPEED;
//}
//bool Enemy::IsInFirstHalfTile() const
//{
//	return pos.y % TILE_SIZE < TILE_SIZE;
//}
//bool Enemy::IsInSecondHalfTile() const
//{
//	return pos.y % TILE_SIZE >= TILE_SIZE;
//}
//void Enemy::SetAnimation(int id)
//{
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetAnimation(id);
//}
//EnemyAnim Enemy::GetAnimation()
//{
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	return (EnemyAnim)sprite->GetAnimation();
//}
////void Enemy::Stop()
////{
////	dir = { 0,0 };
////	state = State::IDLE;
////	if (IsLookingRight())	SetAnimation((int)PlayerAnim::IDLE_RIGHT);
////	else					SetAnimation((int)PlayerAnim::IDLE_LEFT);
////}
//void Enemy::StartWalkingLeft()
//{
//	state = StateEnem::WALKING;
//	look = LookEnem::LEFT;
//	SetAnimation((int)EnemyAnim::WALKING_LEFT);
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetAutomaticMode();
//}
//void Enemy::StartWalkingRight()
//{
//	state = StateEnem::WALKING;
//	look = LookEnem::RIGHT;
//	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetAutomaticMode();
//}
////void Enemy::StartFalling()
////{
////	dir.y = PLAYER_SPEED;
////	state = State::FALLING;
////	if (IsLookingRight())	SetAnimation((int)PlayerAnim::FALLING_RIGHT);
////	else					SetAnimation((int)PlayerAnim::FALLING_LEFT);
////}
//void Enemy::StartJumping()
//{
//	dir.y = -ENEMY_JUMP_FORCE;
//	state = StateEnem::JUMPING;
//	if (IsLookingRight())	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
//	else					SetAnimation((int)EnemyAnim::WALKING_LEFT);
//	jump_delay = ENEMY_JUMP_DELAY;
//}
////void Enemy::StartClimbingUp()
////{
////	state = State::CLIMBING;
////	SetAnimation((int)PlayerAnim::CLIMBING);
////	Sprite* sprite = dynamic_cast<Sprite*>(render);
////	sprite->SetManualMode();
////}
////void Enemy::StartClimbingDown()
////{
////	state = State::CLIMBING;
////	SetAnimation((int)PlayerAnim::CLIMBING_TOP);
////	Sprite* sprite = dynamic_cast<Sprite*>(render);
////	sprite->SetManualMode();
////}
//void Enemy::ChangeAnimRight()
//{
//	look = LookEnem::RIGHT;
//	switch (state)
//	{
//	case StateEnem::WALKING: SetAnimation((int)EnemyAnim::WALKING_RIGHT); break;
//	case StateEnem::JUMPING: SetAnimation((int)EnemyAnim::WALKING_RIGHT); break;
//	}
//}
//void Enemy::ChangeAnimLeft()
//{
//	look = LookEnem::LEFT;
//	switch (state)
//	{
//	case StateEnem::WALKING: SetAnimation((int)EnemyAnim::WALKING_LEFT); break;
//	case StateEnem::JUMPING: SetAnimation((int)EnemyAnim::WALKING_LEFT); break;
//	}
//}
//void Enemy::Update()
//{
//	//Player doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
//	//Instead, uses an independent behaviour for each axis.
//	MoveX();
//	//MoveY();
//
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->Update();
//}
//void Enemy::MoveX()
//{
//	AABB box;
//	int prev_x = pos.x;
//
//	//We can only go up and down while climbing
//	//if (state == State::CLIMBING)	return;
//	if (look == LookEnem::RIGHT)
//	{
//		pos.x += ENEMY_SPEED;
//		StartWalkingRight();
//
//		box = GetHitbox();
//		if (map->TestCollisionWallRight(box))
//		{
//			pos.x = prev_x;
//			StartWalkingLeft();
//		}
//	}
//	if (look == LookEnem::LEFT)
//	{
//		pos.x -= ENEMY_SPEED;
//		StartWalkingLeft();
//
//		box = GetHitbox();
//		if (map->TestCollisionWallLeft(box))
//		{
//			pos.x = prev_x;
//			pos.x += ENEMY_SPEED;
//			StartWalkingRight();
//		}
//	}
//}
////void Enemy::MoveY()
////{
////	AABB box;
////
////	if (state == State::JUMPING)
////	{
////		LogicJumping();
////	}
////	else if (state == State::CLIMBING)
////	{
////		LogicClimbing();
////	}
////	else //idle, walking, falling
////	{
////		pos.y += PLAYER_SPEED;
////		box = GetHitbox();
////		if (map->TestCollisionGround(box, &pos.y))
////		{
////			if (state == State::FALLING) Stop();
////
////			if (IsKeyDown(KEY_UP))
////			{
////				box = GetHitbox();
////				if (map->TestOnLadder(box, &pos.x))
////					StartClimbingUp();
////			}
////			else if (IsKeyDown(KEY_DOWN))
////			{
////				//To climb up the ladder, we need to check the control point (x, y)
////				//To climb down the ladder, we need to check pixel below (x, y+1) instead
////				box = GetHitbox();
////				box.pos.y++;
////				if (map->TestOnLadderTop(box, &pos.x))
////				{
////					StartClimbingDown();
////					pos.y += PLAYER_LADDER_SPEED;
////				}
////
////			}
////			else if (IsKeyPressed(KEY_SPACE))
////			{
////				StartJumping();
////			}
////		}
////		else
////		{
////			if (state != State::FALLING) StartFalling();
////		}
////	}
////}
////void Enemy::LogicJumping()
////{
////	AABB box, prev_box;
////	int prev_y;
////
////	jump_delay--;
////	if (jump_delay == 0)
////	{
////		prev_y = pos.y;
////		prev_box = GetHitbox();
////
////		pos.y += dir.y;
////		dir.y += GRAVITY_FORCE;
////		jump_delay = ENEMY_JUMP_DELAY;
////
////		//Is the jump finished?
////		if (dir.y > ENEMY_JUMP_FORCE)
////		{
////			dir.y = ENEMY_SPEED;
////			StartFalling();
////		}
////		else
////		{
////			//Jumping is represented with 3 different states
////			if (IsAscending())
////			{
////				if (IsLookingRight())	SetAnimation((int)PlayerAnim::JUMPING_RIGHT);
////				else					SetAnimation((int)PlayerAnim::JUMPING_LEFT);
////			}
////			else if (IsLevitating())
////			{
////				if (IsLookingRight())	SetAnimation((int)PlayerAnim::LEVITATING_RIGHT);
////				else					SetAnimation((int)PlayerAnim::LEVITATING_LEFT);
////			}
////			else if (IsDescending())
////			{
////				if (IsLookingRight())	SetAnimation((int)PlayerAnim::FALLING_RIGHT);
////				else					SetAnimation((int)PlayerAnim::FALLING_LEFT);
////			}
////		}
////		//We check ground collision when jumping down
////		if (dir.y >= 0)
////		{
////			box = GetHitbox();
////
////			//A ground collision occurs if we were not in a collision state previously.
////			//This prevents scenarios where, after levitating due to a previous jump, we found
////			//ourselves inside a tile, and the entity would otherwise be placed above the tile,
////			//crossing it.
////			if (!map->TestCollisionGround(prev_box, &prev_y) &&
////				map->TestCollisionGround(box, &pos.y))
////			{
////				Stop();
////			}
////		}
////	}
////}
////void Enemy::LogicClimbing()
////{
////	AABB box;
////	Sprite* sprite = dynamic_cast<Sprite*>(render);
////	int tmp;
////
////	if (IsKeyDown(KEY_UP))
////	{
////		pos.y -= PLAYER_LADDER_SPEED;
////		sprite->NextFrame();
////	}
////	else if (IsKeyDown(KEY_DOWN))
////	{
////		pos.y += PLAYER_LADDER_SPEED;
////		sprite->PrevFrame();
////	}
////
////	//It is important to first check LadderTop due to its condition as a collision ground.
////	//By doing so, we ensure that we don't stop climbing down immediately after starting the descent.
////	box = GetHitbox();
////	if (map->TestOnLadderTop(box, &tmp))
////	{
////		if (IsInSecondHalfTile())		SetAnimation((int)PlayerAnim::CLIMBING_PRE_TOP);
////		else if (IsInFirstHalfTile())	SetAnimation((int)PlayerAnim::CLIMBING_TOP);
////		else					LOG("Internal error, tile should be a LADDER_TOP, coord: (%d,%d)", box.pos.x, box.pos.y);
////	}
////	else if (map->TestCollisionGround(box, &pos.y))
////	{
////		//Case leaving the ladder descending.
////		Stop();
////		sprite->SetAutomaticMode();
////	}
////	else if (!map->TestOnLadder(box, &tmp))
////	{
////		//Case leaving the ladder ascending.
////		//If we are not in a LadderTop, colliding ground or in the Ladder it means we are leaving
////		//ther ladder ascending.
////		Stop();
////		sprite->SetAutomaticMode();
////	}
////	else
////	{
////		if (GetAnimation() != PlayerAnim::CLIMBING)	SetAnimation((int)PlayerAnim::CLIMBING);
////	}
////}
//void Enemy::DrawDebug(const Color& col) const
//{
//	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
//
//	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
//	DrawPixel(pos.x, pos.y, WHITE);
//}
//void Enemy::Release()
//{
//	ResourceManager& data = ResourceManager::Instance();
//	data.ReleaseTexture(Resource::IMG_ENEMY);
//
//	render->Release();
//}