#include "Planet.h"
#include <math.h>
#ifndef Solar_System_Simulator_PlanetSprite_H
#define Solar_System_Simulator_PlanetSprite_H

namespace Simulator {
    class PlanetSprite {
        private:
            Planet* linkedPlanet;
        public:
            Planet getPlanet() { return *linkedPlanet; }
            void linkPlanet(Planet* planet) { this->linkedPlanet = planet; }

            void Draw();

            void PushToTrail(Vector2 pos);
    };
}

#endif