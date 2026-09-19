#include "UI/UI Bool.h"
using namespace Simulator;

void UIBool::Draw(Vector2 anchor) {
    hitBox.x = anchor.x;
    hitBox.y = anchor.y;
    hitBox.width = 50;
    hitBox.height = 20;
    Color boxColor = (getter() ? BLUE : GRAY);
    boxColor = ColorBrightness(boxColor, brightnessShift);
    DrawRectangleRec(hitBox, boxColor);
}