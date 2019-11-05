//
// Created by aurailus on 10/06/19.
//

#pragma once

#include <string>
#include <sol2/sol.hpp>
#include "SelectionBox.h"
#include "BlockModel.h"
#include "../ItemDef.h"
#include "../../lua/Callback.h"
#include "../../game/entity/Model.h"

class BlockDef : public ItemDef {
public:
    BlockDef() = default;
    BlockDef(const std::string& identifier, const std::string& name, const BlockModel& model, bool solid, const std::vector<SelectionBox>& sBoxes);
    BlockDef(const std::string& identifier, unsigned int index, const std::string& name, const BlockModel& model, bool solid, const std::vector<SelectionBox>& sBoxes);

    void createModel();

    BlockModel model;
    bool culls = false;
    bool solid = false;

    std::vector<SelectionBox> sBoxes;
    sptr<Model> entityModel = std::make_shared<Model>();

    std::unordered_map<Callback, sol::function, Util::EnumClassHash> callbacks {};
};