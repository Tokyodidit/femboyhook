#pragma once

#include "xorstr.h"
#include "singleton.hpp"
#include "fnv.hpp"
#include "utilities.hpp"
#include "notifications.hpp"
#include "../minhook/minhook.h"
#define FMT_HEADER_ONLY
#include "../fmt/format.h"
#include "../interfaces/interfaces.hpp"
#include "../../source-sdk/sdk.hpp"
#include "../../core/hooks/hooks.hpp"
#include "../math/math.hpp"
#include "render/render.hpp"
#include "console/console.hpp"
#include "easing.hpp"

namespace csgo {
	extern player_t* local_player;
	extern c_usercmd* global_cmd;
}