//
// Created by aurailus on 11/01/19.
//

#include <iostream>

#include "ClientNetworkInterpreter.h"

#include "../PacketView.h"
#include "../Serializer.h"
#include "../NetHandler.h"
#include "../../util/Log.h"
#include "NetPlayerField.h"
#include "ServerConnection.h"
#include "../../game/entity/Model.h"
#include "../../game/scene/world/Player.h"
#include "../../game/scene/world/LocalWorld.h"

ClientNetworkInterpreter::ClientNetworkInterpreter(ServerConnection &connection, ClientGame &defs, Player& player) :
    player(player),
    connection(connection),
    playerModel(std::make_shared<Model>()) {
    playerModel->fromSerialized(defs.models.models["zeus:default:player"], { defs.textures["zeus:default:player"] });
}

void ClientNetworkInterpreter::init(LocalWorld *world, std::function<void(std::unique_ptr<PacketView>)> invCallback) {
    this->world = world;
    this->onInvPacket = invCallback;
}

void ClientNetworkInterpreter::update() {
    recvPackets = 0;

    ENetEvent event;
    while (connection.pollEvents(&event)) {
        recvPackets++;

        switch (event.type) {
            default: break;
            case ENET_EVENT_TYPE_CONNECT: {
                std::cout << Log::info << "Connected to server "
                          << NetHandler::intToIPString(event.peer->address.host)
                          << ":" << event.peer->address.port << "." << Log::endl;
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                std::unique_ptr<PacketView> p = std::make_unique<PacketView>(event.packet);
                receivedPacket(std::move(p));
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                std::cout << Log::info << "Disconnected from server "
                          << event.peer->address.host << ":" << event.peer->address.port << "." << Log::endl;
                break;
            }
        }
    }

    //Send Player Position
    Packet p(PacketType::PLAYER_INFO);
    p.data = Serializer()
            .append(player.getPos())
            .append(player.getPitch())
            .append(player.getYaw())
            .data;

    p.sendTo(connection.getPeer(), PacketChannel::PLAYER);
}

void ClientNetworkInterpreter::receivedPacket(std::unique_ptr<PacketView> p) {
    switch (p->type) {
        default:
            std::cout << Log::err << "Received unknown packet of type " << static_cast<int>(p->type)
                << ". Is the server on a different protocol version?" << Log::endl; break;

        case PacketType::SERVER_INFO:
            serverSideChunkGens = p->d.read<unsigned int>(); break;

        case PacketType::THIS_PLAYER_INFO:
            player.handleAssertion(p->d); break;
            
        case PacketType::PLAYER_INFO: {
            unsigned int cid = p->d.read<unsigned int>();
            if (player.id == cid) break;

            bool found = false;
            for (auto& entity : world->dimension.playerEntities) {
                if (entity.getCid() == cid) {
                    entity.interpPos(p->d.read<glm::vec3>());
                    entity.interpRotateZ(-p->d.read<float>() + 90);
                    entity.interpRotateY(-p->d.read<float>() + 90);

                    found = true;
                    break;
                }
            }
            if (found) break;

            // Instantiate a new PlayerEntity
            world->dimension.playerEntities.emplace_back(p->d.read<glm::vec3>(), cid, playerModel);
            break; }

        case PacketType::CHUNK:
        case PacketType::MAPBLOCK:
            world->loadWorldPacket(std::move(p)); break;
            
        case PacketType::BLOCK_SET: {
            auto pos = p->d.read<glm::ivec3>();
            auto block = p->d.read<unsigned int>();
            world->setBlock(pos, block);
            break; }

        case PacketType::ENTITY_INFO:
            world->dimension.serverEntityInfo(*p); break;

        case PacketType::ENTITY_REMOVED:
            world->dimension.serverEntityRemoved(p->d.read<unsigned int>()); break;

        case PacketType::INV_DATA:
            onInvPacket(std::move(p));
            break;
        
        case PacketType::INV_INVALID: {
            std::string source = p->d.read<std::string>();
            std::string list = p->d.read<std::string>();
            throw std::runtime_error("Invalid inventory " + source + ":" + list + " was request by client.");
            break; }
    }
}

void ClientNetworkInterpreter::blockPlace(glm::ivec3 pos, unsigned int block) {
    Serializer().append(pos).append(block).packet(PacketType::BLOCK_SET)
        .sendTo(connection.getPeer(), PacketChannel::BLOCK);
}

void ClientNetworkInterpreter::blockInteract(glm::ivec3 pos) {
    Serializer().append(pos).packet(PacketType::BLOCK_INTERACT)
        .sendTo(connection.getPeer(), PacketChannel::BLOCK);
}

void ClientNetworkInterpreter::invWatch(const std::string& inv, const std::string& list) {
    Serializer().append(inv).append(list).packet(PacketType::INV_WATCH)
        .sendTo(connection.getPeer(), PacketChannel::INVENTORY);
}

void ClientNetworkInterpreter::invUnwatch(const std::string& inv, const std::string& list) {
    Serializer().append(inv).append(list).packet(PacketType::INV_UNWATCH)
        .sendTo(connection.getPeer(), PacketChannel::INVENTORY);
}

void ClientNetworkInterpreter::invInteractPrimary(const std::string &inv, const std::string &list, unsigned short ind) {
    Serializer().append<unsigned short>(0).append(inv).append(list).append<unsigned short>(ind).packet(PacketType::INV_INTERACT)
        .sendTo(connection.getPeer(), PacketChannel::INVENTORY);
}

void ClientNetworkInterpreter::invInteractSecondary(const std::string &inv, const std::string &list, unsigned short ind) {
    Serializer().append<unsigned short>(1).append(inv).append(list).append<unsigned short>(ind).packet(PacketType::INV_INTERACT)
        .sendTo(connection.getPeer(), PacketChannel::INVENTORY);
}