//
// Created by aurailus on 17/12/18.
//

#ifndef SRC_GAMEWORLD_H
#define SRC_GAMEWORLD_H


#include "World.h"
#include "../engine/Camera.h"
#include "../engine/Window.h"
#include "../engine/PerlinNoise.h"
#include "../engine/graphics/Renderer.h"
#include "../engine/helpers/ArrayTrans3D.h"
#include "../lua_api/LuaParser.h"
#include "../engine/graphics/HudText.h"

class GameInstance {
public:
    GameInstance();

    void initialize(Renderer* renderer);

    void update(GLfloat deltaTime);

    void draw();

    std::vector<Entity*>* getGuiEntities();

    HudText* fpsText;
public:
    //The renderer contains the camera, window, and draw methods.
    Renderer* renderer;

    //The World object represents the physical game region that is played in. It handles chunk updates and entities.
    World* world;

    //The texture atlas makes a single patched texture from an asset folder.
    TextureAtlas* textureAtlas;

    //The block atlas holds block definitions and models.
    BlockAtlas* blockAtlas;

    //GUI Entities (Things to draw on the screen
    std::vector<Entity*> guiEntities;
    Texture fontTexture;

    HudText* alphaText;
    HudText* blockText;
};


#endif //SRC_GAMEWORLD_H
