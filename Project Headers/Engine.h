#include "Planet.h"
#include <set>
#include <functional>
#ifndef Solar_System_Simulator_Engine_H
#define Solar_System_Simulator_Engine_H

namespace Simulator {
    class Engine {
        private:
            float bigG;
            float accelerationMultiplier;

            std::map<std::string, Planet> planets;

            Vector2 CalculateAcceleration(Planet p1, Planet p2);
        public:
            float getBigG() { return bigG; }
            void setBigG(float bigG) { this->bigG = bigG; }

            float getSimSpeed() { return accelerationMultiplier; }
            void setSimSpeed(float simSpeed) { this->accelerationMultiplier = simSpeed; }

            auto getPlanets() { return planets; }
            auto getPlanet(std::string name) { return planets.at(name); }
            std::set<std::string> GetNamesofPlanets(std::map<std::string, Planet> planets);
            
            Planet* addPlanet(std::string name, Planet planet);
            void removePlanet(std::string name);

            Engine(float bigG = 0.01, float speedMultiplier = 0.1): bigG(bigG), accelerationMultiplier(speedMultiplier) {}

            void Tick(int ticks, std::function<void(int, Engine)>);
            void Tick(int ticks) { Tick(ticks, [](int, Engine){}); }

            std::set<Planet> MapToSet(std::map<std::string, Planet> map);
    };
}

#endif