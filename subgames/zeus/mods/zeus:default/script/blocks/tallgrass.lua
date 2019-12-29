for i=1,5,1 do
    zepha.register_block("zeus:default:tallgrass_" .. i, {
        culls = false,
        solid = false,
        name = "Tall Grass",
        model = "base:cross_plant",
        textures = {
            "biometint(zeus:default:tallgrass_"..i..")"
        },
        lowdef_render = false,
        selection_box = {
            {1/16, 0, 1/16, 15/16, 0.30 + i * 0.1, 15/16}
        },
        toughness = {
            hand = 0
        },
        on_break_client = function(pos)
            if math.random() > 0.8 then
                zepha.add_entity("zeus:default:dropped_item", vector.add(pos, v(0.5)),
                    {object = "zeus:materials:plant_fibre"});
            end
        end
    })
end