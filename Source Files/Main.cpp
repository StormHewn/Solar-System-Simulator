#include "Engine.h"
#include "Planet.h"
#include "Sim History.h"
#include "Playback Renderer.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#define string std::string
using namespace Simulator;

enum WindowState {
    Waiting = 0,
    Running,
    Paused,
};

void RegisterPlanet(Engine* engine, std::map<string, PlanetSprite>* PlanetSpriteMap, string name, Planet planet, Color planetColor);

int main() {
    // Initialize Engine, Rederer, etc
    Engine engine(70, 0.01);
    std::map<string, PlanetSprite> planetSprites;
    RegisterPlanet(&engine, &planetSprites, "Sol", Planet(400, Vector2{0, 0}, Vector2{0, -0}), YELLOW);
    RegisterPlanet(&engine, &planetSprites, "Arrakis", Planet(40, Vector2{0, -40}, Vector2{-2.5, 0}), ORANGE);
    RegisterPlanet(&engine, &planetSprites, "Calidan", Planet(80, Vector2{0, 50}, Vector2{2, 0}), BLUE);
    SimHistory simHistory(engine.GetNamesofPlanets(engine.getPlanets()));
    PlaybackRenderer renderer(&simHistory, planetSprites);
    
    // Tick Engine, fill simHistory
    engine.Tick(100, [&sH = simHistory](int tick, Engine engine){
        sH.AddTickState(tick, engine);
    });
    
    // Initialize Window, setup raylib
    InitWindow(500, 500, "Solar System Simulator Draw Test");
    SetTargetFPS(60);
    Camera2D camera;
    camera.target = Vector2{0, 0};
    camera.offset = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0;
    camera.zoom = 1;
    
    // Render
    int tick = 0;
    enum WindowState solarSystemState = Waiting;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode2D(camera);

        // Check for window resizing and shift camera accordingly
        if (IsWindowResized()) {
            camera.offset = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        }
        
        switch (solarSystemState) {
            case Waiting:
                break;
            case Running:
                    ClearBackground(BLACK);
                    renderer.Draw(tick, 10);
                    tick++;
                    if (tick == 100) { solarSystemState = Waiting; tick = 0; }
                    break;
            case Paused:
                break;
            }

        EndMode2D();
        EndDrawing();
    }
        
        CloseWindow();
    }

void RegisterPlanet(Engine* engine, std::map<string, PlanetSprite>* planetSpriteMap, string name, Planet planet, Color planetColor) {
    Planet* newPlanetRef = engine->addPlanet(name, planet);
    planetSpriteMap->insert({name, PlanetSprite(newPlanetRef, planetColor)});
}