#pragma once
#include "Entity.h"

#define OBJECT_PHYSICAL_SIZE	6
#define OBJECT_FRAME_SIZE		8
#define OBJECT_FRAME_SIZE_GOONIE	16

#define POINTS_APPLE	10
#define POINTS_CHILI	20
#define POINTS_KEY		200
#define POINTS_POTION	500
#define POINTS_GOONIE	2000

enum class ObjectType { APPLE, CHILI, KEY, KEYHOLE, POTION, HELMET, BIG_HELMET, GOONIE };

class Object : public Entity
{
public:
	Object(const Point& p, ObjectType t);
	~Object();

	ObjectType GetType() const;
	void DrawDebug(const Color& col) const;
	int Points() const;

protected:
	ObjectType type;
};

