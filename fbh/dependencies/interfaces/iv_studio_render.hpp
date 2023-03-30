#pragma once
#include "i_material_system.hpp"
#include "../utilities/xorstr.h"

enum class override_type {
    normal = 0,
    build_shadows,
    depth_write,
    custom_material,
    ssao_depth_write
};

class iv_studio_render {
private:
    std::byte pad_0[0x250];
    i_material* material_override;
    std::byte pad_1[0xC];
    override_type type;
public:
    bool isforced_materialoverride() {
        if (!material_override)
            return type == override_type::depth_write || type == override_type::ssao_depth_write;

        return std::string_view{ material_override->get_name() }.starts_with(xorstr("dev/glow"));
    }
};