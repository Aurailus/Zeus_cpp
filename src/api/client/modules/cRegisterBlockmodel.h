//
// Created by aurailus on 28/06/19.
//

#ifndef ZEUS_CREGISTERBLOCKMODEL_H
#define ZEUS_CREGISTERBLOCKMODEL_H

#include <sol2/sol.hpp>

namespace ClientApi {
    void register_blockmodel(sol::state& lua, sol::table& zeus) {
        zeus["registered_blockmodels"] = lua.create_table();

        zeus.set_function("register_blockmodel", [&](std::string identifier, sol::table data) {
            if (identifier.length() == 0) throw "Missing Identifier";
            zeus["registered_blockmodels"][identifier] = data;
        });
    }
}

#endif //ZEUS_CREGISTERBLOCKMODEL_H
