//
// Created by aurailus on 04/10/19.
//

#pragma once

#include <sol2/sol.hpp>

namespace ClientApi {
    void register_entity(sol::state& lua, sol::table& core) {
        core["registered_entities"] = lua.create_table();

        core.set_function("register_entity", [&](sol::this_environment env, std::string identifier, sol::table data) {
            if (identifier.length() == 0) throw "Missing Identifier";
            auto modname = static_cast<sol::environment>(env).get<std::string>("_MODNAME");
            if (identifier.compare(0, modname.length() + 1, modname + ":")) {
                std::cout << Log::err << "\"" << identifier << "\" does not begin with its mod's prefix \"" << modname << "\"!" << Log::endl;
            }
            data["__index"] = data;
            core["registered_entities"][identifier] = data;
        });
    }
}