#include "Engine.h"
#include "raylib.h"
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace Simulator;
#ifndef Solar_System_Simulator_SimHistory_H
#define Solar_System_Simulator_SimHistory_H

namespace Simulator {
    class SimHistory {
        private:
            std::vector<Vector2> simData;
            std::set<std::string> planetList;

            std::vector<Vector2*> GetTickDataRef(int tick);
            Vector2* GetPosDataRef(int tick, std::string name);
        public:
            Vector2 GetPlanetPos(int tick, std::string name);
            void SetPlanetPos(int tick, std::string name, Vector2 pos);

            std::map<std::string, Vector2> GetTickState(int tick);
            void SetTickState(int tick, std::map<std::string, Vector2>);

            const std::set<std::string>* GetPlanetlist() { return &planetList; }

            SimHistory(std::set<std::string> planetList) { this->planetList = planetList; }

            void AddTickState(int tick, Engine engine);
    };
}


#endif