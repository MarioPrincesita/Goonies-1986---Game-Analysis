#include "Door.h"
#include "Sprite.h"

//Representation model size: 32x32
#define DOOR_FRAME_SIZE_WIDTH	24
#define DOOR_FRAME_SIZE_HEIGHT	32

//Logical model size: 8x8
#define DOOR_WIDTH				8
#define DOOR_PHYSICAL_HEIGHT	8

Door::Door(const Point& p) 
    : Entity(p, DOOR_WIDTH, DOOR_PHYSICAL_HEIGHT, DOOR_FRAME_SIZE_WIDTH, DOOR_FRAME_SIZE_HEIGHT), map(nullptr), isopen(false) {}
Door::~Door() 
{
}
AppStatus Door::Initialise()
{
	int i;
	const int n = DOOR_FRAME_SIZE_WIDTH;
	const int h = DOOR_FRAME_SIZE_HEIGHT;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_DOOR_GREEN, "images/door_green.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_DOOR_GREEN));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for enemy sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)DoorAnim::NUM_ANIMATIONS);

	// Closed
	sprite->SetAnimationDelay((int)DoorAnim::CLOSED, ANIM_DELAY);
	sprite->AddKeyFrame((int)DoorAnim::CLOSED, { 0, 0, n, h });

	// Opened
	sprite->SetAnimationDelay((int)DoorAnim::OPEN, ANIM_DELAY);
	sprite->AddKeyFrame((int)DoorAnim::OPEN, { n, 0, n, h });

	sprite->SetAnimation((int)DoorAnim::CLOSED);

	return AppStatus::OK;
}
void Door::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	//TODO Change this so that the width and height are appropriate
	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), WINDOW_WIDTH - 90, 50, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Door::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
void Door::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
bool Door::IsOpen() const
{
	return isopen;
}
void Door::OpenDoor()
{
	SetAnimation((int)DoorAnim::OPEN);
}
void Door::Update()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Door::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_DOOR_GREEN);

	render->Release();
}
