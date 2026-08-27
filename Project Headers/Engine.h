#include "Planet.h"
#ifndef Solar_System_Simulator_Engine_H
#define Solar_System_Simulator_Engine_H

namespace Simulator {
    class Engine {
        private:
            float bigG;
            std::map<std::string, Planet> planets;
        public:
            float getBigG() { return bigG; }
            void setBigG(float bigG) { this->bigG = bigG; }

            auto getPlanets() { return planets; }
            
            void addPlanet(std::string name, Planet planet);
            void removePlanet(std::string name);

            Engine(float bigG): bigG(bigG) {}
    };
}

#endif