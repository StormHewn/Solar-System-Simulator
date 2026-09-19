#include "Playback Renderer.h"
#include "Planet Sprite.h"
#include "raylib.h"
#include <math.h>
#include <vector>
using namespace Simulator;

void PlaybackRenderer::Draw(const SimHistory* history, int tick, int trailLength) const {
    if (IsWindowReady()) {
        for (auto it = planets.begin(); it != planets.end(); ++it) {
            // Setup
            PlanetSprite planetSprite = it->second;
            Planet planet = planetSprite.getPlanet();

            // Pull planet history from SimHistory
            std::vector<Vector2> trailData;
            for (int i = std::max(tick - trailLength, 0); i < tick; i++) {
                trailData.push_back(history->GetPlanetPos(i, it->first));
            }

            // Draw Planet
            Vector2 planetPosAtTick = history->GetPlanetPos(tick, it->first);
            DrawCircleV(planetPosAtTick, planet.getSize(), planetSprite.getColor());

            // Draw Trail
            if (trailData.size() != 0) {
                for (auto it = trailData.begin(); it != (trailData.end() - 1); ++it) {
                    Vector2 firstPos  = *it;
                    Vector2 secondPos = *(it + 1);
                    DrawLine(firstPos.x, firstPos.y, secondPos.x, secondPos.y, planetSprite.getColor());
                }
            }
        }
    }
}