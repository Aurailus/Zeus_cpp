//
// World subclass for the server.
// Handles blocks, entities, and clients.
// Created by aurailus on 05/03/19.
//

#pragma once

#include "../../../game/scene/world/World.h"

#include "../../../world/ServerDimension.h"

class Target;
class ItemStack;
class ClientList;
class ServerClient;
class ServerSubgame;
class FileManipulator;
class ServerGenStream;
class ServerPacketStream;

class ServerWorld : public World {
public:
    explicit ServerWorld(unsigned int seed, ServerSubgame& game, ClientList& clients);

    void init(const std::string& worldDir);
    void update(double delta) override;

    unsigned int getBlock(glm::ivec3 pos) override;
    void setBlock(glm::ivec3 pos, unsigned int block) override;

    void blockPlace(const Target& target, ServerClient& client);
    void blockPlaceOrInteract(const Target& target, ServerClient& client);
    void blockInteract(const Target& target, ServerClient& client);

    ServerDimension dimension;
private:
    void changedMapBlocks(ServerClient& client);
    static bool isInBounds(glm::ivec3 pos, std::pair<glm::ivec3, glm::ivec3>& bounds);

    void generateMapBlocks(ServerClient& client);
    bool generateMapBlock(glm::ivec3 pos);
    void sendChunksToPlayer(ServerClient& client);

    std::shared_ptr<ServerGenStream> genStream = nullptr;
    std::shared_ptr<ServerPacketStream> packetStream = nullptr;

    unsigned int seed;
    ServerSubgame& game;
    ClientList& clientList;
    
    std::string worldDir;
    std::shared_ptr<FileManipulator> fileManip;

    unsigned int generatedMapBlocks = 0;
    std::vector<glm::ivec3> generateOrder;

    const glm::ivec2 mapBlockGenRange = {4, 4};
    const glm::ivec2 sendRange        = {4, 4};
    const glm::ivec2 activeChunkRange = {16, 16};
};

