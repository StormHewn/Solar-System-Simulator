#include "Engine.h"
#include "Planet.h"
#include "raymath.h"
#include <map>
#include <set>
#include <string>
#include <functional>
#include <stdexcept>
#define string std::string
using namespace Simulator;

Planet* Engine::addPlanet(string name, Planet planet) {
    auto it = planets.find(name);
    bool isAvailable = (it == planets.end());
    if (isAvailable) {
        planets.insert({name, planet});
        auto it = planets.find(name);
        return &(it->second);
    } else {
        throw std::runtime_error("Planet called \'" + name + "\' already exists!");
    }
}

void Engine::removePlanet(string name) {
    auto it = planets.find(name);
    if (it != planets.end()) {
        planets.erase(name);
    } else {
        throw std::runtime_error("No planet called \'" + name + "\' found!");
    }
}

std::set<string> Engine::GetNamesofPlanets(std::map<string, Planet> planets) {
    std::set<string> planetList;
    for (auto mapEntry : planets) {
        planetList.insert(mapEntry.first);
    }
    return planetList;
}

void Engine::Tick(int ticks, std::function<void(int, Engine)> postTickFunc) {
    for (int tickCounter = 0; tickCounter < ticks; tickCounter++) {
        auto oldPlanets = MapToSet(planets);
        // Iterate over planets
        for (auto iter1 = planets.begin(); iter1 != planets.end(); ++iter1) {
            auto planet1 = iter1->second;
            auto totalAcceleration = Vector2Zero();
            // Iterate over planets again
            for (auto iter2 = oldPlanets.begin(); iter2 != oldPlanets.end(); ++iter2) {
                    auto planet2 = *iter2;
                    // Only execute if the two iterated planets don't match 
                    if (iter1->second != *iter2) {
                            // Calculate acceleration that planet 1 experieces from planet 2
                            Vector2 partialAcceleration = CalculateAcceleration(planet1, planet2);
                            totalAcceleration = Vector2Add(totalAcceleration, partialAcceleration);
                        }
                    }
                    // Add this acceleration onto the original planet's velocity, scaled by speed multiplier
                    auto truePlanet1 = &planets.at(iter1->first);
                    truePlanet1->setVel(Vector2Add(truePlanet1->getVel(), (Vector2Scale(totalAcceleration, accelerationMultiplier))));
                    truePlanet1->setPos(Vector2Add(truePlanet1->getPos(), truePlanet1->getVel()));
        }
        postTickFunc(tickCounter, *this);
    }
}

Vector2 Engine::CalculateAcceleration(Planet p1, Planet p2) {
    Vector2 VectorToP2 = Vector2Subtract(p2.getPos(), p1.getPos());
    float distanceToP2 = Vector2Length(VectorToP2);
    Vector2 directionToP2 = Vector2Normalize(VectorToP2);

    float scalarAccelleration = (bigG * p2.getMass() / (distanceToP2 * distanceToP2));
    Vector2 vectorAcceleration = Vector2Scale(directionToP2, scalarAccelleration);
    return vectorAcceleration;
}

// Converts a map into a set; only works on maps with no repeating second elements
// My alternative for a map<String, Planet> deep copy
std::set<Planet> Engine::MapToSet(std::map<string, Planet> map) {
    std::set<Planet> set;
    for (auto it = map.begin(); it != map.end(); ++it) {
        set.insert(it->second);
    }
    return set;
}