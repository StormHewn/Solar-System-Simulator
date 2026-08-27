#include "Engine.h"
#include "Planet.h"
#include <map>
#include <string>
#include <stdexcept>
using namespace Simulator;

void Engine::addPlanet(std::string name, Planet planet) {
    // Search 
    auto it = planets.find(name);
    bool isAvailable = it == planets.end();
    if (isAvailable) {
        planets.insert({name, planet});
    } else {
        throw std::runtime_error("Planet called \'" + name + "\' already exists!");
    }
}

void Engine::removePlanet(std::string name) {
    auto it = planets.find(name);
    if (it != planets.end()) {
        planets.erase(name);
    } else {
        throw std::runtime_error("No planet called \'" + name + "\' found!");
    }
}