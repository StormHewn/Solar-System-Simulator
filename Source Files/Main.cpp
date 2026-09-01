#include "Main.h"
#include "Engine.h"
#include "Planet.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace Simulator;

int main() {
    Engine engine;
    engine.addPlanet("greg", Planet(GRAY, 40, {0,5}, Vector2{5,0}));
    engine.addPlanet("fred", Planet(GREEN, 400, {0,-5}, Vector2{0, 0.2f}));

    std::cout << engine.getPlanet("greg").getPos().y << std::endl;
    std::cout << engine.getPlanet("fred").getPos().y << std::endl;
    
    engine.Tick(1);
    
    std::cout << engine.getPlanet("greg").getPos().y << std::endl;
    std::cout << engine.getPlanet("fred").getPos().y << std::endl;
}