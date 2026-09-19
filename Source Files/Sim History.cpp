#include "Sim History.h"
#include <algorithm>
#include <ranges>
#define string std::string
using namespace Simulator;

std::vector<Vector2*> SimHistory::GetTickDataRef(int tick) {
    std::vector<int> range = GetTickDataIndecies(tick);
    std::vector<Vector2*> data;
    for (auto it = range.begin(); it != range.end(); ++it) {
        data.push_back(&simData[*it]);
    }
    return data;
}

std::vector<int> SimHistory::GetTickDataIndecies(int tick) const {
    int dataStartIndex = tick * planetList.size();
    int dataEndIndex = dataStartIndex + planetList.size();
    std::vector<int> range;
    for (int i = dataStartIndex; i <= dataEndIndex; i++) {
        range.push_back(i);
    }

    return range;
}

Vector2* SimHistory::GetPosDataRef(int tick, string name) {
    int dataIndex = GetPosDataIndex(tick, name);
    if (simData.size() <= dataIndex) {
        simData.resize(dataIndex + 1);
    }

    return &simData[dataIndex];
}

int SimHistory::GetPosDataIndex(int tick, string name) const {
    auto foundIterator = planetList.find(name);
    int foundIndex = std::distance(planetList.begin(), foundIterator);
    int dataIndex = (tick * planetList.size()) + foundIndex;

    return dataIndex;
}

Vector2 SimHistory::GetPlanetPos(int tick, string name) const {
    return simData.at(GetPosDataIndex(tick, name));
}

void SimHistory::SetPlanetPos(int tick, string name, Vector2 pos) {
    *GetPosDataRef(tick, name) = pos;
}

std::map<string, Vector2> SimHistory::GetTickState(int tick) const {
    std::vector<int> tickIndecies = GetTickDataIndecies(tick);
    std::map<string, Vector2> tickState;
    for (auto it = planetList.begin(); it != planetList.end(); ++it) {
        int index = std::distance(planetList.begin(), it);
        tickState.insert({*it, simData.at(tickIndecies.at(index))});
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