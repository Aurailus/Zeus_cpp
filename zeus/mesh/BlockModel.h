//
// Created by aurailus on 04/12/18.
//

#ifndef GLPROJECT_BLOCKMODEL_H
#define GLPROJECT_BLOCKMODEL_H

#include <vector>
#include <sol.hpp>
#include "MeshPart.h"

using namespace std; //Just to preserve my sanity

struct BlockModel {
public:

    //MeshPart Vectors for each face. The vector may be empty but it may not contain null pointers.
    vector<MeshPart*> leftFaces, rightFaces, topFaces, bottomFaces, frontFaces, backFaces, noCulledFaces;
    bool culls, visible, nullModel;

    BlockModel(bool culls, bool visible);

    BlockModel(vector<MeshPart*> leftFaces, vector<MeshPart*> rightFaces, vector<MeshPart*> topFaces,
               vector<MeshPart*> bottomFaces, vector<MeshPart*> frontFaces, vector<MeshPart*> backFaces,
               vector<MeshPart*> noCulledFaces, bool culls, bool visible);

    BlockModel(MeshPart* leftFace, MeshPart* rightFace, MeshPart* topFace, MeshPart* bottomFace, MeshPart* frontFace,
               MeshPart* backFace, MeshPart* noCulledFace, bool culls, bool visible);

    ~BlockModel();

    static BlockModel* from_lua_def(sol::table model, sol::table textures, TextureAtlas* atlas, bool visible, bool culls);
};


#endif //GLPROJECT_BLOCKMODEL_H
