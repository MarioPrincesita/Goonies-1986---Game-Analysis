#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>

Game::Game()
{
    state = GameState::START_MENU;
    scene = nullptr;
    img_menu = nullptr;
    img_start_menu = nullptr;
    img_win = nullptr;
    img_lose = nullptr;
    musicLose = {};
    musicWin = {};
    musicStart_Menu = {};
    musicStage1 = {};
    musicStage2 = {};

    InitAudioDevice();


    target = {};
    src = {};
    dst = {};
}
Game::~Game()
{
    UnloadMusicStream(musicStage1);
    UnloadMusicStream(musicStage2);
    UnloadMusicStream(musicStart_Menu);
    UnloadMusicStream(musicWin);
    UnloadMusicStream(musicLose);
    CloseAudioDevice();

    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }
}
void Game::ToggleFullScreenWindow(int windowWidth, int windowHeight)
{
    if (!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetDisplayWidth(), GetDisplayHeight());
        ToggleFullscreen();
    }
    else {
        ToggleFullscreen();
        SetWindowSize(windowWidth, windowHeight);
    }
}
int Game::GetDisplayWidth()
{
    if (IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        return GetMonitorWidth(monitor);
    }
    else 
    {
        return GetScreenWidth();
    }
}
int Game::GetDisplayHeight()
{
    if (IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        return GetMonitorHeight(monitor);
    }
    else
    {
        return GetScreenWidth();
    }
}
AppStatus Game::Initialise(float scale)
{
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
    InitWindow((int)w, (int)h, "The Goonies");
    ToggleFullScreenWindow(WINDOW_WIDTH,WINDOW_HEIGHT);

    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (target.id == 0)
    {
        LOG("Failed to create render texture");
        return AppStatus::ERROR;
    }
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
    dst = { 0, 0, w, h };

    //Load resources
    if (LoadResources() != AppStatus::OK)
    {
        LOG("Failed to load resources");
        return AppStatus::ERROR;
    }


    musicStage1 = LoadMusicStream("music/stage1.ogg");
    musicStage2 = LoadMusicStream("music/stage2.ogg");
    musicStart_Menu = LoadMusicStream("music/Start_Menu.ogg");
    musicWin = LoadMusicStream("music/Win.ogg");
    musicLose = LoadMusicStream("music/Lose.ogg");

    PlayMusicStream(musicStart_Menu);


    //Set the target frame rate for the application
    SetTargetFPS(60);
    //Disable the escape key to quit functionality
    SetExitKey(0);

    return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
    ResourceManager& data = ResourceManager::Instance();

    if (data.LoadTexture(Resource::IMG_MENU, "images/Inicio_1.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu = data.GetTexture(Resource::IMG_MENU);
    if (data.LoadTexture(Resource::IMG_START, "images/init_screen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_start_menu = data.GetTexture(Resource::IMG_START);
    if (data.LoadTexture(Resource::IMG_WIN, "images/YOU_WIN.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_win = data.GetTexture(Resource::IMG_WIN);
    if (data.LoadTexture(Resource::IMG_LOOSE, "images/GAME_OVER.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_lose = data.GetTexture(Resource::IMG_LOOSE);

    return AppStatus::OK;
}
AppStatus Game::BeginPlay()
{
    scene = new Scene();
    if (scene == nullptr)
    {
        LOG("Failed to allocate memory for Scene");
        return AppStatus::ERROR;
    }
    if (scene->Init() != AppStatus::OK)
    {
        LOG("Failed to initialise Scene");
        return AppStatus::ERROR;
    }

    return AppStatus::OK;
}
void Game::FinishPlay()
{
    scene->Release();
    delete scene;
    scene = nullptr;
}
AppStatus Game::Update()
{
    if (state == GameState::START_MENU || state == GameState::MAIN_MENU)
    {
        PlayMusicStream(musicStart_Menu);
        UpdateMusicStream(musicStart_Menu);
    }
    else {

        StopMusicStream(musicStart_Menu);
    }
    if (state == GameState::YOU_WIN)
    {
        PlayMusicStream(musicWin);
        UpdateMusicStream(musicWin);
    }
    else {
        StopMusicStream(musicWin);
    }
    if (state == GameState::YOU_LOSE)
    {
        PlayMusicStream(musicLose);
        UpdateMusicStream(musicLose);
    }
    else {
        StopMusicStream(musicLose);
    }
    //Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
    if (WindowShouldClose()) return AppStatus::QUIT;

    switch (state)
    {
    case GameState::START_MENU:
        if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
        break;
    case GameState::MAIN_MENU:
        if (IsKeyPressed(KEY_ESCAPE)) state = GameState::START_MENU;
        if (IsKeyPressed(KEY_SPACE))
        {
            if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
            state = GameState::PLAYING;
        }
        break;

    case GameState::PLAYING:
        
        scene->end();

        if (scene->currentStage == 1 && !scene->youWin && !scene->youLose)
        {
            PlayMusicStream(musicStage1);
            UpdateMusicStream(musicStage1);
        }
        else {
            StopMusicStream(musicStage1);
        }
        if (scene->currentStage >= 2 && !scene->youWin && !scene->youLose)
        {
            PlayMusicStream(musicStage2);
            UpdateMusicStream(musicStage2);
        }
        else {
            StopMusicStream(musicStage2);
        }
        if (IsKeyPressed(KEY_W))
        {
            scene->youWin;
            state = GameState::YOU_WIN;
        }
        if (IsKeyPressed(KEY_L))
        {
            scene->youLose;
            state = GameState::YOU_LOSE;
        }
        if (IsKeyPressed(KEY_ESCAPE))
        {
            FinishPlay();
            state = GameState::MAIN_MENU;
        }
        else if (scene->youWin)
        {
            state = GameState::YOU_WIN;

        }
        else if (scene->youLose)
        {
            state = GameState::YOU_LOSE;

        }
        else
        {
            //Game logic
            scene->Update();

        }
        break;
    case GameState::YOU_WIN:
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
        break;
    case GameState::YOU_LOSE:
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
    }
    return AppStatus::OK;
}
void Game::Render()
{
    //Draw everything in the render texture, note this will not be rendered on screen, yet
    BeginTextureMode(target);
    ClearBackground(BLACK);

    switch (state)
    {
    case GameState::START_MENU:
        DrawTexture(*img_start_menu, 0, 0, WHITE);
        break;

    case GameState::MAIN_MENU:
        DrawTexture(*img_menu, 0, 0, WHITE);
        break;

    case GameState::PLAYING:
        scene->Render();
        break;

    case GameState::YOU_WIN:
        DrawTexture(*img_win, 0, 0, WHITE);
        break;

    case GameState::YOU_LOSE:
        DrawTexture(*img_lose, 0, 0, WHITE);
        break;
    }

    EndTextureMode();

    //Draw render texture to screen, properly scaled
    BeginDrawing();
    DrawTexturePro(target.texture, src, dst, { 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}
void Game::Cleanup()
{
    UnloadResources();
    CloseWindow();
}
void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_MENU);

    UnloadRenderTexture(target);
}