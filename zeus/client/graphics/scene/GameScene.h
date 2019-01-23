//
// Created by aurailus on 17/12/18.
//

#ifndef SRC_GAMEWORLD_H
#define SRC_GAMEWORLD_H


#include "../../engine/scene/Scene.h"
#include "../../engine/graphics/Renderer.h"
#include "../gui/DebugGui.h"

#include "../../lua/LuaParser.h"

#include "../../gameworld/World.h"
#include "../../gameworld/Player.h"

#include "../../network/ServerConnection.h"

#include "../../../generic/blocks/TextureAtlas.h"
#include "../../../generic/blocks/BlockAtlas.h"

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

    //Entities to be drawn with gameworld shaders
    std::vector<Entity*> entities;

    //GUI Related things
    std::vector<Entity*> guiEntities;
    DebugGui gui;
};


#endif //SRC_GAMEWORLD_H