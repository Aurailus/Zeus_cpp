//
// Created by aurailus on 27/12/18.
//

#ifndef ZEUS_DEBUGGUI_H
#define ZEUS_DEBUGGUI_H

#include "Histogram.h"
#include "HudText.h"
#include "../../graph/window/Window.h"
#include "../../../util/Ray.h"
#include "RectEntity.h"
#include "../../graph/drawable/DrawableGroup.h"
#include <sstream>

class DebugGui : public DrawableGroup {
public:
    explicit DebugGui(glm::vec2 bufferSize, Texture* tex);

    void bufferResized(glm::vec2 bufferSize);

    void update(Player* player, LocalWorld* world, BlockAtlas* atlas, double fps, int chunks, int drawCalls, int ssGen, int ssPack);
    void positionElements(glm::vec2 bufferSize);

    void changeVisibilityState(int state);
private:
    int displayMode;

    Texture *fontTexture;
    Texture *colorHistTexture, *whiteHistTexture, *transWhiteHistTexture;

    RectEntity *texAtlas;

    HudText    *dataText, *crosshairText;
    RectEntity *dataBG,   *crosshairBG;

    HudText    *chunkText, *meshText, *fpsText, *drawsText, *vramText, *ssGenText, *ssPackText;
    Histogram  *chunkHist, *meshHist, *fpsHist, *drawsHist, *tMeshHist, *vramHist, *ssGenHist, *ssPackHist;
    RectEntity *chunkBack, *meshBack, *fpsBack, *drawsBack, *vramBack, *ssGenBack, *ssPackBack;

    bool visible;
};


#endif //ZEUS_DEBUGGUI_H