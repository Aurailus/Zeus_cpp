//
// Created by aurailus on 17/12/18.
//

#ifndef SRC_GAMEWORLD_H
#define SRC_GAMEWORLD_H


#include "world/World.h"
#include "../engine/Camera.h"
#include "../engine/Window.h"
#include "../engine/PerlinNoise.h"
#include "../engine/graphics/Renderer.h"
#include "../engine/helpers/ArrayTrans3D.h"
#include "../lua_api/LuaParser.h"
#include "../engine/graphics/HudText.h"
#include "gui/DebugGui.h"
#include "world/Player.h"
#include "../engine/Ray.h"
#include "../client/Scene.h"
#include "../server/Server.h"
#include "../client/ServerConnection.h"

class GameScene : public Scene {
public:
    explicit GameScene(ClientState* state);

    void update() override;

    void draw() override;

    void cleanup() override;
public:
    ServerConnection* server;
    Player* player;
    World* world;
    TextureAtlas* textureAtlas;
    BlockAtlas* blockAtlas;

    //Entities to be drawn with world shaders
    std::vector<Entity*> entities;

    //GUI Related things
    std::vector<Entity*> guiEntities;
    DebugGui gui;
};


#endif //SRC_GAMEWORLD_H
