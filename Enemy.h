//#pragma once
//#include "Entity.h"
//
////Representation model size: 32x32
//#define ENEMY_X_FRAME_SIZE		32
////Logical model size: 24x30
//#define ENEMY_X_PHYSICAL_WIDTH	24
//#define ENEMY_X_PHYSICAL_HEIGHT	30
//
////Representation model size: 32x32
//#define ENEMY_Y_FRAME_SIZE		32
////Logical model size: 0x0
//#define ENEMY_Y_PHYSICAL_WIDTH	32
//#define ENEMY_Y_PHYSICAL_HEIGHT	26
//
//enum class EnemyType { ENEMY_X, ENEMY_Y };
//
//class Enemy : public Entity
//{
//public:
//	Enemy(const Point& p, int width, int height, int frame_width, int frame_height);
//	virtual ~Enemy();
//
//	//Draw the maximum visibility area of the enemy
//	void DrawVisibilityArea(const Color& col) const;
//
//	//Pure virtual functions, any class inheriting from this class must provide its own implementations
//
//	//Initialize the enemy with the specified look and area
//	virtual AppStatus Initialise() = 0;
//
//	//Update the enemy according to its logic, return true if the enemy must shoot
//	virtual bool Update(const AABB& box) = 0;
//
//protected:
//
//	Look look;
//};

#pragma once
#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 16x16
#define ENEMY_FRAME_SIZE		16

//Logical model size: 6x14
#define ENEMY_WIDTH				6
#define ENEMY_PHYSICAL_HEIGHT	6

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED				1

//Vertical speed while on a ladder
#define ENEMY_LADDER_SPEED		1

//Frame animation delay while on a ladder
#define ENEMY_LADDER_DELAY		(2*ANIM_DELAY)

//When jumping, initial jump speed and maximum falling speed
#define ENEMY_JUMP_FORCE		6

//Frame delay for updating the jump velocity
#define ENEMY_JUMP_DELAY		1

//Player is levitating when abs(speed) <= this value
#define ENEMY_LEVITATING_SPEED	1

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

#define ENEMY_EXPERIENCE		10

#define ENEMY_PUNTUATION		50

//Logic states
enum class StateEnem { IDLE, WALKING, JUMPING, DEAD  };
enum class LookEnem { RIGHT, LEFT };

//Rendering states
enum class EnemyAnim {
	IDLE_RIGHT, IDLE_LEFT, WALKING_RIGHT, WALKING_LEFT,
	NUM_ANIMATIONS
};

class Enemy : public Entity
{
public:
	Enemy(const Point& p, StateEnem s, LookEnem view);
	~Enemy();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);

	void InitScore();
	void IncrScore(int n);
	int GetScore();

	int GetX();
	int GetY();

	void Update();
	void DrawDebug(const Color& col) const;
	void Release();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;

	//Player mechanics
	void MoveX();
	void MoveY();
	void LogicJumping();
	void LogicClimbing();

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartFalling();
	void StartJumping();
	void StartClimbingUp();
	void StartClimbingDown();
	void ChangeAnimRight();
	void ChangeAnimLeft();

	//Jump steps
	bool IsAscending() const;
	bool IsLevitating() const;
	bool IsDescending() const;

	//Ladder get in/out steps
	bool IsInFirstHalfTile() const;
	bool IsInSecondHalfTile() const;

	StateEnem state;
	LookEnem look;
	int jump_delay;

	TileMap* map;

	int score;
};