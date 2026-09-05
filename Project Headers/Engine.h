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
            
            void addPlanet(std::string name, Planet planet);
            void removePlanet(std::string name);

            Engine(float bigG = 0.01, float speedMultiplier = 0.1): bigG(bigG), accelerationMultiplier(speedMultiplier) {}

            void Tick(int ticks, std::function<void(int, Engine)>);
            void Tick(int ticks) { Tick(ticks, [](int, Engine){}); }
            
            // Converts a map into a set; only works on maps with no repeating second elements
            // My alternative for a map<String, Planet> deep copy
            template <typename K, typename V> 
            std::set<V> MapToSet(std::map<K, V> map) {
                std::set<V> set;
                for (auto it = map.begin(); it != map.end(); ++it) {
                    set.insert(it->second);
                }
                return set;
            }
    };
}

#endif