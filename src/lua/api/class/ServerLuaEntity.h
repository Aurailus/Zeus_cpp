//
// Created by aurailus on 2019-12-28.
//

#pragma once

#include <memory>
#include "../../../server/world/ServerEntity.h"
#include "../../../def/ServerGame.h"

class ServerLuaEntity {
public:
    ServerLuaEntity(std::unique_ptr<ServerEntity> entity, unsigned int id, ServerGame& defs) :
            entity(std::move(entity)), id(id), defs(defs) {}

    std::unique_ptr<ServerEntity> entity = nullptr;
    unsigned int id;
    ServerGame& defs;

    void snap_pos(const sol::table& pos);
    void set_pos(const sol::table& pos);
    sol::table get_pos(sol::this_state s);

    void snap_visual_offset(const sol::table& vs);
    void set_visual_offset(const sol::table& pos);
    sol::table get_visual_offset(sol::this_state s);

    void snap_pitch(float rot);
    void set_pitch(float rot);
    float get_pitch();

    void snap_yaw(float rot);
    void set_yaw(float rot);
    float get_yaw();

    void snap_roll(float rot);
    void set_roll(float rot);
    float get_roll();

    void snap_scale(float scale);
    void set_scale(float scale);
    float get_scale();

    void set_display_type(const std::string& type, const std::string& arg, sol::optional<std::string> arg2);
};