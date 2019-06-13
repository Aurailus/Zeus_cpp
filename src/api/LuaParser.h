//
// Created by aurailus on 11/06/19.
//

#ifndef ZEUS_LUAPARSER_H
#define ZEUS_LUAPARSER_H

#include <sol.hpp>
#include <iostream>
#include <vec3.hpp>
#include "../util/Path.h"
#include "../util/Log.h"

class LuaParser {
public:
    explicit LuaParser(std::string root);
    std::string root;
    Path root_path;

    sol::state lua;
    sol::table zeus;

    sol::table vecToTable(glm::vec3 vec);

protected:
    int DoFileSandboxed(std::string file);
};


#endif //ZEUS_LUAPARSER_H
