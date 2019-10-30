//
// Created by aurailus on 2019-10-29.
//

#pragma once

#include "../basic/GUIContainer.h"
#include "../../../../def/LocalDefs.h"
#include "../basic/GUIRect.h"
#include "../basic/GUIInventoryItem.h"
#include "../../../../def/texture/Font.h"

class GUIInventoryList : public GUIContainer {
public:
    GUIInventoryList() = default;
    GUIInventoryList(const std::string& key);

    void create(glm::vec2 scale, glm::vec4 padding, glm::vec2 innerPadding, unsigned int listWidth, unsigned int listHeight,
                LocalDefs& defs);
};
