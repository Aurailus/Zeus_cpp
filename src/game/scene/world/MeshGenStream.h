//
// Created by aurailus on 27/03/19.
//

#pragma once

#include <queue>
#include <thread>
#include <glm/vec3.hpp>
#include <unordered_set>

#include "ChunkMeshDetails.h"
#include "../../../util/Vec.h"
#include "../../../def/gen/NoiseSample.h"

class Chunk;
class ClientGame;

class LocalDimension;

class MeshGenStream {
public:
    static const int THREADS = 4;
    static const int THREAD_QUEUE_SIZE = 32;

    explicit MeshGenStream(ClientGame& game, LocalDimension& dimension);
    ~MeshGenStream();

    void queue(glm::ivec3 pos, bool priority = false);

    //Will return a vector of MeshDetails pointers containing finished meshes.
    //Frees up the threads and starts new tasks.
    std::vector<ChunkMeshDetails*> update();

    struct Job {
        std::shared_ptr<Chunk> thisChunk = nullptr;
        std::array<std::shared_ptr<Chunk>, 6> adjacentChunks {};

        ChunkMeshDetails* meshDetails = new ChunkMeshDetails();

        bool busy = false;
    };

    struct Thread {
        explicit Thread(ClientGame &defs, std::array<NoiseSample, 3>& offsetSampler);
        void exec();

        ClientGame &game;
        std::array<NoiseSample, 3>& offsetSamplers;
        std::vector<Job> jobs = std::vector<Job>(THREAD_QUEUE_SIZE);

        bool keepAlive = true;
        std::thread thread {};
    };

    std::vector<Thread> threads;
private:

    LocalDimension& dimension;
    ClientGame& game;

    std::array<NoiseSample, 3> noiseSampler;
    std::deque<glm::ivec3> queuedTasks;
    std::unordered_set<glm::vec3, Vec::vec3> queuedMap;
};

