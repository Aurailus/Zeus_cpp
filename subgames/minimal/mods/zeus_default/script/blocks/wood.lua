zepha.register_block(":wood", {
    name = "Log",

    model = "base:block",
    textures = {
        "zeus:default:oak_log_top",
        "zeus:default:oak_log_top",
        "zeus:default:oak_log_side"
    },

    tool_props = {
        health = 30,
        multipliers = {
            chop = 2.0,
            crack = 1.7,
            grab = 0,
            _other = 0.5
        }
    },

    yields = "zeus:default:wood"
})