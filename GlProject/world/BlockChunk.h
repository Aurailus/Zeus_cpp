//
// Created by aurailus on 14/12/18.
//

#ifndef GLPROJECT_BLOCKCHUNK_H
#define GLPROJECT_BLOCKCHUNK_H

#include <vec3.hpp>
#include <vector>

class BlockChunk {
public:
    BlockChunk() = default;
    explicit BlockChunk(std::vector<int>* blocks);

    int getBlock(int ind);
    int getBlock(glm::vec3* pos);
    int getBlock(int x, int y, int z);

    //TODO: Add block setting methods as well
private:
    std::vector<int>* blocks;
};

#endif //GLPROJECT_BLOCKCHUNK_H