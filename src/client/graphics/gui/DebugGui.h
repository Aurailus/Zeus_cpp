//
// Created by aurailus on 27/12/18.
//

#ifndef ZEUS_DEBUGGUI_H
#define ZEUS_DEBUGGUI_H

#include "../../engine/graphics/Histogram.h"
#include "../../engine/graphics/HudText.h"
#include "../../engine/Window.h"
#include "../../engine/Ray.h"
#include "../../engine/graphics/RectEntity.h"

#include <sstream>

class DebugGui {
public:
    DebugGui();

    void pushGuiObjects(std::vector<Entity*> &list);
    void update(Player* player, World* world, Window* window, BlockAtlas* atlas, double fps);
    void positionElements(int bufferWidth, int bufferHeight);

    ~DebugGui();

private:
    Texture *fontTexture;
    Texture *colorHistTexture, *whiteHistTexture;

    HudText    *dataText, *crosshairText;
    RectEntity *dataBG,   *crosshairBG;

    HudText    *chunkUpdateText,      *meshUpdateText,      *fpsText;
    Histogram  *chunkUpdateHistogram, *meshUpdateHistogram, *fpsHistogram;
    RectEntity *chunkUpdateBG,        *meshUpdateBG,        *fpsBG;
};


#endif //ZEUS_DEBUGGUI_H
