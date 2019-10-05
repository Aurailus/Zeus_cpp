zepha.register_block("default:sand", {
    name = "Sand",
    model = "default:block",
    textures = {"zeus:default:sand"},
    toughness = {
        hand = 3,
        shovel = 1,
        pick = 2
    },
    drop = "default:sand",
    on_break_client = function(pos)
        zepha.add_entity("default:dropped_item", {x = pos.x + 0.5, y = pos.y + 0.5, z = pos.z + 0.5},
            {object = zepha.registered_blocks["default:sand"].drop});
    end
})