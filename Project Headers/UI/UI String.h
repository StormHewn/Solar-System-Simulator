#include "Collidable.h"
#include "raylib.h"
#include <functional>
#ifndef Solar_System_Simulator_UIString_H
#define Solar_System_Simulator_UIString_H

namespace Simulator {
    class UIString : public Collidable {
        private:
            std::function<std::string()> getter;
            std::function<void(std::string)> setter;
            int pointerLocBefore = 0;
            bool shouldPointerRender = false;
            int selectionAnchor = -1;
            bool isMouseSelecting = false;
            float brightnessShift = 0;
            bool isActive = false;
            std::string oldString = "";

            int ProbeLocation(Vector2 position);
            void DeleteSelectionBubble();
        public:
            std::function<std::string()> getGetter() { return getter; }
            std::function<void(std::string)> getSetter() { return setter; }


            UIString(std::function<std::string()> getter, std::function<void(std::string value)> setter):
                getter(getter), setter(setter) {}

            void Draw(Vector2 anchor);

            void Hover() { brightnessShift = 0.5; }
            void UnHover() { brightnessShift = 0; }
            void StartClick() { brightnessShift = -0.2; }
            void Activate() {
                isActive = true;
                pointerLocBefore = ProbeLocation(GetMousePosition());
                oldString = getter();
            }
            void Update();
            void Drag() {}
            std::string Deactivate(bool canceled){
                isActive = false;
                brightnessShift = 0;
                selectionAnchor = -1;
                isMouseSelecting = false;
                if (canceled) { setter(oldString); }
                oldString = "";
                return "";
            }
            bool IsActivated() {return isActive;}
    };
}

#endif