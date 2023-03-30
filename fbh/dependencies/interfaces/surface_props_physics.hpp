#pragma once
#include <cstddef>

struct surface_data {
    std::byte pad[80];
    float maxspeedfactor;
    float jumpfactor;
    float penetrationmodifier;
    float damagemodifier;
    short material;
    bool climbable;
};

class physics_surface_props {
public:
    auto get_surface_data(int index) {
        return util::call_virtual_new<surface_data*, int>(this, 5, index);
    }
};