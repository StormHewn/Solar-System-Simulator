#include "raylib.h"
#include <string>
#include <map>

#ifndef Solar_System_Simulator_PLANET_H
#define Solar_System_Simulator_PLANET_H

namespace Simulator {
    class Planet {
        private:
            Color color;
            float mass;
            Vector2 pos;
            Vector2 vel;
        public:
            Color getColor() { return color; };
            void setColor(Color newColor) { color = newColor; };

            float getMass() { return mass; };
            void setMass(float newMass) { mass = newMass; };

            Vector2 getPos() { return pos; };
            void setPos(Vector2 newPos) { pos = newPos; };

            Vector2 getVel() { return vel; };
            void setVel(Vector2 newVel) { vel = newVel; };

            float getSize(float density);

            Planet(Color color, float mass, Vector2 pos, Vector2 vel)
                :color(color), mass(mass), pos(pos), vel(vel) {}
        
            Planet(Color color, float mass, Vector2 pos, const std::map<std::string, Planet> planets);
    };
}

#endif