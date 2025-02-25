#pragma once
#include <raylib.h>
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Object.h"
#include "Entity.h"
#include "Door.h"

enum class DebugMode { OFF, SPRITES_AND_HITBOXES, ONLY_HITBOXES, SIZE };

class Scene
{
public:
    Scene();
    ~Scene();

    AppStatus Init();
    void Update();
    void Render();
    void Release();
    int currentStage = 0;
    void end();
    bool youWin = false;
    bool youLose = false;
    bool CheckTp();

private:
    AppStatus LoadLevel(int stage);
    
    void CheckCollisions(); 
    void CheckEnemyCollisions();
    void ClearLevel();
    void RenderObjects() const;
    void RenderObjectsDebug(const Color& col) const;

    void RenderGUI() const;

    Player *player;
    TileMap *level;
    std::vector<Object*> objects;
    std::vector<Enemy*> enemies;
    Enemy* enemy_x;
    Camera2D camera;
    DebugMode debug;
    Sound  sfxItem;
    Door* door;
    bool teleport;
};

