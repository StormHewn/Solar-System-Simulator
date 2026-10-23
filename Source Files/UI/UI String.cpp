#include "UI/UI String.h"
#include <stdexcept>
#include <math.h>
#define padding 2
#define fontSize (hitBox.height - (padding * 2))
#define textWindowWidth int(hitBox.width - 2 * padding)
#define string std::string
#define comingOutOfSelect ((selectionAnchor != -1) && !(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)))
using namespace Simulator;

int UIString::ProbeLocation(Vector2 position) {
    float startPos = hitBox.x + padding - displayOffset;
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

void UIString::DeleteSelection() {
    int indexMin = std::min(pointerLocBefore, selectionAnchor);
    int indexDiff = std::abs(pointerLocBefore - selectionAnchor);
    setter(getter().erase(indexMin, indexDiff));
    UpdatePointerLocAndDisplayOffset(indexMin);
    selectionAnchor = -1;
}

void UIString::CopySelection() {
    if (selectionAnchor != -1) {
        int indexMin = std::min(pointerLocBefore, selectionAnchor);
        int indexDiff = std::abs(pointerLocBefore - selectionAnchor);
        SetClipboardText(getter().substr(indexMin, indexDiff).c_str());
    }
}

void UIString::CutSelection() {
    CopySelection();
    DeleteSelection();
}

void UIString::Paste() {
    if (selectionAnchor != -1) {
        DeleteSelection();
    }
    string modifiedString = getter();
    string pastedText = GetClipboardText();
    modifiedString.insert(pointerLocBefore, pastedText);
    setter(modifiedString);
    UpdatePointerLocAndDisplayOffset(pointerLocBefore + pastedText.size());
}

void UIString::MoveOrSelect(int newPointerLoc) {
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
        if (selectionAnchor == -1) {
            selectionAnchor = pointerLocBefore;
        }
    } else {
        selectionAnchor = -1;
    }
    UpdatePointerLocAndDisplayOffset(newPointerLoc);
}

void UIString::UpdatePointerLocAndDisplayOffset(int newPointerLoc) {
    // Set pointer loc (clamped)
    pointerLocBefore = std::clamp(newPointerLoc, 0, int(getter().size()));

    // Compute text display offset
    int stringEndOffset = MeasureText(getter().c_str(), fontSize);
    int pointerLocOffset = MeasureText(getter().erase(pointerLocBefore).c_str(), fontSize);

    // if pointer offset is less than the current offset, set the current offset to the pointer offset
    if (pointerLocOffset < displayOffset) displayOffset = pointerLocOffset;
    // if pointer offset is past the current offset's right bound, set the current offset to the pointer offset minus the text window width
    else if (pointerLocOffset > displayOffset + textWindowWidth) displayOffset = pointerLocOffset - textWindowWidth;
    // if text length is less than the current offset plus the window size, set the current offset to the text length minus the text window width
    else if (stringEndOffset < displayOffset + textWindowWidth) displayOffset = std::max(stringEndOffset - textWindowWidth, 0);
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
    BeginScissorMode(hitBox.x + padding, hitBox.y + padding, textWindowWidth, hitBox.height - padding*2);
        DrawText(getter().c_str(), hitBox.x + padding - displayOffset, hitBox.y + padding, fontSize, WHITE);
    EndScissorMode();
    
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
        DrawRectangle(xPosMin - displayOffset, (hitBox.y + padding), xPosDiff, fontSize, color);
    }

    // Draw Text Bar (only if (this is active and timing is right) or (shouldPointerRender is true))
    if (isActive && ((GetTime() - std::trunc(GetTime())) < 0.5) || (forcePointerRender)) {
        string utilString = getter();
        utilString.resize(pointerLocBefore);
        float BarXPos = hitBox.x + padding + MeasureText(utilString.c_str(), fontSize);
        DrawLineEx(Vector2{BarXPos - displayOffset, hitBox.y + padding}, Vector2{BarXPos - displayOffset, hitBox.y + hitBox.height - padding}, 2, WHITE);
    }
}

void UIString::Update() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int mousePos = ProbeLocation(GetMousePosition());
        if (!isMouseSelecting) { // Initial click
            MoveOrSelect(mousePos);
            isMouseSelecting = true;
        } else { // Hold
            if ((pointerLocBefore != mousePos) && (selectionAnchor == -1)) { // If I'm dragging and I don't already have a bubble
                selectionAnchor = pointerLocBefore;
            }
            UpdatePointerLocAndDisplayOffset(mousePos);
        }
    } else {
        isMouseSelecting = false;
    }

    char pressedChar = GetCharPressed();
    while (pressedChar != 0) {
        if ((pressedChar >= 32) && (pressedChar <= 126)) {
            if (selectionAnchor != -1) {
                DeleteSelection();
            }
            string modifiedString = getter();
            modifiedString.insert(modifiedString.begin() + pointerLocBefore, pressedChar);
            setter(modifiedString);
            UpdatePointerLocAndDisplayOffset(pointerLocBefore + 1);
        }

        // Returns 0 if no more keys pressed, breaking the while loop
        pressedChar = GetCharPressed();
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
        if comingOutOfSelect {
            int newPointerLoc = std::min(selectionAnchor, pointerLocBefore) - 1;
            UpdatePointerLocAndDisplayOffset(newPointerLoc);
            selectionAnchor = -1;
        } else {
            MoveOrSelect(pointerLocBefore - 1);
        }
        forcePointerRender = true;
    } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
        if comingOutOfSelect {
            int newPointerLoc = std::max(selectionAnchor, pointerLocBefore) + 1;
            UpdatePointerLocAndDisplayOffset(newPointerLoc);
            selectionAnchor = -1;
        } else {
            MoveOrSelect(pointerLocBefore + 1);
        }
        forcePointerRender = true;
    } else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
        if (selectionAnchor == -1) {
            if (pointerLocBefore != 0) {
                setter(getter().erase(pointerLocBefore - 1, 1));
                UpdatePointerLocAndDisplayOffset(pointerLocBefore - 1);
                forcePointerRender = true;
            }
        } else {
            DeleteSelection();
        }
    } else if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE)) {
        if (selectionAnchor == -1) {
            if (pointerLocBefore != getter().size()) {
                setter(getter().erase(pointerLocBefore, 1));
                forcePointerRender = true;
            }
        } else {
            DeleteSelection();
        }
    } else if (IsKeyPressed(KEY_HOME)) {
        MoveOrSelect(0);
        forcePointerRender = true;
    } else if (IsKeyPressed(KEY_END)) {
        MoveOrSelect(getter().size());
        forcePointerRender = true;
    } else if (IsKeyPressed(KEY_A) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            selectionAnchor = 0;
            UpdatePointerLocAndDisplayOffset(getter().size());
    } else if (IsKeyPressed(KEY_C) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            CopySelection();
    } else if (IsKeyPressed(KEY_X) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            CutSelection();
    } else if (IsKeyPressed(KEY_V) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            Paste();
    } else {
        forcePointerRender = false;
    }
}