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
            bool forcePointerRender = false;
            int selectionAnchor = -1;
            int displayOffset = 0;
            bool isMouseSelecting = false;
            float brightnessShift = 0;
            bool isActive = false;
            std::string oldString = "";

            int ProbeLocation(Vector2 position);
            void DeleteSelection();
            void CopySelection();
            void CutSelection();
            void Paste();
            void MoveOrSelect(int newPointerLoc);
            void UpdatePointerLocAndDisplayOffset(int newPointerLoc);
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
                UpdatePointerLocAndDisplayOffset(ProbeLocation(GetMousePosition()));
                oldString = getter();
            }
            void Update();
            void Drag() {}
            std::string Deactivate(bool canceled){
                UpdatePointerLocAndDisplayOffset(0);
                forcePointerRender = false;
                selectionAnchor = -1;
                displayOffset = 0;
                isMouseSelecting = false;
                brightnessShift = 0;
                isActive = false;
                if (canceled) { setter(oldString); }
                oldString = "";
                return "";
            }
            bool IsActivated() {return isActive;}
    };
}

#endif