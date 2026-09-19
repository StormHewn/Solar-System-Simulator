#include "Planet.h"
#include <math.h>
#ifndef Solar_System_Simulator_PlanetSprite_H
#define Solar_System_Simulator_PlanetSprite_H

namespace Simulator {
    struct PlanetSprite : public Collidable {
        private:
            const Planet* linkedPlanet;
            Color color;
        public:
            Planet getPlanet() { return *linkedPlanet; }
            void linkPlanet(const Planet* planet) { this->linkedPlanet = planet; }

            Color getColor() { return color; };
            void setColor(Color newColor) { color = newColor; };

            PlanetSprite(const Planet* linkedPlanetRef, Color color)
                :linkedPlanet(linkedPlanetRef), color(color) {}
    };
}

#endif