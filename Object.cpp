#include "Object.h"
#include "StaticImage.h"

Object::Object(const Point& p, ObjectType t) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t; 
	
	if (type == ObjectType::GOONIE)
	{
		frame_height = OBJECT_FRAME_SIZE_GOONIE;
	}
	else if (type == ObjectType::BIG_HELMET)
	{
		frame_width = 2 * OBJECT_FRAME_SIZE;
		frame_height = 2 * OBJECT_FRAME_SIZE;
	}

	Rectangle rc;
	const int n = TILE_SIZE;
	switch (type)
	{
		case ObjectType::APPLE: rc = {4*n, 3*n, n, n}; break;
		case ObjectType::CHILI: rc = {5*n, 3*n, n, n}; break;
		case ObjectType::KEY:   rc = {0, 0, n, n}; break;
		case ObjectType::KEYHOLE: rc = {n, 0, n, n}; break;
		case ObjectType::GOONIE: rc = { 2 * n,0,n,2*n }; break;
		case ObjectType::HELMET: rc = { 4 * n,0,n, n }; break;
		case ObjectType::BIG_HELMET: rc = { 5 * n,0,2*n, 2*n }; break;


		default: LOG("Internal error: object creation of invalid type");
	}

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ITEMS, "images/Items.png") != AppStatus::OK)
	{
	}

	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS),rc);
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
	}
}
Object::~Object()
{
}
void Object::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
ObjectType Object::GetType() const
{
	return type;
}
int Object::Points() const
{
	if (type == ObjectType::APPLE)		return POINTS_APPLE;
	else if (type == ObjectType::CHILI)	return POINTS_CHILI;
	else if (type == ObjectType::KEY)	return POINTS_KEY;

	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}