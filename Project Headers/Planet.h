#include "raylib.h"
#include <string>
#include <math.h>
#include <map>
#ifndef Solar_System_Simulator_PLANET_H
#define Solar_System_Simulator_PLANET_H

namespace Simulator {
    class Planet {
        private:
            float mass;
            float density;
            Vector2 pos;
            Vector2 vel;
        public:
            float getMass() { return mass; };
            void setMass(float newMass) { mass = newMass; };

            float getDensity() { return density; }
            void setDensity(float density) { this->density = density; }

            float getSize() { return std::cbrt((4 * (mass / density)) / (3 * PI)); }

            Vector2 getPos() { return pos; };
            void setPos(Vector2 newPos) { pos = newPos; };

            Vector2 getVel() { return vel; };
            void setVel(Vector2 newVel) { vel = newVel; };

            Planet(float mass, Vector2 pos, Vector2 vel, float density = 1)
                :mass(mass), density(density), pos(pos), vel(vel) {}
        
            Planet(float mass, Vector2 pos, const std::map<std::string, Planet> planets, float density = 1);

        // Sorts planets deterministically, but rather arbitrarily, place-value style
        // Neccessary to put planets into sets
        // Is there a better way to do operators than this?
        private:
            static char Compare(Planet p1, Planet p2) {
                     if (p1.mass < p2.mass) { return -1; }
                else if (p1.mass > p2.mass) { return 1; }
                else if (p1.density < p2.density) { return -1; }
                else if (p1.density > p2.density) { return 1; }
                else if (p1.pos.x < p2.pos.x) { return -1; }
                else if (p1.pos.x > p2.pos.x) { return 1; }
                else if (p1.pos.y < p2.pos.y) { return -1; }
                else if (p1.pos.y > p2.pos.y) { return 1; }
                else if (p1.vel.x < p2.vel.x) { return -1; }
                else if (p1.vel.x > p2.vel.x) { return 1; }
                else if (p1.vel.y < p2.vel.y) { return -1; }
                else if (p1.vel.y > p2.vel.y) { return 1; }
                else { return 0; }
            }
        public:
            bool operator== (const Planet p) const { return (Compare(*this, p) == 0); }
            bool operator!= (const Planet p) const { return (Compare(*this, p) != 0); }
            bool operator<= (const Planet p) const { return (Compare(*this, p) == -1); }
            bool operator<  (const Planet p) const { return (Compare(*this, p) != -1); }
            bool operator>= (const Planet p) const { return (Compare(*this, p) == 1); }
            bool operator>  (const Planet p) const { return (Compare(*this, p) != 1); }
    };
}

#endif