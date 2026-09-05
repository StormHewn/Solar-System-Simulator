#include "Sim History.h"
#include <algorithm>
#include <ranges>
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

Vector2* SimHistory::GetPosDataRef(int tick, std::string name) {
    auto foundIterator = std::find(planetList.begin(), planetList.end(), name);
    int foundIndex = foundIterator - planetList.begin();
    int dataIndex = (tick * planetList.size()) + foundIndex;
    if (simData.size() <= dataIndex) {
        simData.resize(dataIndex+1);
    }

    return &simData[dataIndex];
}

Vector2 SimHistory::GetPlanetPos(int tick, std::string name) {
    return *GetPosDataRef(tick, name);
}

void SimHistory::SetPlanetPos(int tick, std::string name, Vector2 pos) {
    *GetPosDataRef(tick, name) = pos;
}

std::map<std::string, Vector2> SimHistory::GetTickState(int tick) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    std::map<std::string, Vector2> tickState;
    for (int i = 0; i < planetList.size(); i++) {
        tickState.insert({planetList.at(i), *tickData.at(i)});
    }
    return tickState;
}

void SimHistory::SetTickState(int tick, std::map<std::string, Vector2> tickState) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    for (int i = 0; i < planetList.size(); i++) {
        std::string planetname = planetList.at(i);
        *tickData.at(i) = tickState.at(planetname);
    }
}

void SimHistory::AddTickState(int tick, Engine engine) {
    std::vector<Vector2*> tickData = GetTickDataRef(tick);
    auto dataIt = tickData.begin();
    std::map<std::string, Planet> planets = engine.getPlanets();
    for (auto planetsIt = planets.begin(); planetsIt != planets.end(); ++planetsIt) {
        *(*dataIt) = planetsIt->second.getPos();
        ++dataIt;
    }
}