#include "Planet.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <string>
#include <map>
#define string std::string
using namespace Simulator;

Planet::Planet(float mass, Vector2 pos, std::map<string, Planet> planets, float density) {
    // Calculate total momentum of all given planets
    Vector2 totalMomentum = {0, 0};
    std::map<string, Planet>::iterator it;
    // Iterate over map
    for(it = planets.begin(); it != planets.end(); ++it) {
        // Extract planet
        auto planet = it->second;
        Vector2 planetMomentum = Vector2Scale(planet.getVel(), planet.getMass());
        totalMomentum = Vector2Add(totalMomentum, planetMomentum);
    }

    // Calculate balancing velocity based on given mass
    Vector2 targetVel = Vector2Scale(totalMomentum, (-1 / mass));
}