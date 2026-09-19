#include "Game.h"
#include "Engine.h"
#include "Planet.h"
#include "Sim History.h"
#include "Playback Renderer.h"
#include "UI/UI Bool.h"
#include "UI/UI String.h"
#include "raylib.h"
#include "raymath.h"
#define string std::string
using namespace Simulator;

void Game::GameLoop() {
    // Persistent
    Engine engine;
    PlaybackRenderer renderer;
    Camera2D camera;
    bool running = false;

    // Waiting only
    GameWaitingState waitingState = Waiting;
    Collidable* collided;
    Vector2 mousePressLocation;
    float dragThreshold = 5;

    // Running only
    
    string testString = "Ping";
    UIString element([&test = testString](){return test;}, [&test = testString](string value){test = value;});
    
    // Setup
    InitWindow(1280, 720, "Solar System Simulator!");
    SetExitKey(KEY_NULL);
    camera.offset = Vector2{640, 360};
    camera.target = Vector2{0, 0};
    camera.rotation = 0;
    camera.zoom = 1;

    Texture ghost = LoadTexture("/home/matt-knox/Documents/VS Code/Git/Solar-System-Simulator/Ghosts.png");
    ghost.width = 400;
    ghost.height = 400;

    while (!WindowShouldClose())
    {
        // Main Game Loop
        if (running) {

        } else {
            StartOfSwitch:
            switch (waitingState) {
                case Waiting: {
                    Vector2 mousePos = GetMousePosition();
                    std::vector<Collidable*> mouseCollisions;
                    if (element.IsHit(mousePos)) {
                        mouseCollisions.push_back(&element);
                    }
                    for (auto it = renderer.getPlanets()->begin(); it != renderer.getPlanets()->begin(); ++it) {
                        if (it->second.IsHit(mousePos)) {
                            mouseCollisions.push_back(&element);
                        }
                    }
                    if (mouseCollisions.size() != 0) {
                        collided = mouseCollisions.at(0);
                        collided->Hover();
                        waitingState = Hovering;
                        goto StartOfSwitch;
                    }
                break; }
                case Hovering: {
                    Vector2 mousePos = GetMousePosition();
                    if (collided->IsHit(mousePos)) {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            mousePressLocation = mousePos;
                            collided->StartClick();
                            waitingState = Clicking;
                            goto StartOfSwitch;
                        }
                    } else {
                        collided->UnHover();
                        collided = nullptr;
                        waitingState = Waiting;
                        goto StartOfSwitch;
                    }
                break; }
                case Clicking: {
                    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
                        collided->Activate();
                        if (collided->IsActivated()) {
                            waitingState = Updating;
                        } else {
                            collided->Hover();
                            waitingState = Hovering;
                        }
                        goto StartOfSwitch;
                    } else if (Vector2Distance(mousePressLocation, GetMousePosition()) > dragThreshold) {
                        waitingState = Dragging;
                        goto StartOfSwitch;
                    }
                break; }
                case Dragging: {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        collided->Drag();
                    } else {
                        collided->UnHover();
                        collided = nullptr;
                        waitingState = Waiting;
                        goto StartOfSwitch;
                    }
                break; }
                case Updating: {
                    collided->Update();
                    if (
                        (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !collided->IsHit(GetMousePosition()))
                        || IsKeyPressed(KEY_ENTER)
                        || IsKeyPressed(KEY_ESCAPE)
                    ) {
                        collided->Deactivate(IsKeyPressed(KEY_ESCAPE));
                        /* !! Handle error messages output by line above !! */
                        waitingState = Hovering;
                        goto StartOfSwitch;
                    }
                break; }
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            element.Draw(Vector2{20, 20});
        EndDrawing();
    }
    CloseWindow();
}