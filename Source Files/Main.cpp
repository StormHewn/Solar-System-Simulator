#include "Main.h"
#include "Engine.h"
#include "Planet.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace Simulator;

int main() {
    Engine engine(1.0f);
    engine.addPlanet("greg", Planet(GRAY, 40, {0,5}, Vector2{5,0}));
    engine.addPlanet("greg", Planet(GREEN, 400, {0,-5}, Vector2{0, 0.2f}));
    engine.removePlanet("greg");
    engine.removePlanet("greg");
}