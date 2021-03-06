-- zepha.register_block("zeus:default:light_light", {
--     name = "Light",
--     model = "base:block",
--     textures = {"zeus:default:light_blue"},
--     toughness = {
--         hand = 3,
--         shovel = 1,
--         pick = 2
--     },
--     yields = "zeus:default:light_light",
--     light_source = {10, 20, 31}
-- })

-- local light_types = {
--     V{0, 0, 31},
--     V{0, 31, 31},
--     V{0, 31, 0},
--     V{31, 31, 0},
--     V{31, 16, 0},
--     V{31, 0, 0},
--     V{31, 0, 31}
-- }
--
-- for n, c in pairs(light_types) do
--     local target = 1
--
--     zepha.register_block("zeus:default:light_" .. tostring(n), {
--         name = "Rainbow Light",
--         model = "base:block",
--         textures = {"zeus:default:light_blue"},
--         light_source = c / 2,
--         on_place_client = function(pos)
--             zepha.after(function()
--                 target = target + 1
--                 if target == 8 then target = 1 end
--                 zepha.set_block(pos, "zeus:default:light_" .. tostring(target))
--                 return true
--             end, 0.15)
--         end
--     })
-- end

zepha.register_block("zeus:default:light_blue", {
    name = "Blue Light",
    model = "base:block",
    textures = {"zeus:default:light_blue"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_blue",
    light_source = {0, 0, 31}
})

zepha.register_block("zeus:default:light_teal", {
    name = "Teal Light",
    model = "base:block",
    textures = {"zeus:default:light_blue"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_teal",
    light_source = {0, 31, 31}
})

zepha.register_block("zeus:default:light_green", {
    name = "Green Light",
    model = "base:block",
    textures = {"zeus:default:light_green"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_green",
    light_source = {0, 31, 0}
})

zepha.register_block("zeus:default:light_yellow", {
    name = "Yellow Light",
    model = "base:block",
    textures = {"zeus:default:light_green"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_yellow",
    light_source = {31, 31, 0}
})

zepha.register_block("zeus:default:light_orange", {
    name = "Orange Light",
    model = "base:block",
    textures = {"zeus:default:light_red"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_orange",
    light_source = {31, 16, 0}
})

zepha.register_block("zeus:default:light_red", {
    name = "Red Light",
    model = "base:block",
    textures = {"zeus:default:light_red"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    yields = "zeus:default:light_red",
    light_source = {31, 0, 0}
})

zepha.register_block("zeus:default:light_purple", {
  name = "Purple Light",
  model = "base:block",
  textures = {"zeus:default:light_red"},
  toughness = {
      hand = 3,
      shovel = 1,
      pick = 2
  },
  yields = "zeus:default:light",
  light_source = {31, 0, 31}
})