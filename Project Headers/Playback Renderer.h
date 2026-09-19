#include "Planet Sprite.h"
#include "Sim History.h"
#include <map>
#include <string>
#ifndef Solar_System_Simulator_PlaybackRenderer_H
#define Solar_System_Simulator_PlaybackRenderer_H

namespace Simulator {
    class PlaybackRenderer {
    private:
        std::map<std::string, PlanetSprite> planets;
    public:
        const std::map<std::string, PlanetSprite>* getPlanets() const { return &planets; }

        void Draw(const SimHistory* history, int tick, int trailLength) const;

        PlaybackRenderer(std::map<std::string, PlanetSprite> planets)
            :planets(planets) {}

        PlaybackRenderer() { PlaybackRenderer(std::map<std::string, PlanetSprite>()); }
    };
}

#endif