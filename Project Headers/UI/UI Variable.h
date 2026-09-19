#include "Collidable.h"
#include "raylib.h"
#ifndef Solar_System_Simulator_UIVariable_H
#define Solar_System_Simulator_UIVariable_H

namespace Simulator {
    class UIVariable : public Collidable {
        public:
            virtual void Draw(Vector2 anchor) {}

            virtual void Hover() {}
            virtual void UnHover() {}
            virtual void StartClick() {}
            virtual void Activate() {}
            virtual void Update() {}
            virtual void Drag() {}
            virtual std::string Deactivate(bool canceled) { return ""; }
            virtual bool IsActivated() { return true; }
    };
}

#endif