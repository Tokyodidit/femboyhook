#include <pch.h>
#include "../features.hpp"
#include "../../../dependencies/rpc/includes/discord_rpc.h"
#include "../../../dependencies/rpc/includes/discord_register.h"

void features::discord::initialize() {
    // Initialize
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize(xorstr("1082024684557701150"), &Handle, 1, NULL);
    console::log(xorstr("discord rpc initialized\n"));
    // Update
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = xorstr("DEV");
    discordPresence.largeImageKey = xorstr("Star");
    Discord_UpdatePresence(&discordPresence);
}

void features::discord::release() {
    // Release
    Discord_Shutdown();
}