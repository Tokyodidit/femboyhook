#include <pch.h>
#include "config.hpp"
#include "variables.hpp"
#include "../../dependencies/utilities/base64/base64.h"
#include "../../dependencies/utilities/json.hpp"
#include <winuser.h>
#include <winbase.h>
#include <format>

const char* path = "C:\\Users\\Public\\Documents\\femboyhook_";

nlohmann::json varsToJSON() {
	nlohmann::json config;

	// MENU
	config["menu"]["accent"] = var::menu::accent;
	config["menu"]["background"] = var::menu::background;
	config["menu"]["background_color"] = var::menu::background_color;
	config["menu"]["background_effect"] = var::menu::background_effect;
	config["menu"]["background_effect_color"] = var::menu::background_effect_color;
	config["menu"]["keybind"] = var::menu::keybind;

	// LEGIT
	config["legit"]["aimbot"]["enabled"] = var::legit::aimbot::enabled;
	config["legit"]["aimbot"]["keybind"] = var::legit::aimbot::keybind;
	config["legit"]["aimbot"]["kb_style"] = var::legit::aimbot::kb_style;
	config["legit"]["aimbot"]["fov"] = var::legit::aimbot::fov;
	config["legit"]["aimbot"]["smooth"] = var::legit::aimbot::smooth;
	config["legit"]["aimbot"]["rcs"] = var::legit::aimbot::rcs;
	config["legit"]["aimbot"]["autowall"] = var::legit::aimbot::autowall;
	config["legit"]["aimbot"]["silent"] = var::legit::aimbot::silent;
	config["legit"]["aimbot"]["head"] = var::legit::aimbot::head;
	config["legit"]["aimbot"]["chest"] = var::legit::aimbot::chest;
	config["legit"]["aimbot"]["stomach"] = var::legit::aimbot::stomach;
	config["legit"]["aimbot"]["draw_fov"] = var::legit::aimbot::draw_fov;
	config["legit"]["aimbot"]["fov_color"] = var::legit::aimbot::fov_color;
	config["legit"]["backtrack"]["enabled"] = var::legit::backtrack::enabled;
	config["legit"]["backtrack"]["keybind"] = var::legit::backtrack::keybind;
	config["legit"]["backtrack"]["kb_style"] = var::legit::backtrack::kb_style;
	config["legit"]["backtrack"]["length"] = var::legit::backtrack::length;
	config["legit"]["triggerbot"]["enabled"] = var::legit::triggerbot::enabled;
	config["legit"]["triggerbot"]["keybind"] = var::legit::triggerbot::keybind;
	config["legit"]["triggerbot"]["kb_style"] = var::legit::triggerbot::kb_style;
	config["legit"]["exploit"]["enabled"] = var::legit::exploit::enabled;
	// VISUAL
	config["visuals"]["esp"]["enabled"] = var::visuals::esp::enabled;
	config["visuals"]["esp"]["keybind"] = var::visuals::esp::keybind;
	config["visuals"]["esp"]["kb_style"] = var::visuals::esp::kb_style;
	config["visuals"]["esp"]["radar"] = var::visuals::esp::radar;
	config["visuals"]["esp"]["name"]["enabled"] = var::visuals::esp::name::enabled;
	config["visuals"]["esp"]["name"]["color"] = var::visuals::esp::name::color;
	config["visuals"]["esp"]["box"]["enabled"] = var::visuals::esp::box::enabled;
	config["visuals"]["esp"]["box"]["color"] = var::visuals::esp::box::color;
	config["visuals"]["esp"]["box"]["corner"] = var::visuals::esp::box::corner;
	config["visuals"]["esp"]["box"]["fill"] = var::visuals::esp::box::fill;
	config["visuals"]["esp"]["box"]["fill_color"] = var::visuals::esp::box::fill_color;
	config["visuals"]["esp"]["box"]["fill_color2"] = var::visuals::esp::box::fill_color2;
	config["visuals"]["esp"]["weapon"]["enabled"] = var::visuals::esp::weapon::enabled;
	config["visuals"]["esp"]["weapon"]["color"] = var::visuals::esp::weapon::color;
	config["visuals"]["esp"]["ammo"]["enabled"] = var::visuals::esp::ammo::enabled;
	config["visuals"]["esp"]["ammo"]["color"] = var::visuals::esp::ammo::color;
	config["visuals"]["esp"]["ammo"]["color2"] = var::visuals::esp::ammo::color2;
	config["visuals"]["esp"]["health"]["enabled"] = var::visuals::esp::health::enabled;
	config["visuals"]["esp"]["health"]["override_color"] = var::visuals::esp::health::override_color;
	config["visuals"]["esp"]["health"]["color"] = var::visuals::esp::health::color;
	config["visuals"]["esp"]["health"]["color2"] = var::visuals::esp::health::color2;
	config["visuals"]["esp"]["flags"]["enabled"] = var::visuals::esp::flags::enabled;
	config["visuals"]["esp"]["flags"]["color"] = var::visuals::esp::flags::color;
	config["visuals"]["esp"]["flags"]["color2"] = var::visuals::esp::flags::color2;
	config["visuals"]["esp"]["flags"]["health"] = var::visuals::esp::flags::health;
	config["visuals"]["esp"]["flags"]["armor"] = var::visuals::esp::flags::armor;
	config["visuals"]["esp"]["flags"]["distance"] = var::visuals::esp::flags::distance;
	config["visuals"]["esp"]["flags"]["money"] = var::visuals::esp::flags::money;
	config["visuals"]["esp"]["flags"]["flashed"] = var::visuals::esp::flags::flashed;
	config["visuals"]["esp"]["flags"]["scoped"] = var::visuals::esp::flags::scoped;
	config["visuals"]["esp"]["flags"]["bomb"] = var::visuals::esp::flags::bomb;
	config["visuals"]["esp"]["flags"]["defusing"] = var::visuals::esp::flags::defusing;
	config["visuals"]["esp"]["flags"]["kit"] = var::visuals::esp::flags::kit;
	config["visuals"]["esp"]["flags"]["bot"] = var::visuals::esp::flags::bot;
	config["visuals"]["esp"]["snaplines"]["enabled"] = var::visuals::esp::snaplines::enabled;
	config["visuals"]["esp"]["snaplines"]["color"] = var::visuals::esp::snaplines::color;
	config["visuals"]["esp"]["viewangles"]["enabled"] = var::visuals::esp::viewangles::enabled;
	config["visuals"]["esp"]["viewangles"]["color"] = var::visuals::esp::viewangles::color;
	config["visuals"]["esp"]["viewangles"]["length"] = var::visuals::esp::viewangles::length;
	config["visuals"]["esp"]["skeleton"]["enabled"] = var::visuals::esp::skeleton::enabled;
	config["visuals"]["esp"]["skeleton"]["color"] = var::visuals::esp::skeleton::color;
	config["visuals"]["esp"]["head"]["enabled"] = var::visuals::esp::head::enabled;
	config["visuals"]["esp"]["head"]["color"] = var::visuals::esp::head::color;
	config["visuals"]["esp"]["dlight"]["enabled"] = var::visuals::esp::dlight::enabled;
	config["visuals"]["esp"]["dlight"]["color"] = var::visuals::esp::dlight::color;
	config["visuals"]["esp"]["dlight"]["radius"] = var::visuals::esp::dlight::radius;
	config["visuals"]["chams"]["enabled"] = var::visuals::chams::enabled;
	config["visuals"]["chams"]["keybind"] = var::visuals::chams::keybind;
	config["visuals"]["chams"]["kb_style"] = var::visuals::chams::kb_style;
	config["visuals"]["chams"]["model_occlusion"] = var::visuals::chams::model_occlusion;
	config["visuals"]["chams"]["wireframe_overlay"] = var::visuals::chams::wireframe_overlay;
	config["visuals"]["chams"]["visible"]["enabled"] = var::visuals::chams::visible::enabled;
	config["visuals"]["chams"]["visible"]["material"] = var::visuals::chams::visible::material;
	config["visuals"]["chams"]["visible"]["color"] = var::visuals::chams::visible::color;
	config["visuals"]["chams"]["occluded"]["enabled"] = var::visuals::chams::occluded::enabled;
	config["visuals"]["chams"]["occluded"]["material"] = var::visuals::chams::occluded::material;
	config["visuals"]["chams"]["occluded"]["color"] = var::visuals::chams::occluded::color;
	config["visuals"]["chams"]["visible_overlay"]["enabled"] = var::visuals::chams::visible_overlay::enabled;
	config["visuals"]["chams"]["visible_overlay"]["material"] = var::visuals::chams::visible_overlay::material;
	config["visuals"]["chams"]["visible_overlay"]["color"] = var::visuals::chams::visible_overlay::color;
	config["visuals"]["chams"]["occluded_overlay"]["enabled"] = var::visuals::chams::occluded_overlay::enabled;
	config["visuals"]["chams"]["occluded_overlay"]["material"] = var::visuals::chams::occluded_overlay::material;
	config["visuals"]["chams"]["occluded_overlay"]["color"] = var::visuals::chams::occluded_overlay::color;
	config["visuals"]["chams"]["arms"]["enabled"] = var::visuals::chams::arms::enabled;
	config["visuals"]["chams"]["arms"]["occluded"] = var::visuals::chams::arms::occluded;
	config["visuals"]["chams"]["arms"]["draw_original"] = var::visuals::chams::arms::draw_original;
	config["visuals"]["chams"]["arms"]["remove_sleeves"] = var::visuals::chams::arms::remove_sleeves;
	config["visuals"]["chams"]["arms"]["material"] = var::visuals::chams::arms::material;
	config["visuals"]["chams"]["arms"]["color"] = var::visuals::chams::arms::color;
	config["visuals"]["chams"]["arms"]["overlay"]["enabled"] = var::visuals::chams::arms::overlay::enabled;
	config["visuals"]["chams"]["arms"]["overlay"]["wireframe"] = var::visuals::chams::arms::overlay::wireframe;
	config["visuals"]["chams"]["arms"]["overlay"]["material"] = var::visuals::chams::arms::overlay::material;
	config["visuals"]["chams"]["arms"]["overlay"]["color"] = var::visuals::chams::arms::overlay::color;
	config["visuals"]["chams"]["weapon"]["enabled"] = var::visuals::chams::weapon::enabled;
	config["visuals"]["chams"]["weapon"]["occluded"] = var::visuals::chams::weapon::occluded;
	config["visuals"]["chams"]["weapon"]["draw_original"] = var::visuals::chams::weapon::draw_original;
	config["visuals"]["chams"]["weapon"]["material"] = var::visuals::chams::weapon::material;
	config["visuals"]["chams"]["weapon"]["color"] = var::visuals::chams::weapon::color;
	config["visuals"]["chams"]["weapon"]["overlay"]["enabled"] = var::visuals::chams::weapon::overlay::enabled;
	config["visuals"]["chams"]["weapon"]["overlay"]["wireframe"] = var::visuals::chams::weapon::overlay::wireframe;
	config["visuals"]["chams"]["weapon"]["overlay"]["material"] = var::visuals::chams::weapon::overlay::material;
	config["visuals"]["chams"]["weapon"]["overlay"]["color"] = var::visuals::chams::weapon::overlay::color;
	config["visuals"]["glow"]["enabled"] = var::visuals::glow::enabled;
	config["visuals"]["glow"]["keybind"] = var::visuals::glow::keybind;
	config["visuals"]["glow"]["kb_style"] = var::visuals::glow::kb_style;
	config["visuals"]["glow"]["player"] = var::visuals::glow::player;
	config["visuals"]["glow"]["color"] = var::visuals::glow::color;
	config["visuals"]["glow"]["style"] = var::visuals::glow::style;
	config["visuals"]["glow"]["bomb"] = var::visuals::glow::bomb;
	config["visuals"]["glow"]["bomb_color"] = var::visuals::glow::bomb_color;
	config["visuals"]["glow"]["chicken"] = var::visuals::glow::chicken;
	config["visuals"]["glow"]["chicken_color"] = var::visuals::glow::chicken_color;
	config["visuals"]["glow"]["weapon"] = var::visuals::glow::weapon;
	config["visuals"]["glow"]["weapon_color"] = var::visuals::glow::weapon_color;
	config["visuals"]["trail"]["enabled"] = var::visuals::trail::enabled;
	config["visuals"]["trail"]["color"] = var::visuals::trail::color;
	config["visuals"]["trail"]["life"] = var::visuals::trail::life;
	config["visuals"]["local_dlight"]["enabled"] = var::visuals::local_dlight::enabled;
	config["visuals"]["local_dlight"]["color"] = var::visuals::local_dlight::color;
	config["visuals"]["local_dlight"]["radius"] = var::visuals::local_dlight::radius;
	config["visuals"]["bullet_tracers"]["enabled"] = var::visuals::bullet_tracers::enabled;
	config["visuals"]["bullet_tracers"]["color"] = var::visuals::bullet_tracers::color;
	config["visuals"]["bullet_impacts"]["enabled"] = var::visuals::bullet_impacts::enabled;
	config["visuals"]["bullet_impacts"]["color"] = var::visuals::bullet_impacts::color;
	config["visuals"]["snipercrosshair"]["enabled"] = var::visuals::snipercrosshair::enabled;
	config["visuals"]["snipercrosshair"]["color"] = var::visuals::snipercrosshair::color;
	config["visuals"]["recoilcrosshair"]["enabled"] = var::visuals::recoilcrosshair::enabled;
	config["visuals"]["recoilcrosshair"]["color"] = var::visuals::recoilcrosshair::color;
	config["visuals"]["view"]["fov"] = var::visuals::view::fov;
	config["visuals"]["view"]["model"] = var::visuals::view::model;
	config["visuals"]["view"]["angle"] = var::visuals::view::angle;
	config["visuals"]["view"]["aspect"] = var::visuals::view::aspect;
	config["visuals"]["motionblur"]["enabled"] = var::visuals::motionblur::enabled;
	config["visuals"]["motionblur"]["strength"] = var::visuals::motionblur::strength;
	config["visuals"]["fog_changer"]["enabled"] = var::visuals::fog_changer::enabled;
	config["visuals"]["fog_changer"]["color"] = var::visuals::fog_changer::color;
	config["visuals"]["fog_changer"]["start"] = var::visuals::fog_changer::start;
	config["visuals"]["nightmode"]["enabled"] = var::visuals::nightmode::enabled;
	config["visuals"]["nightmode"]["color"] = var::visuals::nightmode::color;
	config["visuals"]["nightmode"]["brightness"] = var::visuals::nightmode::brightness;
	config["visuals"]["particles"]["enabled"] = var::visuals::particles::enabled;
	config["visuals"]["particles"]["color"] = var::visuals::particles::color;
	config["visuals"]["particles"]["color2"] = var::visuals::particles::color2;
	config["visuals"]["indicators"]["enabled"] = var::visuals::indicators::enabled;
	config["visuals"]["indicators"]["color"] = var::visuals::indicators::color;
	config["visuals"]["indicators"]["color2"] = var::visuals::indicators::color2;
	config["visuals"]["indicators"]["velocity"] = var::visuals::indicators::velocity;
	config["visuals"]["indicators"]["stamina"] = var::visuals::indicators::stamina;
	config["visuals"]["indicators"]["pre"] = var::visuals::indicators::pre;
	config["visuals"]["indicators"]["loss"] = var::visuals::indicators::loss;
	config["visuals"]["indicators"]["keybinds"] = var::visuals::indicators::keybinds;
	config["visuals"]["indicators"]["fade"] = var::visuals::indicators::fade;
	config["visuals"]["indicators"]["font"] = var::visuals::indicators::font;
	config["visuals"]["thirdperson"]["keybind"] = var::visuals::thirdperson::keybind;
	config["visuals"]["thirdperson"]["kb_style"] = var::visuals::thirdperson::kb_style;
	config["visuals"]["thirdperson"]["distance"] = var::visuals::thirdperson::distance;
	config["visuals"]["remove_scope"]["enabled"] = var::visuals::remove_scope::enabled;
	config["visuals"]["remove_scope"]["color"] = var::visuals::remove_scope::color;
	config["visuals"]["sky_changer"] = var::visuals::sky_changer;
	config["visuals"]["disable_postprocess"] = var::visuals::disable_postprocess;
	config["visuals"]["fullbright"] = var::visuals::fullbright;
	config["visuals"]["watermark"] = var::visuals::watermark;
	config["visuals"]["speclist"] = var::visuals::speclist;
	config["visuals"]["wireframe_smoke"] = var::visuals::wireframe_smoke;
	config["visuals"]["flash_opacity"] = var::visuals::flash_opacity;

	// MISC
	config["misc"]["clantag"] = var::misc::clantag;
	config["misc"]["killsay"] = var::misc::killsay;
	config["misc"]["event_logs"] = var::misc::event_logs;
	config["misc"]["chat_logs"] = var::misc::chat_logs;
	config["misc"]["vote_reveal"] = var::misc::vote_reveal;
	config["misc"]["movement_notify"] = var::misc::movement_notify;
	config["misc"]["hit_sound"] = var::misc::hit_sound;
	config["misc"]["detection_sound"] = var::misc::detection_sound;
	config["misc"]["autoweapon"] = var::misc::autoweapon;
	config["misc"]["autoaccept"] = var::misc::autoaccept;
	config["misc"]["rank_reveal"] = var::misc::rank_reveal;
	config["misc"]["unlock_inventory"] = var::misc::unlock_inventory;
	config["misc"]["doorspammer"]["enabled"] = var::misc::doorspammer::enabled;
	config["misc"]["doorspammer"]["keybind"] = var::misc::doorspammer::keybind;
	config["misc"]["doorspammer"]["kb_style"] = var::misc::doorspammer::kb_style;
	config["misc"]["effects"]["hit_boost"] = var::misc::effects::hit_boost;
	config["misc"]["effects"]["hit_sparks"] = var::misc::effects::hit_sparks;
	config["misc"]["effects"]["hit_beam"] = var::misc::effects::hit_beam;
	config["misc"]["effects"]["detection_boost"] = var::misc::effects::detection_boost;
	config["misc"]["effects"]["detection_sparks"] = var::misc::effects::detection_sparks;
	config["misc"]["effects"]["detection_beam"] = var::misc::effects::detection_beam;
	config["misc"]["effects"]["color"] = var::misc::effects::color;
	config["misc"]["detection_indicator"]["enabled"] = var::misc::detection_indicator::enabled;
	config["misc"]["detection_indicator"]["color"] = var::misc::detection_indicator::color;
	config["misc"]["knife"]["model"] = var::misc::knife::model;
	config["misc"]["knife"]["skin"] = var::misc::knife::skin;
	config["misc"]["knife"]["custom_color"] = var::misc::knife::custom_color;
	config["misc"]["knife"]["color1"] = var::misc::knife::color1;
	config["misc"]["knife"]["color2"] = var::misc::knife::color2;
	config["misc"]["knife"]["color3"] = var::misc::knife::color3;
	config["misc"]["knife"]["color4"] = var::misc::knife::color4;
	config["misc"]["glove"]["model"] = var::misc::glove::model;
	config["misc"]["glove"]["skin"] = var::misc::glove::skin;

	// MOVEMENT
	config["movement"]["bunnyhop"]["enabled"] = var::movement::bunnyhop::enabled;
	config["movement"]["bunnyhop"]["hitchance"] = var::movement::bunnyhop::hitchance;
	config["movement"]["edgebug"]["enabled"] = var::movement::edgebug::enabled;
	config["movement"]["edgebug"]["keybind"] = var::movement::edgebug::keybind;
	config["movement"]["edgebug"]["kb_style"] = var::movement::edgebug::kb_style;
	config["movement"]["pixelsurf"]["enabled"] = var::movement::pixelsurf::enabled;
	config["movement"]["pixelsurf"]["keybind"] = var::movement::pixelsurf::keybind;
	config["movement"]["pixelsurf"]["kb_style"] = var::movement::pixelsurf::kb_style;
	config["movement"]["jumpbug"]["enabled"] = var::movement::jumpbug::enabled;
	config["movement"]["jumpbug"]["keybind"] = var::movement::jumpbug::keybind;
	config["movement"]["jumpbug"]["kb_style"] = var::movement::jumpbug::kb_style;
	config["movement"]["edgejump"]["enabled"] = var::movement::edgejump::enabled;
	config["movement"]["edgejump"]["keybind"] = var::movement::edgejump::keybind;
	config["movement"]["edgejump"]["kb_style"] = var::movement::edgejump::kb_style;
	config["movement"]["minijump"]["enabled"] = var::movement::minijump::enabled;
	config["movement"]["minijump"]["keybind"] = var::movement::minijump::keybind;
	config["movement"]["minijump"]["kb_style"] = var::movement::minijump::kb_style;
	config["movement"]["longjump"]["enabled"] = var::movement::longjump::enabled;
	config["movement"]["longjump"]["keybind"] = var::movement::longjump::keybind;
	config["movement"]["longjump"]["kb_style"] = var::movement::longjump::kb_style;
	config["movement"]["ladderglide"]["enabled"] = var::movement::ladderglide::enabled;
	config["movement"]["ladderglide"]["keybind"] = var::movement::ladderglide::keybind;
	config["movement"]["ladderglide"]["kb_style"] = var::movement::ladderglide::kb_style;
	config["movement"]["fakebackwards"]["enabled"] = var::movement::fakebackwards::enabled;
	config["movement"]["fakebackwards"]["keybind"] = var::movement::fakebackwards::keybind;
	config["movement"]["fakebackwards"]["angle"] = var::movement::fakebackwards::angle;
	config["movement"]["fakebackwards"]["kb_style"] = var::movement::fakebackwards::kb_style;
	config["movement"]["staminahop"]["enabled"] = var::movement::staminahop::enabled;
	config["movement"]["staminahop"]["keybind"] = var::movement::staminahop::keybind;
	config["movement"]["staminahop"]["kb_style"] = var::movement::staminahop::kb_style;
	config["movement"]["blockbot"]["enabled"] = var::movement::blockbot::enabled;
	config["movement"]["blockbot"]["keybind"] = var::movement::blockbot::keybind;
	config["movement"]["blockbot"]["kb_style"] = var::movement::blockbot::kb_style;
	config["movement"]["checkpoint"]["enabled"] = var::movement::checkpoint::enabled;
	config["movement"]["checkpoint"]["keybind"] = var::movement::checkpoint::keybind;
	config["movement"]["checkpoint"]["keybind_teleport"] = var::movement::checkpoint::keybind_teleport;
	config["movement"]["ticks"] = var::movement::ticks;
	config["movement"]["lock_factor"] = var::movement::lock_factor;
	config["movement"]["fastduck"] = var::movement::fastduck;
	config["movement"]["faststop"] = var::movement::faststop;
	config["movement"]["slidewalk"] = var::movement::slidewalk;
	config["movement"]["autoalign"] = var::movement::autoalign;

	return config;
}

void varsFromJSON(nlohmann::json config) {
	if (config.contains("menu")) {
		// Menu section
		nlohmann::json menu = config["menu"];

		if (menu.contains("accent")) std::copy(menu["accent"].begin(), menu["accent"].end(), var::menu::accent); // read color array
		if (menu.contains("background")) var::menu::background = menu["background"].get<bool>(); // cast to bool
		if (menu.contains("background_color")) std::copy(menu["background_color"].begin(), menu["background_color"].end(), var::menu::background_color); // read color array
		if (menu.contains("background_effect")) var::menu::background_effect = menu["background_effect"].get<bool>(); // cast to bool
		if (menu.contains("background_effect_color")) std::copy(menu["background_effect_color"].begin(), menu["background_effect_color"].end(), var::menu::background_effect_color); // read color array
		if (menu.contains("keybind")) var::menu::keybind = menu["keybind"].get<int>(); // cast to int
	}

	if (config.contains("legit")) {
		// Legit section
		nlohmann::json legit = config["legit"];

		if (legit.contains("aimbot")) {
			// Aimbot
			nlohmann::json aimbot = legit["aimbot"];

			if (aimbot.contains("enabled")) var::legit::aimbot::enabled = aimbot["enabled"].get<bool>(); // cast to bool
			if (aimbot.contains("keybind")) var::legit::aimbot::keybind = aimbot["keybind"].get<int>(); // cast to int
			if (aimbot.contains("kb_style")) var::legit::aimbot::kb_style = aimbot["kb_style"].get<int>(); // cast to int
			if (aimbot.contains("fov")) var::legit::aimbot::fov = std::clamp(aimbot["fov"].get<int>(), 1, 180); // clamp min and max values
			if (aimbot.contains("smooth")) var::legit::aimbot::smooth = std::clamp(aimbot["smooth"].get<int>(), 1, 100); // clamp min and max values
			if (aimbot.contains("rcs")) var::legit::aimbot::rcs = std::clamp(aimbot["rcs"].get<int>(), 0, 100); // clamp min and max values
			if (aimbot.contains("autowall")) var::legit::aimbot::autowall = aimbot["autowall"].get<bool>(); // cast to bool
			if (aimbot.contains("silent")) var::legit::aimbot::silent = aimbot["silent"].get<bool>(); // cast to bool
			if (aimbot.contains("head")) var::legit::aimbot::head = aimbot["head"].get<bool>(); // cast to bool
			if (aimbot.contains("chest")) var::legit::aimbot::chest = aimbot["chest"].get<bool>(); // cast to bool
			if (aimbot.contains("stomach")) var::legit::aimbot::stomach = aimbot["stomach"].get<bool>(); // cast to bool
			if (aimbot.contains("draw_fov")) var::legit::aimbot::draw_fov = aimbot["draw_fov"].get<bool>(); // cast to bool
			if (aimbot.contains("fov_color")) std::copy(aimbot["fov_color"].begin(), aimbot["fov_color"].end(), var::legit::aimbot::fov_color); // read color array
		}

		if (legit.contains("backtrack")) {
			// Backtrack
			nlohmann::json backtrack = legit["backtrack"];

			if (backtrack.contains("enabled")) var::legit::backtrack::enabled = backtrack["enabled"].get<bool>(); // cast to bool
			if (backtrack.contains("keybind")) var::legit::backtrack::keybind = backtrack["keybind"].get<int>(); // cast to int
			if (backtrack.contains("kb_style")) var::legit::backtrack::kb_style = backtrack["kb_style"].get<int>(); // cast to int
			if (backtrack.contains("length")) var::legit::backtrack::length = std::clamp(backtrack["length"].get<int>(), 1, 200); // clamp min and max values
		}

		if (legit.contains("triggerbot")) {
			// Triggerbot
			nlohmann::json triggerbot = legit["triggerbot"];

			if (triggerbot.contains("enabled")) var::legit::triggerbot::enabled = triggerbot["enabled"].get<bool>(); // cast to bool
			if (triggerbot.contains("keybind")) var::legit::triggerbot::keybind = triggerbot["keybind"].get<int>(); // cast to int
			if (triggerbot.contains("kb_style")) var::legit::triggerbot::kb_style = triggerbot["kb_style"].get<int>(); // cast to int
		}

		if (legit.contains("exploit")) {
			// Triggerbot
			nlohmann::json exploit = legit["exploit"];

			if (exploit.contains("enabled")) var::legit::exploit::enabled = exploit["enabled"].get<bool>(); // cast to bool
		}
	}

	if (config.contains("visuals")) {
		// Visuals section
		nlohmann::json visuals = config["visuals"];

		if (visuals.contains("esp")) {
			// Esp
			nlohmann::json esp = visuals["esp"];

			if (esp.contains("enabled")) var::visuals::esp::enabled = esp["enabled"].get<bool>(); // cast to bool
			if (esp.contains("keybind")) var::visuals::esp::keybind = esp["keybind"].get<int>(); // cast to int
			if (esp.contains("kb_style")) var::visuals::esp::kb_style = esp["kb_style"].get<int>(); // cast to int
			if (esp.contains("radar")) var::visuals::esp::radar = esp["radar"].get<bool>(); // cast to bool
			if (esp.contains("name")) {
				// Name
				nlohmann::json name = esp["name"];

				if (name.contains("enabled")) var::visuals::esp::name::enabled = name["enabled"].get<bool>(); // cast to bool
				if (name.contains("color")) std::copy(name["color"].begin(), name["color"].end(), var::visuals::esp::name::color); // read color array
			}
			if (esp.contains("box")) {
				// Box
				nlohmann::json box = esp["box"];

				if (box.contains("enabled")) var::visuals::esp::box::enabled = box["enabled"].get<bool>(); // cast to bool
				if (box.contains("color")) std::copy(box["color"].begin(), box["color"].end(), var::visuals::esp::box::color); // read color array
				if (box.contains("corner")) var::visuals::esp::box::corner = box["corner"].get<bool>(); // cast to bool
				if (box.contains("fill")) var::visuals::esp::box::fill = box["fill"].get<bool>(); // cast to bool
				if (box.contains("fill_color")) std::copy(box["fill_color"].begin(), box["fill_color"].end(), var::visuals::esp::box::fill_color); // read color array
				if (box.contains("fill_color2")) std::copy(box["fill_color2"].begin(), box["fill_color2"].end(), var::visuals::esp::box::fill_color2); // read color array
			}
			if (esp.contains("weapon")) {
				// Weapon
				nlohmann::json weapon = esp["weapon"];

				if (weapon.contains("enabled")) var::visuals::esp::weapon::enabled = weapon["enabled"].get<bool>(); // cast to bool
				if (weapon.contains("color")) std::copy(weapon["color"].begin(), weapon["color"].end(), var::visuals::esp::weapon::color); // read color array
			}
			if (esp.contains("ammo")) {
				// Ammo
				nlohmann::json ammo = esp["ammo"];

				if (ammo.contains("enabled")) var::visuals::esp::ammo::enabled = ammo["enabled"].get<bool>(); // cast to bool
				if (ammo.contains("color")) std::copy(ammo["color"].begin(), ammo["color"].end(), var::visuals::esp::ammo::color); // read color array
				if (ammo.contains("color2")) std::copy(ammo["color2"].begin(), ammo["color2"].end(), var::visuals::esp::ammo::color2); // read color array
			}
			if (esp.contains("health")) {
				// Health
				nlohmann::json health = esp["health"];

				if (health.contains("enabled")) var::visuals::esp::health::enabled = health["enabled"].get<bool>(); // cast to bool
				if (health.contains("override_color")) var::visuals::esp::health::override_color = health["override_color"].get<bool>(); // cast to bool
				if (health.contains("color")) std::copy(health["color"].begin(), health["color"].end(), var::visuals::esp::health::color); // read color array
				if (health.contains("color2")) std::copy(health["color2"].begin(), health["color2"].end(), var::visuals::esp::health::color2); // read color array
			}
			if (esp.contains("flags")) {
				// Flags
				nlohmann::json flags = esp["flags"];

				if (flags.contains("enabled")) var::visuals::esp::flags::enabled = flags["enabled"].get<bool>(); // cast to bool
				if (flags.contains("color")) std::copy(flags["color"].begin(), flags["color"].end(), var::visuals::esp::flags::color); // read color array
				if (flags.contains("color2")) std::copy(flags["color2"].begin(), flags["color2"].end(), var::visuals::esp::flags::color2); // read color array
				if (flags.contains("health")) var::visuals::esp::flags::health = flags["health"].get<bool>(); // cast to bool
				if (flags.contains("armor")) var::visuals::esp::flags::armor = flags["armor"].get<bool>(); // cast to bool
				if (flags.contains("distance")) var::visuals::esp::flags::distance = flags["distance"].get<bool>(); // cast to bool
				if (flags.contains("money")) var::visuals::esp::flags::money = flags["money"].get<bool>(); // cast to bool
				if (flags.contains("flashed")) var::visuals::esp::flags::flashed = flags["flashed"].get<bool>(); // cast to bool
				if (flags.contains("scoped")) var::visuals::esp::flags::scoped = flags["scoped"].get<bool>(); // cast to bool
				if (flags.contains("bomb")) var::visuals::esp::flags::bomb = flags["bomb"].get<bool>(); // cast to bool
				if (flags.contains("defusing")) var::visuals::esp::flags::defusing = flags["defusing"].get<bool>(); // cast to bool
				if (flags.contains("kit")) var::visuals::esp::flags::kit = flags["kit"].get<bool>(); // cast to bool
				if (flags.contains("bot")) var::visuals::esp::flags::bot = flags["bot"].get<bool>(); // cast to bool
			}
			if (esp.contains("snaplines")) {
				// Snaplines
				nlohmann::json snaplines = esp["snaplines"];

				if (snaplines.contains("enabled")) var::visuals::esp::snaplines::enabled = snaplines["enabled"].get<bool>(); // cast to bool
				if (snaplines.contains("color")) std::copy(snaplines["color"].begin(), snaplines["color"].end(), var::visuals::esp::snaplines::color); // read color array
			}
			if (esp.contains("viewangles")) {
				// Viewangles
				nlohmann::json viewangles = esp["viewangles"];

				if (viewangles.contains("enabled")) var::visuals::esp::viewangles::enabled = viewangles["enabled"].get<bool>(); // cast to bool
				if (viewangles.contains("color")) std::copy(viewangles["color"].begin(), viewangles["color"].end(), var::visuals::esp::viewangles::color); // read color array
				if (viewangles.contains("length")) var::visuals::esp::viewangles::length = std::clamp(viewangles["length"].get<int>(), 50, 150); // clamp min and max values
			}
			if (esp.contains("skeleton")) {
				// Skeleton
				nlohmann::json skeleton = esp["skeleton"];

				if (skeleton.contains("enabled")) var::visuals::esp::skeleton::enabled = skeleton["enabled"].get<bool>(); // cast to bool
				if (skeleton.contains("color")) std::copy(skeleton["color"].begin(), skeleton["color"].end(), var::visuals::esp::skeleton::color); // read color array
			}
			if (esp.contains("head")) {
				// Head
				nlohmann::json head = esp["head"];

				if (head.contains("enabled")) var::visuals::esp::head::enabled = head["enabled"].get<bool>(); // cast to bool
				if (head.contains("color")) std::copy(head["color"].begin(), head["color"].end(), var::visuals::esp::head::color); // read color array
			}
			if (esp.contains("dlight")) {
				// Dlight
				nlohmann::json dlight = esp["dlight"];

				if (dlight.contains("enabled")) var::visuals::esp::dlight::enabled = dlight["enabled"].get<bool>(); // cast to bool
				if (dlight.contains("color")) std::copy(dlight["color"].begin(), dlight["color"].end(), var::visuals::esp::dlight::color); // read color array
				if (dlight.contains("radius")) var::visuals::esp::dlight::radius = std::clamp(dlight["radius"].get<int>(), 100, 200); // clamp min and max values
			}
		}

		if (visuals.contains("chams")) {
			// Chams
			nlohmann::json chams = visuals["chams"];

			if (chams.contains("enabled")) var::visuals::chams::enabled = chams["enabled"].get<bool>(); // cast to bool
			if (chams.contains("keybind")) var::visuals::chams::keybind = chams["keybind"].get<int>(); // cast to int
			if (chams.contains("kb_style")) var::visuals::chams::kb_style = chams["kb_style"].get<int>(); // cast to int
			if (chams.contains("model_occlusion")) var::visuals::chams::model_occlusion = chams["model_occlusion"].get<bool>(); // cast to bool
			if (chams.contains("wireframe_overlay")) var::visuals::chams::wireframe_overlay = chams["wireframe_overlay"].get<bool>(); // cast to bool

			if (chams.contains("visible")) {
				// Visible
				nlohmann::json visible = chams["visible"];

				if (visible.contains("enabled")) var::visuals::chams::visible::enabled = visible["enabled"].get<bool>(); // cast to bool
				if (visible.contains("material")) var::visuals::chams::visible::material = visible["material"].get<int>(); // cast to int
				if (visible.contains("color")) std::copy(visible["color"].begin(), visible["color"].end(), var::visuals::chams::visible::color); // read color array
			}
			if (chams.contains("occluded")) {
				// Occluded
				nlohmann::json occluded = chams["occluded"];

				if (occluded.contains("enabled")) var::visuals::chams::occluded::enabled = occluded["enabled"].get<bool>(); // cast to bool
				if (occluded.contains("material")) var::visuals::chams::occluded::material = occluded["material"].get<int>(); // cast to int
				if (occluded.contains("color")) std::copy(occluded["color"].begin(), occluded["color"].end(), var::visuals::chams::occluded::color); // read color array
			}
			if (chams.contains("visible_overlay")) {
				// Visible overlay
				nlohmann::json visible_overlay = chams["visible_overlay"];

				if (visible_overlay.contains("enabled")) var::visuals::chams::visible_overlay::enabled = visible_overlay["enabled"].get<bool>(); // cast to bool
				if (visible_overlay.contains("material")) var::visuals::chams::visible_overlay::material = visible_overlay["material"].get<int>(); // cast to int
				if (visible_overlay.contains("color")) std::copy(visible_overlay["color"].begin(), visible_overlay["color"].end(), var::visuals::chams::visible_overlay::color); // read color array
			}
			if (chams.contains("occluded_overlay")) {
				// Occluded overlay
				nlohmann::json occluded_overlay = chams["occluded_overlay"];

				if (occluded_overlay.contains("enabled")) var::visuals::chams::occluded_overlay::enabled = occluded_overlay["enabled"].get<bool>(); // cast to bool
				if (occluded_overlay.contains("material")) var::visuals::chams::occluded_overlay::material = occluded_overlay["material"].get<int>(); // cast to int
				if (occluded_overlay.contains("color")) std::copy(occluded_overlay["color"].begin(), occluded_overlay["color"].end(), var::visuals::chams::occluded_overlay::color); // read color array
			}
			if (chams.contains("arms")) {
				// Arms
				nlohmann::json arms = chams["arms"];

				if (arms.contains("enabled")) var::visuals::chams::arms::enabled = arms["enabled"].get<bool>(); // cast to bool
				if (arms.contains("occluded")) var::visuals::chams::arms::occluded = arms["occluded"].get<bool>(); // cast to bool
				if (arms.contains("draw_original")) var::visuals::chams::arms::draw_original = arms["draw_original"].get<bool>(); // cast to bool
				if (arms.contains("remove_sleeves")) var::visuals::chams::arms::remove_sleeves = arms["remove_sleeves"].get<bool>(); // cast to bool
				if (arms.contains("material")) var::visuals::chams::arms::material = arms["material"].get<int>(); // cast to int
				if (arms.contains("color")) std::copy(arms["color"].begin(), arms["color"].end(), var::visuals::chams::arms::color); // read color array

				if (arms.contains("overlay")) {
					// Overlay
					nlohmann::json overlay = arms["overlay"];

					if (overlay.contains("enabled")) var::visuals::chams::arms::overlay::enabled = overlay["enabled"].get<bool>(); // cast to bool
					if (overlay.contains("wireframe")) var::visuals::chams::arms::overlay::wireframe = overlay["wireframe"].get<bool>(); // cast to bool
					if (overlay.contains("material")) var::visuals::chams::arms::overlay::material = overlay["material"].get<int>(); // cast to int
					if (overlay.contains("color")) std::copy(overlay["color"].begin(), overlay["color"].end(), var::visuals::chams::arms::overlay::color); // read color array
				}
			}
			if (chams.contains("weapon")) {
				// Weapon
				nlohmann::json weapon = chams["weapon"];

				if (weapon.contains("enabled")) var::visuals::chams::weapon::enabled = weapon["enabled"].get<bool>(); // cast to bool
				if (weapon.contains("occluded")) var::visuals::chams::weapon::occluded = weapon["occluded"].get<bool>(); // cast to bool
				if (weapon.contains("draw_original")) var::visuals::chams::weapon::draw_original = weapon["draw_original"].get<bool>(); // cast to bool
				if (weapon.contains("material")) var::visuals::chams::weapon::material = weapon["material"].get<int>(); // cast to int
				if (weapon.contains("color")) std::copy(weapon["color"].begin(), weapon["color"].end(), var::visuals::chams::weapon::color); // read color array

				if (weapon.contains("overlay")) {
					// Overlay
					nlohmann::json overlay = weapon["overlay"];

					if (overlay.contains("enabled")) var::visuals::chams::weapon::overlay::enabled = overlay["enabled"].get<bool>(); // cast to bool
					if (overlay.contains("wireframe")) var::visuals::chams::weapon::overlay::wireframe = overlay["wireframe"].get<bool>(); // cast to bool
					if (overlay.contains("material")) var::visuals::chams::weapon::overlay::material = overlay["material"].get<int>(); // cast to int
					if (overlay.contains("color")) std::copy(overlay["color"].begin(), overlay["color"].end(), var::visuals::chams::weapon::overlay::color); // read color array
				}
			}
		}

		if (visuals.contains("glow")) {
			// Glow
			nlohmann::json glow = visuals["glow"];

			if (glow.contains("enabled")) var::visuals::glow::enabled = glow["enabled"].get<bool>(); // cast to bool
			if (glow.contains("keybind")) var::visuals::glow::keybind = glow["keybind"].get<int>(); // cast to int
			if (glow.contains("kb_style")) var::visuals::glow::kb_style = glow["kb_style"].get<int>(); // cast to int
			if (glow.contains("player")) var::visuals::glow::player = glow["player"].get<bool>(); // cast to bool
			if (glow.contains("color")) std::copy(glow["color"].begin(), glow["color"].end(), var::visuals::glow::color); // read color array
			if (glow.contains("style")) var::visuals::glow::style = glow["style"].get<int>(); // cast to int
			if (glow.contains("bomb")) var::visuals::glow::bomb = glow["bomb"].get<bool>(); // cast to bool
			if (glow.contains("bomb_color")) std::copy(glow["bomb_color"].begin(), glow["bomb_color"].end(), var::visuals::glow::bomb_color); // read color array
			if (glow.contains("chicken")) var::visuals::glow::chicken = glow["chicken"].get<bool>(); // cast to bool
			if (glow.contains("chicken_color")) std::copy(glow["chicken_color"].begin(), glow["chicken_color"].end(), var::visuals::glow::chicken_color); // read color array
			if (glow.contains("weapon")) var::visuals::glow::weapon = glow["weapon"].get<bool>(); // cast to bool
			if (glow.contains("weapon_color")) std::copy(glow["weapon_color"].begin(), glow["weapon_color"].end(), var::visuals::glow::chicken_color); // read color array
		}

		if (visuals.contains("trail")) {
			// Trail
			nlohmann::json trail = visuals["trail"];

			if (trail.contains("enabled")) var::visuals::trail::enabled = trail["enabled"].get<bool>(); // cast to bool
			if (trail.contains("color")) std::copy(trail["color"].begin(), trail["color"].end(), var::visuals::trail::color); // read color array
			if (trail.contains("life")) var::visuals::trail::life = std::clamp(trail["life"].get<int>(), 1, 5); // clamp min and max values
		}
		if (visuals.contains("local_dlight")) {
			// Local dlight
			nlohmann::json local_dlight = visuals["local_dlight"];

			if (local_dlight.contains("enabled")) var::visuals::local_dlight::enabled = local_dlight["enabled"].get<bool>(); // cast to bool
			if (local_dlight.contains("color")) std::copy(local_dlight["color"].begin(), local_dlight["color"].end(), var::visuals::local_dlight::color); // read color array
			if (local_dlight.contains("radius")) var::visuals::local_dlight::radius = std::clamp(local_dlight["radius"].get<int>(), 100, 200); // clamp min and max values
		}
		if (visuals.contains("bullet_tracers")) {
			// Bullet tracers
			nlohmann::json bullet_tracers = visuals["bullet_tracers"];

			if (bullet_tracers.contains("enabled")) var::visuals::bullet_tracers::enabled = bullet_tracers["enabled"].get<bool>(); // cast to bool
			if (bullet_tracers.contains("color")) std::copy(bullet_tracers["color"].begin(), bullet_tracers["color"].end(), var::visuals::bullet_tracers::color); // read color array
		}
		if (visuals.contains("bullet_impacts")) {
			// Bullet impacts
			nlohmann::json bullet_impacts = visuals["bullet_impacts"];

			if (bullet_impacts.contains("enabled")) var::visuals::bullet_impacts::enabled = bullet_impacts["enabled"].get<bool>(); // cast to bool
			if (bullet_impacts.contains("color")) std::copy(bullet_impacts["color"].begin(), bullet_impacts["color"].end(), var::visuals::bullet_impacts::color); // read color array
		}
		if (visuals.contains("snipercrosshair")) {
			// Sniper crosshair
			nlohmann::json snipercrosshair = visuals["snipercrosshair"];

			if (snipercrosshair.contains("enabled")) var::visuals::snipercrosshair::enabled = snipercrosshair["enabled"].get<bool>(); // cast to bool
			if (snipercrosshair.contains("color")) std::copy(snipercrosshair["color"].begin(), snipercrosshair["color"].end(), var::visuals::snipercrosshair::color); // read color array
		}
		if (visuals.contains("recoilcrosshair")) {
			// Recoil crosshair
			nlohmann::json recoilcrosshair = visuals["recoilcrosshair"];

			if (recoilcrosshair.contains("enabled")) var::visuals::recoilcrosshair::enabled = recoilcrosshair["enabled"].get<bool>(); // cast to bool
			if (recoilcrosshair.contains("color")) std::copy(recoilcrosshair["color"].begin(), recoilcrosshair["color"].end(), var::visuals::recoilcrosshair::color); // read color array
		}
		if (visuals.contains("view")) {
			// View
			nlohmann::json view = visuals["view"];

			if (view.contains("fov")) var::visuals::view::fov = std::clamp(view["fov"].get<int>(), 90, 120); // clamp min and max values
			if (view.contains("model")) var::visuals::view::model = std::clamp(view["model"].get<int>(), 60, 120); // clamp min and max values
			if (view.contains("angle")) var::visuals::view::angle = std::clamp(view["angle"].get<int>(), -180, 180); // clamp min and max values
			if (view.contains("aspect")) var::visuals::view::aspect = std::clamp(view["aspect"].get<float>(), 0.f, 3.f); // clamp min and max values
		}
		if (visuals.contains("motionblur")) {
			// Motion blur
			nlohmann::json motionblur = visuals["fog_changer"];

			if (motionblur.contains("enabled")) var::visuals::motionblur::enabled = motionblur["enabled"].get<bool>(); // cast to bool
			if (motionblur.contains("strength")) var::visuals::motionblur::strength = std::clamp(motionblur["strength"].get<float>(), 1.f, 10.f); // clamp min and max values
		}
		if (visuals.contains("fog_changer")) {
			// Fog changer
			nlohmann::json fog_changer = visuals["fog_changer"];

			if (fog_changer.contains("enabled")) var::visuals::fog_changer::enabled = fog_changer["enabled"].get<bool>(); // cast to bool
			if (fog_changer.contains("color")) std::copy(fog_changer["color"].begin(), fog_changer["color"].end(), var::visuals::fog_changer::color); // read color array
			if (fog_changer.contains("start")) var::visuals::fog_changer::start = std::clamp(fog_changer["start"].get<int>(), 0, 2500); // clamp min and max values
		}
		if (visuals.contains("nightmode")) {
			// Nightmode
			nlohmann::json nightmode = visuals["nightmode"];

			if (nightmode.contains("enabled")) var::visuals::nightmode::enabled = nightmode["enabled"].get<bool>(); // cast to bool
			if (nightmode.contains("color")) std::copy(nightmode["color"].begin(), nightmode["color"].end(), var::visuals::nightmode::color); // read color array
			if (nightmode.contains("brightness")) var::visuals::nightmode::brightness = std::clamp(nightmode["brightness"].get<int>(), 1, 99); // clamp min and max values
		}
		if (visuals.contains("particles")) {
			// Particles
			nlohmann::json particles = visuals["particles"];

			if (particles.contains("enabled")) var::visuals::particles::enabled = particles["enabled"].get<bool>(); // cast to bool
			if (particles.contains("color")) std::copy(particles["color"].begin(), particles["color"].end(), var::visuals::particles::color); // read color array
			if (particles.contains("color2")) std::copy(particles["color2"].begin(), particles["color2"].end(), var::visuals::particles::color2); // read color array
		}
		if (visuals.contains("indicators")) {
			// Indicators
			nlohmann::json indicators = visuals["indicators"];

			if (indicators.contains("enabled")) var::visuals::indicators::enabled = indicators["enabled"].get<bool>(); // cast to bool
			if (indicators.contains("color")) std::copy(indicators["color"].begin(), indicators["color"].end(), var::visuals::indicators::color); // read color array
			if (indicators.contains("color2")) std::copy(indicators["color2"].begin(), indicators["color2"].end(), var::visuals::indicators::color2); // read color array
			if (indicators.contains("velocity")) var::visuals::indicators::velocity = indicators["velocity"].get<bool>(); // cast to bool
			if (indicators.contains("stamina")) var::visuals::indicators::stamina = indicators["stamina"].get<bool>(); // cast to bool
			if (indicators.contains("pre")) var::visuals::indicators::pre = indicators["pre"].get<bool>(); // cast to bool
			if (indicators.contains("loss")) var::visuals::indicators::loss = indicators["loss"].get<bool>(); // cast to bool
			if (indicators.contains("keybinds")) var::visuals::indicators::keybinds = indicators["keybinds"].get<bool>(); // cast to bool
			if (indicators.contains("fade")) var::visuals::indicators::fade = indicators["fade"].get<bool>(); // cast to bool
			if (indicators.contains("font")) var::visuals::indicators::font = indicators["font"].get<int>(); // cast to int
		}
		if (visuals.contains("thirdperson")) {
			// Thirdperson
			nlohmann::json thirdperson = visuals["thirdperson"];

			if (thirdperson.contains("keybind")) var::visuals::thirdperson::keybind = thirdperson["keybind"].get<int>(); // cast to int
			if (thirdperson.contains("kb_style")) var::visuals::thirdperson::kb_style = thirdperson["kb_style"].get<int>(); // cast to int
			if (thirdperson.contains("distance")) var::visuals::thirdperson::distance = std::clamp(thirdperson["distance"].get<int>(), 100, 300); // clamp min and max values
		}
		if (visuals.contains("remove_scope")) {
			// Remove scope
			nlohmann::json remove_scope = visuals["remove_scope"];

			if (remove_scope.contains("enabled")) var::visuals::remove_scope::enabled = remove_scope["enabled"].get<bool>(); // cast to bool
			if (remove_scope.contains("color")) std::copy(remove_scope["color"].begin(), remove_scope["color"].end(), var::visuals::remove_scope::color); // read color array
		}
		if (visuals.contains("sky_changer")) var::visuals::sky_changer = visuals["sky_changer"].get<int>(); // cast to int
		if (visuals.contains("disable_postprocess")) var::visuals::disable_postprocess = visuals["disable_postprocess"].get<bool>(); // cast to bool
		if (visuals.contains("fullbright")) var::visuals::fullbright = visuals["fullbright"].get<bool>(); // cast to bool
		if (visuals.contains("watermark")) var::visuals::watermark = visuals["watermark"].get<bool>(); // cast to bool
		if (visuals.contains("speclist")) var::visuals::speclist = visuals["speclist"].get<bool>(); // cast to bool
		if (visuals.contains("wireframe_smoke")) var::visuals::wireframe_smoke = visuals["wireframe_smoke"].get<bool>(); // cast to bool
		if (visuals.contains("flash_opacity")) var::visuals::flash_opacity = std::clamp(visuals["flash_opacity"].get<int>(), 0, 100); // clamp min and max values
	}

	if (config.contains("misc")) {
		// Misc section
		nlohmann::json misc = config["misc"];

		if (misc.contains("clantag")) var::misc::clantag = misc["clantag"].get<bool>(); // cast to bool
		if (misc.contains("killsay")) var::misc::killsay = misc["killsay"].get<bool>(); // cast to bool
		if (misc.contains("event_logs")) var::misc::event_logs = misc["event_logs"].get<bool>(); // cast to bool
		if (misc.contains("chat_logs")) var::misc::chat_logs = misc["chat_logs"].get<bool>(); // cast to bool
		if (misc.contains("vote_reveal")) var::misc::vote_reveal = misc["vote_reveal"].get<bool>(); // cast to bool
		if (misc.contains("movement_notify")) var::misc::movement_notify = misc["movement_notify"].get<bool>(); // cast to bool
		if (misc.contains("hit_sound")) var::misc::hit_sound = misc["hit_sound"].get<int>(); // cast to int
		if (misc.contains("detection_sound")) var::misc::detection_sound = misc["detection_sound"].get<int>(); // cast to int
		if (misc.contains("autoweapon")) var::misc::autoweapon = misc["autoweapon"].get<bool>(); // cast to bool
		if (misc.contains("autoaccept")) var::misc::autoaccept = misc["autoaccept"].get<bool>(); // cast to bool
		if (misc.contains("rank_reveal")) var::misc::rank_reveal = misc["rank_reveal"].get<bool>(); // cast to bool
		if (misc.contains("unlock_inventory")) var::misc::unlock_inventory = misc["unlock_inventory"].get<bool>(); // cast to bool

		if (misc.contains("doorspammer")) {
			// Doorspammer
			nlohmann::json doorspammer = misc["doorspammer"];

			if (doorspammer.contains("enabled")) var::misc::doorspammer::enabled = doorspammer["enabled"].get<bool>(); // cast to bool
			if (doorspammer.contains("keybind")) var::misc::doorspammer::keybind = doorspammer["keybind"].get<int>(); // cast to int
			if (doorspammer.contains("kb_style")) var::misc::doorspammer::kb_style = doorspammer["kb_style"].get<int>(); // cast to int
		}
		if (misc.contains("effects")) {
			// Effects
			nlohmann::json effects = misc["effects"];

			if (effects.contains("hit_boost")) var::misc::effects::hit_boost = effects["hit_boost"].get<bool>(); // cast to bool
			if (effects.contains("hit_sparks")) var::misc::effects::hit_sparks = effects["hit_sparks"].get<bool>(); // cast to bool
			if (effects.contains("hit_beam")) var::misc::effects::hit_beam = effects["hit_beam"].get<bool>(); // cast to bool
			if (effects.contains("detection_boost")) var::misc::effects::detection_boost = effects["detection_boost"].get<bool>(); // cast to bool
			if (effects.contains("detection_sparks")) var::misc::effects::detection_sparks = effects["detection_sparks"].get<bool>(); // cast to bool
			if (effects.contains("detection_beam")) var::misc::effects::detection_beam = effects["detection_beam"].get<bool>(); // cast to bool
			if (effects.contains("color")) std::copy(effects["color"].begin(), effects["color"].end(), var::misc::effects::color); // read color array
		}
		if (misc.contains("detection_indicator")) {
			// Detection indicator
			nlohmann::json detection_indicator = misc["detection_indicator"];

			if (detection_indicator.contains("enabled")) var::misc::detection_indicator::enabled = detection_indicator["enabled"].get<bool>(); // cast to bool
			if (detection_indicator.contains("color")) std::copy(detection_indicator["color"].begin(), detection_indicator["color"].end(), var::misc::detection_indicator::color); // read color array
		}
		if (misc.contains("knife")) {
			// Knife
			nlohmann::json knife = misc["knife"];

			if (knife.contains("model")) var::misc::knife::model = knife["model"].get<int>(); // cast to int
			if (knife.contains("skin")) var::misc::knife::skin = knife["skin"].get<int>(); // cast to int
			if (knife.contains("custom_color")) var::misc::knife::custom_color = knife["custom_color"].get<bool>(); // cast to bool
			if (knife.contains("color1")) std::copy(knife["color1"].begin(), knife["color1"].end(), var::misc::knife::color1); // read color array
			if (knife.contains("color2")) std::copy(knife["color2"].begin(), knife["color2"].end(), var::misc::knife::color2); // read color array
			if (knife.contains("color3")) std::copy(knife["color3"].begin(), knife["color3"].end(), var::misc::knife::color3); // read color array
			if (knife.contains("color4")) std::copy(knife["color4"].begin(), knife["color4"].end(), var::misc::knife::color4); // read color array
		}
		if (misc.contains("glove")) {
			// Glove
			nlohmann::json glove = misc["glove"];

			if (glove.contains("model")) var::misc::glove::model = glove["model"].get<int>(); // cast to int
			if (glove.contains("skin")) var::misc::glove::skin = glove["skin"].get<int>(); // cast to int
		}
	}

	if (config.contains("movement")) {
		// Movement section
		nlohmann::json movement = config["movement"];

		if (movement.contains("bunnyhop")) {
			// Bunnyhop
			nlohmann::json bunnyhop = movement["bunnyhop"];

			if (bunnyhop.contains("enabled")) var::movement::bunnyhop::enabled = bunnyhop["enabled"].get<bool>(); // cast to bool
			if (bunnyhop.contains("hitchance")) var::movement::bunnyhop::hitchance = std::clamp(bunnyhop["hitchance"].get<int>(), 1, 100); // clamp min and max values
		}
		if (movement.contains("edgebug")) {
			// Edgebug
			nlohmann::json edgebug = movement["edgebug"];

			if (edgebug.contains("enabled")) var::movement::edgebug::enabled = edgebug["enabled"].get<bool>(); // cast to bool
			if (edgebug.contains("keybind")) var::movement::edgebug::keybind = edgebug["keybind"].get<int>(); // cast to int
			if (edgebug.contains("kb_style")) var::movement::edgebug::kb_style = edgebug["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("pixelsurf")) {
			// Pixelsurf
			nlohmann::json pixelsurf = movement["pixelsurf"];

			if (pixelsurf.contains("enabled")) var::movement::pixelsurf::enabled = pixelsurf["enabled"].get<bool>(); // cast to bool
			if (pixelsurf.contains("keybind")) var::movement::pixelsurf::keybind = pixelsurf["keybind"].get<int>(); // cast to int
			if (pixelsurf.contains("kb_style")) var::movement::pixelsurf::kb_style = pixelsurf["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("jumpbug")) {
			// Jumpbug
			nlohmann::json jumpbug = movement["jumpbug"];

			if (jumpbug.contains("enabled")) var::movement::jumpbug::enabled = jumpbug["enabled"].get<bool>(); // cast to bool
			if (jumpbug.contains("keybind")) var::movement::jumpbug::keybind = jumpbug["keybind"].get<int>(); // cast to int
			if (jumpbug.contains("kb_style")) var::movement::jumpbug::kb_style = jumpbug["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("edgejump")) {
			// Edgejump
			nlohmann::json edgejump = movement["edgejump"];

			if (edgejump.contains("enabled")) var::movement::edgejump::enabled = edgejump["enabled"].get<bool>(); // cast to bool
			if (edgejump.contains("keybind")) var::movement::edgejump::keybind = edgejump["keybind"].get<int>(); // cast to int
			if (edgejump.contains("kb_style")) var::movement::edgejump::kb_style = edgejump["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("minijump")) {
			// Mini jump
			nlohmann::json minijump = movement["minijump"];

			if (minijump.contains("enabled")) var::movement::minijump::enabled = minijump["enabled"].get<bool>(); // cast to bool
			if (minijump.contains("keybind")) var::movement::minijump::keybind = minijump["keybind"].get<int>(); // cast to int
			if (minijump.contains("kb_style")) var::movement::minijump::kb_style = minijump["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("longjump")) {
			// Longjump
			nlohmann::json longjump = movement["longjump"];

			if (longjump.contains("enabled")) var::movement::longjump::enabled = longjump["enabled"].get<bool>(); // cast to bool
			if (longjump.contains("keybind")) var::movement::longjump::keybind = longjump["keybind"].get<int>(); // cast to int
			if (longjump.contains("kb_style")) var::movement::longjump::kb_style = longjump["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("ladderglide")) {
			// Ladder glide
			nlohmann::json ladderglide = movement["ladderglide"];

			if (ladderglide.contains("enabled")) var::movement::ladderglide::enabled = ladderglide["enabled"].get<bool>(); // cast to bool
			if (ladderglide.contains("keybind")) var::movement::ladderglide::keybind = ladderglide["keybind"].get<int>(); // cast to int
			if (ladderglide.contains("kb_style")) var::movement::ladderglide::kb_style = ladderglide["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("fakebackwards")) {
			// Ladder glide
			nlohmann::json fakebackwards = movement["fakebackwards"];

			if (fakebackwards.contains("enabled")) var::movement::fakebackwards::enabled = fakebackwards["enabled"].get<bool>(); // cast to bool
			if (fakebackwards.contains("keybind")) var::movement::fakebackwards::keybind = fakebackwards["keybind"].get<int>(); // cast to int
			if (fakebackwards.contains("angle")) var::movement::fakebackwards::angle = fakebackwards["angle"].get<int>(); // cast to int
			if (fakebackwards.contains("kb_style")) var::movement::fakebackwards::kb_style = fakebackwards["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("staminahop")) {
			// stamina hop
			nlohmann::json staminahop = movement["staminahop"];

			if (staminahop.contains("enabled")) var::movement::fakebackwards::enabled = staminahop["enabled"].get<bool>(); // cast to bool
			if (staminahop.contains("keybind")) var::movement::fakebackwards::keybind = staminahop["keybind"].get<int>(); // cast to int
			if (staminahop.contains("angle")) var::movement::fakebackwards::angle = staminahop["angle"].get<int>(); // cast to int
			if (staminahop.contains("kb_style")) var::movement::fakebackwards::kb_style = staminahop["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("blockbot")) {
			// Blockbot
			nlohmann::json blockbot = movement["blockbot"];

			if (blockbot.contains("enabled")) var::movement::blockbot::enabled = blockbot["enabled"].get<bool>(); // cast to bool
			if (blockbot.contains("keybind")) var::movement::blockbot::keybind = blockbot["keybind"].get<int>(); // cast to int
			if (blockbot.contains("kb_style")) var::movement::blockbot::kb_style = blockbot["kb_style"].get<int>(); // cast to int
		}
		if (movement.contains("checkpoint")) {
			// Checkpoint
			nlohmann::json checkpoint = movement["checkpoint"];

			if (checkpoint.contains("enabled")) var::movement::checkpoint::enabled = checkpoint["enabled"].get<bool>(); // cast to bool
			if (checkpoint.contains("keybind")) var::movement::checkpoint::keybind = checkpoint["keybind"].get<int>(); // cast to int
			if (checkpoint.contains("keybind_teleport")) var::movement::checkpoint::keybind_teleport = checkpoint["keybind_teleport"].get<int>(); // cast to int
		}
		if (movement.contains("ticks")) var::movement::ticks = std::clamp(movement["ticks"].get<int>(), 1, 64); // clamp min and max values
		if (movement.contains("lock_factor")) var::movement::lock_factor = std::clamp(movement["lock_factor"].get<float>(), 0.f, 1.f); // clamp min and max values
		if (movement.contains("fastduck")) var::movement::fastduck = movement["fastduck"].get<bool>(); // cast to bool
		if (movement.contains("faststop")) var::movement::faststop = movement["faststop"].get<bool>(); // cast to bool
		if (movement.contains("slidewalk")) var::movement::slidewalk = movement["slidewalk"].get<bool>(); // cast to bool
		if (movement.contains("autoalign")) var::movement::autoalign = movement["autoalign"].get<bool>(); // cast to bool
	}
}

void config::reset() {
	// MENU
	std::fill_n(var::menu::accent, 4, 1.f);
	var::menu::background = false;
	std::fill_n(var::menu::background_color, 4, 0.f);
	var::menu::background_effect = false;
	std::fill_n(var::menu::background_effect_color, 4, 1.f);
	var::menu::keybind = 0x2D;

	// LEGIT
	var::legit::aimbot::enabled = false;
	var::legit::aimbot::keybind = 0x01;
	var::legit::aimbot::kb_style = 2;
	var::legit::aimbot::fov = 2;
	var::legit::aimbot::smooth = 10;
	var::legit::aimbot::rcs = 0;
	var::legit::aimbot::autowall = false;
	var::legit::aimbot::silent = false;
	var::legit::aimbot::head = false;
	var::legit::aimbot::chest = false;
	var::legit::aimbot::stomach = false;
	var::legit::aimbot::draw_fov = false;
	std::fill_n(var::legit::aimbot::fov_color, 4, 1.f);
	var::legit::backtrack::enabled = false;
	var::legit::backtrack::keybind = 0x01;
	var::legit::backtrack::kb_style = 1;
	var::legit::backtrack::length = 200;
	var::legit::triggerbot::enabled = false;
	var::legit::triggerbot::keybind = 0;
	var::legit::triggerbot::kb_style = 2;
	var::legit::exploit::enabled = false;

	// VISUAL
	var::visuals::esp::enabled = false;
	var::visuals::esp::keybind = 0;
	var::visuals::esp::kb_style = 1;
	var::visuals::esp::radar = false;
	var::visuals::esp::name::enabled = false;
	std::fill_n(var::visuals::esp::name::color, 4, 1.f);
	var::visuals::esp::box::enabled = false;
	std::fill_n(var::visuals::esp::box::color, 4, 1.f);
	var::visuals::esp::box::corner = false;
	var::visuals::esp::box::fill = false;
	std::fill_n(var::visuals::esp::box::fill_color, 4, 0.1f);
	std::fill_n(var::visuals::esp::box::fill_color2, 4, 0.1f);
	var::visuals::esp::weapon::enabled = false;
	std::fill_n(var::visuals::esp::weapon::color, 4, 1.f);
	var::visuals::esp::ammo::enabled = false;
	std::fill_n(var::visuals::esp::ammo::color, 4, 1.f);
	std::fill_n(var::visuals::esp::ammo::color2, 4, 1.f);
	var::visuals::esp::health::enabled = false;
	var::visuals::esp::health::override_color = false;
	std::fill_n(var::visuals::esp::health::color, 4, 1.f);
	std::fill_n(var::visuals::esp::health::color2, 4, 1.f);
	var::visuals::esp::flags::enabled = false;
	std::fill_n(var::visuals::esp::flags::color, 4, 1.f);
	std::fill_n(var::visuals::esp::flags::color2, 4, 1.f);
	var::visuals::esp::flags::health = false;
	var::visuals::esp::flags::armor = false;
	var::visuals::esp::flags::distance = false;
	var::visuals::esp::flags::money = false;
	var::visuals::esp::flags::flashed = false;
	var::visuals::esp::flags::scoped = false;
	var::visuals::esp::flags::bomb = false;
	var::visuals::esp::flags::defusing = false;
	var::visuals::esp::flags::kit = false;
	var::visuals::esp::flags::bomb = false;
	var::visuals::esp::snaplines::enabled = false;
	std::fill_n(var::visuals::esp::snaplines::color, 4, 1.f);
	var::visuals::esp::viewangles::enabled = false;
	std::fill_n(var::visuals::esp::viewangles::color, 4, 1.f);
	var::visuals::esp::viewangles::length = 100;
	var::visuals::esp::skeleton::enabled = false;
	std::fill_n(var::visuals::esp::skeleton::color, 4, 1.f);
	var::visuals::esp::head::enabled = false;
	std::fill_n(var::visuals::esp::head::color, 4, 1.f);
	var::visuals::esp::dlight::enabled = false;
	std::fill_n(var::visuals::esp::dlight::color, 4, 1.f);
	var::visuals::esp::dlight::radius = 100;
	var::visuals::chams::enabled = false;
	var::visuals::chams::keybind = 0;
	var::visuals::chams::kb_style = 1;
	var::visuals::chams::model_occlusion = false;
	var::visuals::chams::wireframe_overlay = false;
	var::visuals::chams::visible::enabled = false;
	var::visuals::chams::visible::material = 0;
	std::fill_n(var::visuals::chams::visible::color, 4, 1.f);
	var::visuals::chams::occluded::enabled = false;
	var::visuals::chams::occluded::material = 0;
	std::fill_n(var::visuals::chams::occluded::color, 4, 1.f);
	var::visuals::chams::visible_overlay::enabled = false;
	var::visuals::chams::visible_overlay::material = 0;
	std::fill_n(var::visuals::chams::visible_overlay::color, 4, 1.f);
	var::visuals::chams::occluded_overlay::enabled = false;
	var::visuals::chams::occluded_overlay::material = 0;
	std::fill_n(var::visuals::chams::occluded_overlay::color, 4, 1.f);
	var::visuals::chams::arms::enabled = false;
	var::visuals::chams::arms::occluded = false;
	var::visuals::chams::arms::draw_original = false;
	var::visuals::chams::arms::remove_sleeves = false;
	var::visuals::chams::arms::material = 0;
	std::fill_n(var::visuals::chams::arms::color, 4, 1.f);
	var::visuals::chams::arms::overlay::enabled = false;
	var::visuals::chams::arms::overlay::wireframe = false;
	var::visuals::chams::arms::overlay::material = 0;
	std::fill_n(var::visuals::chams::arms::overlay::color, 4, 1.f);
	var::visuals::chams::weapon::enabled = false;
	var::visuals::chams::weapon::occluded = false;
	var::visuals::chams::weapon::draw_original = false;
	var::visuals::chams::weapon::material = 0;
	std::fill_n(var::visuals::chams::weapon::color, 4, 1.f);
	var::visuals::chams::weapon::overlay::enabled = false;
	var::visuals::chams::weapon::overlay::wireframe = false;
	var::visuals::chams::weapon::overlay::material = 0;
	std::fill_n(var::visuals::chams::weapon::overlay::color, 4, 1.f);
	var::visuals::glow::enabled = false;
	var::visuals::glow::keybind = 0;
	var::visuals::glow::kb_style = 1;
	var::visuals::glow::player = false;
	std::fill_n(var::visuals::glow::color, 4, 1.f);
	var::visuals::glow::style = 0;
	var::visuals::glow::bomb = false;
	std::fill_n(var::visuals::glow::bomb_color, 4, 1.f);
	var::visuals::glow::chicken = false;
	std::fill_n(var::visuals::glow::chicken_color, 4, 1.f);
	var::visuals::glow::weapon = false;
	std::fill_n(var::visuals::glow::weapon_color, 4, 1.f);
	var::visuals::trail::enabled = false;
	std::fill_n(var::visuals::trail::color, 4, 1.f);
	var::visuals::trail::life = 1;
	var::visuals::local_dlight::enabled = false;
	std::fill_n(var::visuals::local_dlight::color, 4, 1.f);
	var::visuals::local_dlight::radius = 1;
	var::visuals::bullet_tracers::enabled = false;
	std::fill_n(var::visuals::bullet_tracers::color, 4, 1.f);
	var::visuals::bullet_impacts::enabled = false;
	std::fill_n(var::visuals::bullet_impacts::color, 4, 1.f);
	var::visuals::snipercrosshair::enabled = false;
	std::fill_n(var::visuals::snipercrosshair::color, 4, 1.f);
	var::visuals::recoilcrosshair::enabled = false;
	std::fill_n(var::visuals::recoilcrosshair::color, 4, 1.f);
	var::visuals::view::fov = 90;
	var::visuals::view::model = 60;
	var::visuals::view::angle = 0;
	var::visuals::view::aspect = 0;
	var::visuals::motionblur::enabled = false;
	var::visuals::motionblur::strength = 1;
	var::visuals::fog_changer::enabled = false;
	std::fill_n(var::visuals::fog_changer::color, 4, 1.f);
	var::visuals::fog_changer::start = 0;
	var::visuals::nightmode::enabled = false;
	std::fill_n(var::visuals::nightmode::color, 4, 1.f);
	var::visuals::nightmode::brightness = 99;
	var::visuals::particles::enabled = false;
	std::fill_n(var::visuals::particles::color, 4, 1.f);
	std::fill_n(var::visuals::particles::color2, 4, 1.f);
	var::visuals::indicators::enabled = false;
	std::fill_n(var::visuals::indicators::color, 4, 1.f);
	std::fill_n(var::visuals::indicators::color2, 4, 1.f);
	var::visuals::indicators::velocity = false;
	var::visuals::indicators::stamina = false;
	var::visuals::indicators::pre = false;
	var::visuals::indicators::loss = false;
	var::visuals::indicators::keybinds = false;
	var::visuals::indicators::fade = false;
	var::visuals::indicators::font = 0;
	var::visuals::thirdperson::keybind = 0;
	var::visuals::thirdperson::kb_style = 3;
	var::visuals::thirdperson::distance = 100;
	var::visuals::remove_scope::enabled = false;
	std::fill_n(var::visuals::remove_scope::color, 4, 1.f);
	var::visuals::sky_changer = 0;
	var::visuals::disable_postprocess = false;
	var::visuals::fullbright = false;
	var::visuals::watermark = false;
	var::visuals::speclist = false;
	var::visuals::wireframe_smoke = false;
	var::visuals::flash_opacity = 100;

	// MISC
	var::misc::clantag = false;
	var::misc::killsay = false;
	var::misc::event_logs = false;
	var::misc::chat_logs = false;
	var::misc::vote_reveal = false;
	var::misc::movement_notify = false;
	var::misc::detection_sound = 0;
	var::misc::hit_sound = 0;
	var::misc::autoweapon = false;
	var::misc::autoaccept = false;
	var::misc::rank_reveal = false;
	var::misc::unlock_inventory = false;
	var::misc::doorspammer::enabled = false;
	var::misc::doorspammer::keybind = 0;
	var::misc::doorspammer::kb_style = 2;
	var::misc::effects::hit_boost = false;
	var::misc::effects::hit_sparks = false;
	var::misc::effects::hit_beam = false;
	var::misc::effects::detection_boost = false;
	var::misc::effects::detection_sparks = false;
	var::misc::effects::detection_beam = false;
	std::fill_n(var::misc::effects::color, 4, 1.f);
	var::misc::detection_indicator::enabled = false;
	std::fill_n(var::misc::detection_indicator::color, 4, 1.f);
	var::misc::knife::model = 0;
	var::misc::knife::skin = 0;
	var::misc::knife::custom_color = false;
	std::fill_n(var::misc::knife::color1, 4, 1.f);
	std::fill_n(var::misc::knife::color2, 4, 1.f);
	std::fill_n(var::misc::knife::color3, 4, 1.f);
	std::fill_n(var::misc::knife::color4, 4, 1.f);
	var::misc::glove::model = 0;
	var::misc::glove::skin = 0;

	// MOVEMENT
	var::movement::bunnyhop::enabled = false;
	var::movement::bunnyhop::hitchance = 100;
	var::movement::edgebug::enabled = false;
	var::movement::edgebug::keybind = 0;
	var::movement::edgebug::kb_style = 2;
	var::movement::pixelsurf::enabled = false;
	var::movement::pixelsurf::keybind = 0;
	var::movement::pixelsurf::kb_style = 2;
	var::movement::jumpbug::enabled = false;
	var::movement::jumpbug::keybind = 0;
	var::movement::jumpbug::kb_style = 2;
	var::movement::edgejump::enabled = false;
	var::movement::edgejump::keybind = 0;
	var::movement::edgejump::kb_style = 2;
	var::movement::minijump::enabled = false;
	var::movement::minijump::keybind = 0;
	var::movement::minijump::kb_style = 2;
	var::movement::longjump::enabled = false;
	var::movement::longjump::keybind = 0;
	var::movement::longjump::kb_style = 2;
	var::movement::ladderglide::enabled = false;
	var::movement::ladderglide::keybind = 0;
	var::movement::ladderglide::kb_style = 2;
	var::movement::fakebackwards::enabled = false;
	var::movement::fakebackwards::keybind = 0;
	var::movement::fakebackwards::angle = 0;
	var::movement::fakebackwards::kb_style = 2;
	var::movement::staminahop::enabled = false;
	var::movement::staminahop::keybind = 0;
	var::movement::staminahop::kb_style = 2;
	var::movement::blockbot::enabled = false;
	var::movement::blockbot::keybind = 0;
	var::movement::blockbot::kb_style = 2;
	var::movement::checkpoint::enabled = false;
	var::movement::checkpoint::keybind = 0;
	var::movement::checkpoint::keybind_teleport = 0;
	var::movement::ticks = 32;
	var::movement::lock_factor = 0.5f;
	var::movement::fastduck = false;
	var::movement::faststop = false;
	var::movement::slidewalk = false;
	var::movement::autoalign = false;
}

void config::load(const std::string name) {
	try {
		nlohmann::json config;
		std::ifstream ifs(path + name);

		std::string encoded((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		std::string decoded = base64_decode(encoded);
		std::stringstream stream(decoded);
		stream >> config;

		varsFromJSON(config);
	} catch (...) {
		config::reset();
	}
}

void config::save(const std::string name) {
	try {
		nlohmann::json config = varsToJSON();
		std::string encoded = base64_encode(config.dump());

		std::cin >> encoded;
		std::ofstream write(path + name);

		write << encoded;
		write.close();
	} catch (const std::exception& e) {
		MessageBoxA(nullptr, std::vformat("an error occurred while trying to save a config: {}", std::make_format_args(e.what())).data(), "fbh", MB_OK);
	}
}

std::string get_clipboard()
{
	try {
		OpenClipboard(nullptr);
		HANDLE hData = GetClipboardData(CF_TEXT);

		char* pszText = static_cast<char*>(GlobalLock(hData));
		std::string text(pszText);
		GlobalUnlock(hData);
		CloseClipboard();

		return text;
	}
	catch (std::exception exception) {
		return "error exporting";
	}
}

void set_clipboard(std::string text) {
	try {
		auto glob = GlobalAlloc(GMEM_FIXED, text.length() + 1);
		memcpy(glob, text.c_str(), text.length());

		OpenClipboard(GetActiveWindow());
		EmptyClipboard();
		SetClipboardData(CF_TEXT, glob);
		CloseClipboard();
	}
	catch (std::exception exception) {
		return;
	}
}

void config::import_cfg() {
	try {
		nlohmann::json config;
		std::string encoded = get_clipboard();
		std::string decoded = base64_decode(encoded);

		std::stringstream stream(decoded);
		stream >> config;
		varsFromJSON(config);
	}
	catch (...) {}
}

void config::export_cfg() {
	try {
		nlohmann::json config = varsToJSON();
		std::string decoded = config.dump();
		std::string encoded = base64_encode(decoded);
		set_clipboard(encoded);
	}
	catch (...) {}
}