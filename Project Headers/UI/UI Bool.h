#include "UI/UI Variable.h"
#include "raylib.h"
#include <functional>
#ifndef Solar_System_Simulator_UIBool_H
#define Solar_System_Simulator_UIBool_H

namespace Simulator {
    class UIBool : public UIVariable {
        private:
            std::function<bool()> getter;
            std::function<void(bool)> setter;
            float brightnessShift = 0;
        public:
            std::function<bool()> getGetter() { return getter; }
            std::function<void(bool)> getSetter() { return setter; }

            UIBool(std::function<bool()> getter, std::function<void(bool value)> setter):
                getter(getter), setter(setter) {}

            void Draw(Vector2 anchor);

            bool GetValue() { return getter(); }
            void SetValue(bool value) { setter(value); }
            void ToggleValue() { setter(!getter()); }

            void Hover() { brightnessShift = 0.5; }
            void UnHover() { brightnessShift = 0; }
            void StartClick() { brightnessShift = -0.2; }
            void Activate() { ToggleValue();  brightnessShift = 0; }
            void Update() {}
            void Drag() {}
            std::string Deactivate(bool canceled) { return ""; }
            bool IsActivated() { return false; }
    };
}

#endif