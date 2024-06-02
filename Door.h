#include "Entity.h"
#include "TileMap.h"

enum class DoorAnim {OPEN, CLOSED, NUM_ANIMATIONS};
class Door : public Entity {
public:
	
	Door(const Point& p);
	~Door();
	
	AppStatus Initialise();
	void DrawDebug(const Color& col) const;
	void SetTileMap(TileMap* tilemap);
	void SetAnimation(int id);
	bool IsOpen() const;
	void OpenDoor();
	void Update();
	void Release();
	bool isopen;
private:
	TileMap* map;

};