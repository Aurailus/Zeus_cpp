local function collides(entity)
    return zepha.get_block({
        x = math.floor(entity.pos.x),
        y = math.floor(entity.pos.y - 0.5),
        z = math.floor(entity.pos.z)}) ~= "air"
end

zepha.register_entity("zeus:default:dropped_item", {
    display = "gameobject",
    display_object = "zeus:default:stone",

    on_create = function(self, static)
        static = static or {}
        self.item = static.item or self.display_object

        self.object:set_display_type("gameobject", self.item)

        self.tick = 0
        self.time = static.time or 0
        self.speed = static.speed or 20
        self.velocityY = static.velocityY or -100

        self.delete = false
        self.scooping = false

        if not zepha.registered_blocks[static.object] then self.object.scale = 1/2
        else self.object.scale = 1/3 end
    end,
    on_update = function(self, delta)
        self.object.yaw = self.object.yaw + self.speed
        if self.speed > 4 then self.speed = self.speed * 0.92 end

        self.tick = self.tick + delta

        if self.time > 5 * 60 then
            zepha.remove_entity(self)
            return
        end

        if self.scooping then return end

        if not collides(self.object) then
            self.velocityY = math.min(self.velocityY + 300 * delta, 480)
        end

        local iter = 1
        while not collides(self.object) and iter <= math.abs(self.velocityY * delta) do
            local interval = 0
            if self.velocityY < 0 then interval = 1/16 else interval = -1/16 end
            self.object.pos = vector.add(self.object.pos, v{0, interval, 0})
            iter = iter + 0.25
        end

        self.object.visual_offset = v{0, math.sin(self.time * 2) / 8, 0}

        if collides(self.object) then
            self.velocityY = 0
            self.time = self.time + delta
        end

        if self.tick > 0.15 then
            self.tick = 0
            if zepha.client then self:check_collect() end
        end
    end,
    check_collect = function(self)
        if vector.distance(zepha.player.pos, self.object.pos) < 2 then
            self.object.pos = vector.add(zepha.player.pos, v{0, 0.90, 0})
            self.scooping = true

            zepha.delay(function()
                zepha.remove_entity(self)
                zepha.player:get_inventory():get_list("main"):add_stack({self.item, 1})
            end, 2/20)
        end
    end,
    on_serialize = function(self)
        return {
            velocityY = self.velocityY,
            time = self.time,
            speed = self.speed
        }
    end
})