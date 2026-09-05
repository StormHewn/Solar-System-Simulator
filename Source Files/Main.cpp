#include "Main.h"
#include "Engine.h"
#include "Planet.h"
#include "Sim History.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace Simulator;

int main() {
    Engine engine;
    engine.addPlanet("greg", Planet(GRAY, 40, {0, 5}, Vector2{5, 0}));
    engine.addPlanet("jeff", Planet(RED, 80, {2, 50}, Vector2{50, 0}));
    engine.addPlanet("fred", Planet(GREEN, 400, {0, -5}, Vector2{0, 0.2f}));
    
    std::vector<std::string> planetList;
    for (auto mapEntry : engine.getPlanets()) {
        planetList.push_back(mapEntry.first);
    }
    SimHistory simHistory(planetList);
    engine.Tick(100, [&sH = simHistory](int tick, Engine engine){
        sH.AddTickState(tick, engine);
    });

    Vector2 jeffPos = simHistory.GetPlanetPos(99, "jeff");
    std::cout << jeffPos.x << ", " << jeffPos.y << std::endl;
}