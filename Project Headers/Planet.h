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

            // Sorts planets deterministically, but rather arbitrarily, place-value style
            // Neccessary to put planets into sets
            // Is there a better way to do operators than this?
            bool operator!= (const Planet p) const {
                     if (this->mass == p.mass) { return false; }
                else if (this->color.r == p.color.r) { return false; }
                else if (this->color.r == p.color.g) { return false; }
                else if (this->color.r == p.color.b) { return false; }
                else if (this->color.r == p.color.a) { return false; }
                else if (this->color.r == p.pos.x) { return false; }
                else if (this->color.r == p.pos.y) { return false; }
                else if (this->color.r == p.vel.x) { return false; }
                else if (this->color.r == p.vel.y) { return false; }
                else { return true; }
            }

            bool operator<= (const Planet p) const {
                     if (this->mass > p.mass) { return false; }
                else if (this->color.r > p.color.r) { return false; }
                else if (this->color.r > p.color.g) { return false; }
                else if (this->color.r > p.color.b) { return false; }
                else if (this->color.r > p.color.a) { return false; }
                else if (this->color.r > p.pos.x) { return false; }
                else if (this->color.r > p.pos.y) { return false; }
                else if (this->color.r > p.vel.x) { return false; }
                else if (this->color.r > p.vel.y) { return false; }
                else { return true; }
            }

            bool operator>= (const Planet p) const {
                     if (this->mass < p.mass) { return false; }
                else if (this->color.r < p.color.r) { return false; }
                else if (this->color.r < p.color.g) { return false; }
                else if (this->color.r < p.color.b) { return false; }
                else if (this->color.r < p.color.a) { return false; }
                else if (this->color.r < p.pos.x) { return false; }
                else if (this->color.r < p.pos.y) { return false; }
                else if (this->color.r < p.vel.x) { return false; }
                else if (this->color.r < p.vel.y) { return false; }
                else { return true; }
            }

            bool operator== (const Planet p) const {
                return !(*this != p);
            }

            bool operator< (const Planet p) const {
                return !(*this >= p);
            }

            bool operator> (const Planet p) const {
                return !(*this <= p);
            }
    };
}

#endif