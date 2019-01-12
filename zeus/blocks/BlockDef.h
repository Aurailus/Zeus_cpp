//
// Created by aurailus on 02/12/18.
//

#ifndef GLPROJECT_BLOCKDEF_H
#define GLPROJECT_BLOCKDEF_H

#include "../mesh/BlockModel.h"

class BlockDef {

public:
    BlockDef(std::string identifier, BlockModel* model, bool solid);

    bool        isSolid();
    BlockModel* getModel();
    std::string getIdentifier();

    ~BlockDef();
private:
    bool solid;
    BlockModel* model;
    std::string identifier;
};


#endif //GLPROJECT_BLOCKDEF_H
