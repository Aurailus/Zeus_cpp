//
// Created by aurailus on 2019-11-20.
//

#include "Dimension.h"

std::shared_ptr<Region> Dimension::getRegion(glm::ivec3 regionPosition) {
    if (!regions.count(regionPosition)) return nullptr;
    return regions[regionPosition];
}

void Dimension::removeRegion(glm::ivec3 pos) {
    regions.erase(pos);
}

std::shared_ptr<MapBlock> Dimension::getMapBlock(glm::ivec3 mapBlockPosition) {
    auto region = getRegion(Space::Region::world::fromMapBlock(mapBlockPosition));
    if (region == nullptr) return nullptr;
    return (*region)[Space::MapBlock::index(mapBlockPosition)];
}

void Dimension::removeMapBlock(glm::ivec3 pos) {
    auto region = getRegion(Space::Region::world::fromMapBlock(pos));
    if (region == nullptr) return;
    auto ind = Space::MapBlock::index(pos);
    region->remove(ind);
    if (region->count == 0) removeRegion(Space::Region::world::fromMapBlock(pos));
}

std::shared_ptr<BlockChunk> Dimension::getChunk(glm::ivec3 chunkPosition) {
    auto mapBlock = getMapBlock(Space::MapBlock::world::fromChunk(chunkPosition));
    if (mapBlock == nullptr) return nullptr;
    return (*mapBlock)[Space::Chunk::index(chunkPosition)];
}

void Dimension::setChunk(std::shared_ptr<BlockChunk> chunk) {
    auto mapBlock = getOrCreateMapBlock(Space::MapBlock::world::fromChunk(chunk->pos));
    (*mapBlock).set(Space::Chunk::index(chunk->pos), chunk);
}

void Dimension::removeChunk(glm::ivec3 pos){
    auto mapBlock = getMapBlock(Space::MapBlock::world::fromChunk(pos));
    if (mapBlock == nullptr) return;
    auto ind = Space::Chunk::index(pos);
    mapBlock->remove(ind);
    if (mapBlock->count == 0) removeMapBlock(Space::MapBlock::world::fromChunk(pos));
}

unsigned int Dimension::getBlock(glm::ivec3 pos) {
    auto chunk = getChunk(Space::Chunk::world::fromBlock(pos));
    if (chunk != nullptr) return chunk->getBlock(Space::Block::relative::toChunk(pos));
    return 0;
}

bool Dimension::setBlock(glm::ivec3 pos, unsigned int block) {
    auto chunk = getChunk(Space::Chunk::world::fromBlock(pos));
    if (chunk == nullptr) return false;

    chunk->setBlock(Space::Block::relative::toChunk(pos), block);
    return true;
}

std::shared_ptr<Region> Dimension::getOrCreateRegion(glm::ivec3 pos) {
    if (regions[pos] != nullptr) return regions[pos];
    regions[pos] = std::make_shared<Region>(pos);
    return regions[pos];
}

std::shared_ptr<MapBlock> Dimension::getOrCreateMapBlock(glm::ivec3 mapBlockPosition) {
    auto region = getOrCreateRegion(Space::Region::world::fromMapBlock(mapBlockPosition));
    unsigned int index = Space::MapBlock::index(mapBlockPosition);

    if ((*region)[index] != nullptr) return (*region)[index];
    (*region).set(index, std::make_shared<MapBlock>(mapBlockPosition));
    return (*region)[index];
}
