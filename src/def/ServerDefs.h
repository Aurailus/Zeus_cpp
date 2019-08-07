//
// Created by aurailus on 10/06/19.
//

#ifndef ZEUS_SERVERDEFS_H
#define ZEUS_SERVERDEFS_H


#include "block/server/ServerBlockAtlas.h"
#include "../api/server/ServerLuaParser.h"
#include "texture/ServerTextureStorage.h"

class ServerWorld;

class ServerDefs {
public:
    void init(ServerWorld& world, const std::string& path);

    ServerBlockAtlas& blocks();
    ServerLuaParser& lua();
    ServerTextureStorage& textures();

    void update(double delta);

    ~ServerDefs() = default;
private:
    double delta = 0;

    ServerTextureStorage textureStorage;
    ServerBlockAtlas blockAtlas;
    ServerLuaParser luaApi;
};


#endif //ZEUS_SERVERDEFS_H
