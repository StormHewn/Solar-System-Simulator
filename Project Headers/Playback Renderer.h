#include "Planet Sprite.h"
#include "Sim History.h"
#include <string>
#include <map>
#ifndef Solar_System_Simulator_PlaybackRenderer_H
#define Solar_System_Simulator_PlaybackRenderer_H

namespace Simulator {
    class PlaybackRenderer {
    private:
        SimHistory* history;
        std::map<std::string, PlanetSprite> planets;
    public:
        const SimHistory* getSimHistoryRef() { return history; }

        const std::map<std::string, PlanetSprite>* getPlanets() { return &planets; }

        void Draw(int tick, int trailLength);

        PlaybackRenderer(SimHistory* history, std::map<std::string, PlanetSprite> planets)
            :history(history), planets(planets) {}
    };
}

#endif