#include "Planet.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <string>
#include <map>
using namespace Simulator;

Planet::Planet(Color color, float mass, Vector2 pos, std::map<std::string, Planet> planets) {
    // Calculate total momentum of all given planets
    Vector2 totalMomentum = {0, 0};
    std::map<std::string, Planet>::iterator it;
    // Iterate over map
    for(it = planets.begin(); it != planets.end(); ++it) {
        // Extract planet
        auto planet = it->second;
        Vector2 planetMomentum = Vector2Scale(planet.getVel(), planet.getMass());
        totalMomentum = Vector2Add(totalMomentum, planetMomentum);
    }

    // Calculate balancing velocity based on given mass
    Vector2 targetVel = Vector2Scale(totalMomentum, (-1 / mass));

    Planet(color, mass, pos, targetVel);
}