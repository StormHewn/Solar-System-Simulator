#include "raylib.h"
#include <string>

#ifndef Solar_System_Simulator_Collidable_H
#define Solar_System_Simulator_Collidable_H

namespace Simulator {
    class Collidable {
        protected:
            Rectangle hitBox;
        public:
            Rectangle getHitbox() const { return hitBox; }
            bool IsHit(Vector2 testPosition) const {
                return (
                    testPosition.x >= hitBox.x
                    && testPosition.y >= hitBox.y
                    && testPosition.x <= hitBox.x + hitBox.width
                    && testPosition.y <= hitBox.y + hitBox.height
                );
            }

            virtual void Hover() {}
            virtual void UnHover() {}
            virtual void StartClick() {}
            virtual void Activate() {}
            virtual void Update() {}
            virtual void Drag() {}
            virtual std::string Deactivate(bool canceled) {return "";}
            virtual bool IsActivated() {return true;}
    };
}

#endif