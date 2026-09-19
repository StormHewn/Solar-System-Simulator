#include "Engine.h"
#include "Planet.h"
#include "Sim History.h"
#include "Playback Renderer.h"
#include "UI/UI Bool.h"
#include "raylib.h"
#include "raymath.h"
using namespace Simulator;

#ifndef Solar_System_Simulator_Game_H
#define Solar_System_Simulator_Game_H

namespace Simulator {
    class Game {
        enum GameWaitingState {
            Waiting = 0,
            Hovering,
            Clicking,
            Dragging,
            Updating
        };
        public:
            static void GameLoop();
    };
}

#endif