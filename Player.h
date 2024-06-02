#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 16x16
#define PLAYER_FRAME_SIZE		16

//Logical model size: 6x14
#define PLAYER_PHYSICAL_WIDTH	10
#define PLAYER_PHYSICAL_HEIGHT	14

//Horizontal speed and vertical speed while falling down
#define PLAYER_SPEED			1

//Vertical speed while on a ladder
#define PLAYER_LADDER_SPEED		1

//Frame animation delay while on a ladder
#define ANIM_LADDER_DELAY		(2*ANIM_DELAY)

//When jumping, initial jump speed and maximum falling speed
#define PLAYER_JUMP_FORCE		6

//Frame delay for updating the jump velocity
#define PLAYER_JUMP_DELAY		3.0f

//Player is levitating when abs(speed) <= this value
#define PLAYER_LEVITATING_SPEED	4

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

#define TIME_DURATION_ATTACK	8

//Logic states
enum class State { IDLE, WALKING, JUMPING, FALLING, CLIMBING, ATTACK, DEAD };
enum class Look { RIGHT, LEFT };

//Rendering states
enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT,
	WALKING_LEFT, WALKING_RIGHT,
	JUMPING_LEFT, JUMPING_RIGHT,
	LEVITATING_LEFT, LEVITATING_RIGHT,
	FALLING_LEFT, FALLING_RIGHT,
	CLIMBING, CLIMBING_PRE_TOP, CLIMBING_TOP,
	SHOCK_LEFT, SHOCK_RIGHT,
	PUNCHING_LEFT, PUNCHING_RIGHT,
	TELEPORT_LEFT, TELEPORT_RIGHT,
	NUM_ANIMATIONS
};

class Stats
{
public:
	Stats();
	
	void IncrementScore(int score);
	void IncrementLives(int lives);
	void LoseLives();
	void IncrementExperience(int experience);

	//Getters
	int GetScore();
	int GetLives();
	int GetExperience();

	void DrawHealthBar();
	void DrawExperienceBar();


private:
	int score;
	int lives;
	int experience;
	Rectangle Bar;
	Rectangle RecLife;
	Rectangle RecExperience;
};

class Inventory
{
public:
private:

};

class Player: public Entity
{
public:
	Player(const Point& p, State s, Look view);
	~Player();
	
	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);

	void InitScore();
	void IncrScore(int n);
	int GetScore();

	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	void KeyRecollected();
	void KeyUsed();
	bool HasKey();
	int  GetGoonie();
	void IncreaseGoonie();
	State GetState() const;
	AABB GetHitboxAttacking() const;

	Stats* stats;
	AABB attackHitbox;

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;

	//Player mechanics
	void MoveX();
	void MoveY();
	void LogicJumping();
	void LogicClimbing();
	void LogicAttacking();

	//Animation management
	void SetAnimation(int id);
	PlayerAnim GetAnimation();
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartFalling();
	void StartJumping();
	void StartClimbingUp();
	void StartClimbingDown();
	void StartAttack();
	void ChangeAnimRight();
	void ChangeAnimLeft();

	//Jump steps
	bool IsAscending() const;
	bool IsLevitating() const;
	bool IsDescending() const;

	//Ladder get in/out steps
	bool IsInFirstHalfTile() const;
	bool IsInSecondHalfTile() const;

	bool hasKey;
	State state;
	Look look;
	int jump_delay;
	TileMap *map;
	int time;
	int score;
	int numGoonies = 0;
};

