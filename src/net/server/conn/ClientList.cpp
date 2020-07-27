//
// Created by aurailus on 07/02/19.
//

#include <iostream>

#include "ClientList.h"

#include "../../Serializer.h"
#include "../../NetHandler.h"
#include "../../../util/Log.h"
#include "../../../def/ServerSubgame.h"
#include "../../client/NetPlayerField.h"
#include "../../../lua/ServerLuaParser.h"

ClientList::ClientList(ServerSubgame& defs) :
    defs(defs) {}

void ClientList::handleConnect(ENetEvent e, InventoryRefs& refs) {
    ENetPeer* peer = e.peer;
    ENetAddress& addr = peer->address;

    auto client = std::make_shared<ServerClient>(peer, addr, refs);
    clients.push_back(client);
    peer->data = client.get();

    std::cout << Log::info << NetHandler::intToIPString(addr.host) << ":" << addr.port << " connected." << Log::endl;
}

void ClientList::handleDisconnect(ENetEvent e) {
    unsigned int cid = static_cast<ServerClient*>(e.peer->data)->cid;

    for (unsigned int i = 0; i < clients.size(); i++) {
        if (clients[i]->cid == cid) {
            defs.lua->playerDisconnected(clients[i]);
            clients.erase(clients.begin() + i);
            break;
        }
    }

    ENetAddress& addr = e.peer->address;
    std::cout << Log::info << NetHandler::intToIPString(addr.host) << ":" << addr.port << " disconnected." << Log::endl;
}

void ClientList::createPlayer(std::shared_ptr<ServerClient> c) {
    c->hasPlayer = true;
    c->setUsername("TEMPORaRY");

    c->getInventory()->createList("cursor", 1, 1);

    defs.lua->playerConnected(c);

    Packet p(PacketType::THIS_PLAYER_INFO);
    p.data = Serializer()
            .append<unsigned int>(static_cast<unsigned int>(NetPlayerField::ID))
            .append<unsigned int>(c->cid)
            .append<unsigned int>(static_cast<unsigned int>(NetPlayerField::POSITION))
            .append<glm::vec3>(c->getPos())
            .data;

    p.sendTo(c->peer, PacketChannel::ENTITY);
}

const std::shared_ptr<ServerClient> ClientList::getClient(unsigned int cid) const {
    for (auto& c : clients) if (c->cid == cid) return c;
    return nullptr;
}
