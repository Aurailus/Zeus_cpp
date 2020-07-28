//
// Created by aurailus on 11/06/19.
//

#pragma once

#include <enet/enet.h>

#include "LuaParser.h"

#include "ServerModHandler.h"

class ServerSubgame;
class ServerWorld;
class ServerClient;

class ServerLuaParser : public LuaParser {
public:
    explicit ServerLuaParser(ServerSubgame& game);
    void init(ServerWorld& world, const std::string& rootPath);

    void update(double delta) override;

    void sendModsPacket(ENetPeer* peer) const;

    void playerConnected(std::shared_ptr<ServerClient> client);
    void playerDisconnected(std::shared_ptr<ServerClient> client);

    template<typename... Args> sol::safe_function_result safe_function(sol::protected_function f, Args... args) const {
        auto res = f(args...);
        if (!res.valid()) errorCallback(res);
        return res;
    }
private:
    void loadApi(ServerSubgame& defs, ServerWorld& world);
    void registerDefs(ServerSubgame &defs);

    sol::protected_function_result errorCallback(sol::protected_function_result errPfr) const;
    sol::protected_function_result runFileSandboxed(const std::string& file);

    ServerSubgame& game;

    ServerModHandler handler;
    double delta = 0;
};
