#include "Sim History.h"
#include <algorithm>
#include <ranges>
#define string std::string
using namespace Simulator;

std::vector<Vector2*> SimHistory::GetTickDataRef(int tick) {
    int dataStartIndex = tick * planetList.size();
    int dataEndIndex = dataStartIndex + planetList.size();
    if (simData.size() < dataEndIndex) {
        simData.resize(dataEndIndex);
    }

    std::vector<Vector2*> data;
    for (int i = dataStartIndex; i < dataEndIndex; i++) {
        data.push_back(&simData[i]);
    }
    return data;
}

Vector2* SimHistory::GetPosDataRef(int tick, string name) {
    auto foundIterator = planetList.find(name);
    int foundIndex = std::distance(planetList.begin(), foundIterator);
    int dataIndex = (tick * planetList.size()) + foundIndex;
    if (simData.size() <= dataIndex) {
        simData.resize(dataIndex + 1);
    }

    return &simData[dataIndex];
}

Vector2 SimHistory::GetPlanetPos(int tick, string name) {
    return *GetPosDataRef(tick, name);
}

void SimHistory::SetPlanetPos(int tick, string name, Vector2 pos) {
    *GetPosDataRef(tick, name) = pos;
}

std::map<string, Vector2> SimHistory::GetTickState(int tick) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    std::map<string, Vector2> tickState;
    for (auto it = planetList.begin(); it != planetList.end(); ++it) {
        int index = std::distance(planetList.begin(), it);
        tickState.insert({*it, *tickData.at(index)});
    }
    return tickState;
}

void SimHistory::SetTickState(int tick, std::map<string, Vector2> tickState) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    for (auto it = planetList.begin(); it != planetList.end(); ++it) {
        int index = std::distance(planetList.begin(), it);
        string planetname = *it;
        *tickData.at(index) = tickState.at(planetname);
    }
}

void SimHistory::AddTickState(int tick, Engine engine) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    auto dataIt = tickData.begin();
    std::map<string, Planet> planets = engine.getPlanets();
    for (auto planetsIt = planets.begin(); planetsIt != planets.end(); ++planetsIt) {
        *(*dataIt) = planetsIt->second.getPos();
        ++dataIt;
    }
}