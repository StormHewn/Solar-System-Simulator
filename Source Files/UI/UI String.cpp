#include "UI/UI String.h"
#include <stdexcept>
#include <math.h>
#define padding 2
#define fontSize (hitBox.height - (padding * 2))
#define string std::string
#define StartRecordTime startedKeyHoldTimestamp = GetTime();
#define StopRecordTime startedKeyHoldTimestamp = -1;
#define KeyHoldTime (startedKeyHoldTimestamp == -1) ? -1 : GetTime() - startedKeyHoldTimestamp
#define StartKeyFireDelay startedKeyHoldTimestamp = GetTime() - (1 / 30);
using namespace Simulator;

int UIString::ProbeLocation(Vector2 position) {
    float startPos = hitBox.x + padding;
    float distanceToStart = position.x - startPos;
    string probeString = getter();
    for (int i = probeString.size(); i > 0; i--) {
        float dist1 = MeasureText(probeString.c_str(), fontSize);
        probeString.pop_back();
        float dist2 = MeasureText(probeString.c_str(), fontSize);
        float avgDist = (dist1 + dist2) / 2;
        
        if (avgDist <= distanceToStart) {
            return probeString.size() + 1;
        }
    }
    return 0;
}

void UIString::DeleteSelectionBubble() {
    int indexMin = std::min(pointerLocBefore, selectionAnchor);
    int indexDiff = std::abs(pointerLocBefore - selectionAnchor);
    setter(getter().erase(indexMin, indexDiff));
    pointerLocBefore = indexMin;
    selectionAnchor = -1;
}

void UIString::Draw(Vector2 anchor) {
    // Rectangle Setup
    hitBox.x = anchor.x;
    hitBox.y = anchor.y;
    hitBox.width = 500;
    hitBox.height = 50;

    // Draw Box
    Color boxColor = (GRAY);
    boxColor = ColorBrightness(boxColor, brightnessShift);
    DrawRectangleRec(hitBox, boxColor);

    // Draw Text
    DrawText(getter().c_str(), hitBox.x + padding, hitBox.y + padding, fontSize, WHITE);
    
    // Draw selection bubble (only if selectionAnchor isn't -1)
    if (selectionAnchor != -1) {
        string utilStringPointer = getter();
        string utilStringAnchor  = getter();
        utilStringPointer.resize(pointerLocBefore);
        utilStringAnchor .resize(selectionAnchor );
        float xPos1 = hitBox.x + padding + MeasureText(utilStringPointer.c_str(), fontSize);
        float xPos2 = hitBox.x + padding + MeasureText(utilStringAnchor .c_str(), fontSize);
        float xPosDiff = std::abs(xPos1 - xPos2);
        float xPosMin = std::min(xPos1, xPos2);
        Color color = ColorAlpha(BLUE, 0.5);
        DrawRectangle(xPosMin, (hitBox.y + padding), xPosDiff, fontSize, color);
    }

    // Draw Text Bar (only if (this is active and timing is right) or (shouldPointerRender is true))
    if (isActive && ((GetTime() - std::trunc(GetTime())) < 0.5) || (shouldPointerRender)) {
        string utilString = getter();
        utilString.resize(pointerLocBefore);
        float BarXPos = hitBox.x + padding + MeasureText(utilString.c_str(), fontSize);
        DrawLineEx(Vector2{BarXPos, hitBox.y + padding}, Vector2{BarXPos, hitBox.y + hitBox.height - padding}, 2, WHITE);
    }
}

void UIString::Update() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int currentPointerLocBefore = ProbeLocation(GetMousePosition());
        if (isMouseSelecting) {
            if ((pointerLocBefore != currentPointerLocBefore) && (selectionAnchor == -1)) {
                selectionAnchor = pointerLocBefore;
            }
        } else {
            selectionAnchor = -1;
        }
        pointerLocBefore = currentPointerLocBefore;
        isMouseSelecting = true;
    } else {
        isMouseSelecting = false;
    }

    char pressedChar = GetCharPressed();
    while (pressedChar != 0) {
        if ((pressedChar >= 32) && (pressedChar <= 126)) {
            if (selectionAnchor != -1) {
                DeleteSelectionBubble();
            }
            string oldString = getter();
            oldString.insert(oldString.begin() + pointerLocBefore, pressedChar);
            setter(oldString);
            pointerLocBefore++;
        }

        // Returns 0 if no more keys pressed, breaking the while loop
        pressedChar = GetCharPressed();
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
        if (pointerLocBefore != 0) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                if (selectionAnchor == -1) {
                    selectionAnchor = pointerLocBefore;
                }
            } else {
                selectionAnchor = -1;
            }
            pointerLocBefore--;
            shouldPointerRender = true;
        }
    } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
        if (pointerLocBefore != getter().size()) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                if (selectionAnchor == -1) {
                    selectionAnchor = pointerLocBefore;
                }
            } else {
                selectionAnchor = -1;
            }
            pointerLocBefore++;
            shouldPointerRender = true;
        }
    } else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
        if (selectionAnchor == -1) {
            if (pointerLocBefore != 0) {
                setter(getter().erase(pointerLocBefore - 1, 1));
                pointerLocBefore--;
                shouldPointerRender = true;
            }
        } else {
            DeleteSelectionBubble();
        }
    } else if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE)) {
        if (selectionAnchor == -1) {
            if (pointerLocBefore != getter().size()) {
                setter(getter().erase(pointerLocBefore, 1));
                shouldPointerRender = true;
            }
        } else {
            DeleteSelectionBubble();
        }
    } else {
        shouldPointerRender = false;
    }
}