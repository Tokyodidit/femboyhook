#include <pch.h>
#include "menu.hpp"

// Variables
const char* glow_style[] = { "default", "pulse", "outline", "outline pulse" };
const char* chams_types[] = { "regular", "flat", "crystal", "pearlescent", "reverse pearlescent", "fog", "damascus", "model" };
const char* chams_overlay_types[] = { "glow", "outline", "metallic", "snow" };
const char* cham_types[] = { "player", "arms", "weapon" };
const char* sky_type[] = { "none", "night", "lunacy", "custom" };
const char* indicator_type[] = { "Default", "Verdana", "Impact", "Tahoma", "Arial"};
static int chams_type = 0;
const char* sounds[] = { "none", "default", "coin", "custom" };
const char* fb_angles[] = { "right", "backwards", "left" };
const char* configs[] = { "one", "two", "three", "four", "five" };
const char* knifes[] = { "default", "bayonet", "m9 bayonet", "karambit", "butterfly", "bowie", "falchion", "flip", "gut", "huntsman", "shadow daggers", "navaja", "stiletto", "talon", "ursus", "nomad", "skeleton", "survival", "paracord", "classic" };
const char* gloves[] = { "default", "blood", "sport", "slick", "leather", "moto", "specialist", "hydra", "fang" };
static int current_config = 0;
std::string cfg = std::to_string(current_config + 1);

void menu::tabs::aim() {
	gui::Checkbox(xorstr("legitbot"), &var::legit::aimbot::enabled);
	if (var::legit::aimbot::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("legitbot bind"), &var::legit::aimbot::keybind, &var::legit::aimbot::kb_style);
		gui::SliderInt(xorstr("fov"), &var::legit::aimbot::fov, 1, 180, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::SliderInt(xorstr("smooth"), &var::legit::aimbot::smooth, 1, 100, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::SliderInt(xorstr("rcs"), &var::legit::aimbot::rcs, 0, 100, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::Checkbox(xorstr("aimlock"), &var::legit::aimbot::aimlock);
		gui::Checkbox(xorstr("autowall"), &var::legit::aimbot::autowall);
		gui::Checkbox(xorstr("silent"), &var::legit::aimbot::silent);
		if (gui::BeginCombo(xorstr("hitboxes"), xorstr("...")))
		{
			gui::Selectable(xorstr("head"), &var::legit::aimbot::head, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("chest"), &var::legit::aimbot::chest, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("stomach"), &var::legit::aimbot::stomach, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::EndCombo();
		}
		gui::Checkbox(xorstr("draw fov"), &var::legit::aimbot::draw_fov);
		if (var::legit::aimbot::draw_fov) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("fov color"), var::legit::aimbot::fov_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
	}
}

void menu::tabs::aim_other() {
	gui::Checkbox(xorstr("backtrack"), &var::legit::backtrack::enabled);
	if (var::legit::backtrack::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("bt bind"), &var::legit::backtrack::keybind, &var::legit::backtrack::kb_style);
		gui::SliderInt(xorstr("bt length"), &var::legit::backtrack::length, 1, 200, xorstr("%d ms"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("triggerbot"), &var::legit::triggerbot::enabled);
	if (var::legit::triggerbot::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("triggerbot bind"), &var::legit::triggerbot::keybind, &var::legit::triggerbot::kb_style);
	}
	gui::Checkbox(xorstr("rng exploit"), &var::legit::exploit::enabled);
}

void menu::tabs::visual() {
	gui::Checkbox(xorstr("watermark"), &var::visuals::watermark);
	gui::Checkbox(xorstr("spectator list"), &var::visuals::speclist);
	gui::Checkbox(xorstr("indicators"), &var::visuals::indicators::enabled);
	if (var::visuals::indicators::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("indicator color"), var::visuals::indicators::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine(0, 3);
		gui::ColorEdit4(xorstr("indicator color2"), var::visuals::indicators::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		if (gui::BeginCombo(xorstr("options"), xorstr("...")))
		{
			gui::Selectable(xorstr("velocity"), &var::visuals::indicators::velocity, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("stamina"), &var::visuals::indicators::stamina, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("pre speed"), &var::visuals::indicators::pre, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("loss"), &var::visuals::indicators::loss, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("keybinds"), &var::visuals::indicators::keybinds, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::Selectable(xorstr("fade"), &var::visuals::indicators::fade, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			gui::EndCombo();
		}
	}
	gui::Combo(xorstr("indicator font"), &var::visuals::indicators::font, indicator_type, IM_ARRAYSIZE(indicator_type));

	gui::Checkbox(xorstr("trail"), &var::visuals::trail::enabled);
	if (var::visuals::trail::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("trail color"), var::visuals::trail::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("trail life"), &var::visuals::trail::life, 1, 5, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("local dlight"), &var::visuals::local_dlight::enabled);
	if (var::visuals::local_dlight::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("dlight color"), var::visuals::local_dlight::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("dlight radius"), &var::visuals::local_dlight::radius, 100, 200, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("bullet tracers"), &var::visuals::bullet_tracers::enabled);
	if (var::visuals::bullet_tracers::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("bullet tracer color"), var::visuals::bullet_tracers::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("bullet impacts"), &var::visuals::bullet_impacts::enabled);
	if (var::visuals::bullet_impacts::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("bullet impact color"), var::visuals::bullet_impacts::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("sniper crosshair"), &var::visuals::snipercrosshair::enabled);
	if (var::visuals::snipercrosshair::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("sniper crosshair color"), var::visuals::snipercrosshair::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("recoil crosshair"), &var::visuals::recoilcrosshair::enabled);
	if (var::visuals::recoilcrosshair::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("recoil crosshair color"), var::visuals::recoilcrosshair::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("remove scope"), &var::visuals::remove_scope::enabled);
	if (var::visuals::remove_scope::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("remove scope color"), var::visuals::remove_scope::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("disable postprocess"), &var::visuals::disable_postprocess);
	gui::Checkbox(xorstr("wireframe smoke"), &var::visuals::wireframe_smoke);
	gui::SliderInt(xorstr("flash opacity"), &var::visuals::flash_opacity, 0, 100, xorstr("%d%%"), ImGuiSliderFlags_NoInput);
}

void menu::tabs::visual_local() {
	gui::Checkbox(xorstr("motion blur"), &var::visuals::motionblur::enabled);
	if (var::visuals::motionblur::enabled) {
		gui::SliderFloat(xorstr("blur strength"), &var::visuals::motionblur::strength, 1.f, 10.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("fog changer"), &var::visuals::fog_changer::enabled);
	if (var::visuals::fog_changer::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("fog color"), var::visuals::fog_changer::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("fog distance"), &var::visuals::fog_changer::start, 0, 2500, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	//gui::Checkbox(xorstr("full bright"), &var::visuals::fullbright);
	gui::Checkbox(xorstr("world modulation"), &var::visuals::nightmode::enabled);
	if (var::visuals::nightmode::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("sky color"), var::visuals::nightmode::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("brightness"), &var::visuals::nightmode::brightness, 1, 99, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("particle modulation"), &var::visuals::particles::enabled);
	if (var::visuals::particles::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("molotov color"), var::visuals::particles::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine(0, 3);
		gui::ColorEdit4(xorstr("smoke color"), var::visuals::particles::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Combo(xorstr("skybox changer"), &var::visuals::sky_changer, sky_type, IM_ARRAYSIZE(sky_type));
	//gui::Text(xorstr("thirdperson"));
	//gui::SameLine();
	//gui::KeyBind(xorstr("thirdperson bind"), &var::visuals::thirdperson::keybind, &var::visuals::thirdperson::kb_style);
	//gui::SliderInt(xorstr("thirdperson distance"), &var::visuals::thirdperson::distance, 100, 300, xorstr("%d"), ImGuiSliderFlags_NoInput);
	gui::SliderInt(xorstr("fov"), &var::visuals::view::fov, 90, 120, xorstr("%d"), ImGuiSliderFlags_NoInput);
	gui::SliderInt(xorstr("viewmodel"), &var::visuals::view::model, 60, 120, xorstr("%d"), ImGuiSliderFlags_NoInput);
	gui::SliderFloat(xorstr("aspect ratio"), &var::visuals::view::aspect, 0.f, 3.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
	gui::SliderInt(xorstr("roll angle"), &var::visuals::view::angle, -180, 180, xorstr("%d"), ImGuiSliderFlags_NoInput);
}

void menu::tabs::esp() {
	gui::Checkbox(xorstr("esp"), &var::visuals::esp::enabled);
	if (var::visuals::esp::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("esp bind"), &var::visuals::esp::keybind, &var::visuals::esp::kb_style);
		gui::Checkbox(xorstr("radar"), &var::visuals::esp::radar);
		gui::Checkbox(xorstr("name"), &var::visuals::esp::name::enabled);
		if (var::visuals::esp::name::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("name color"), var::visuals::esp::name::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("box"), &var::visuals::esp::box::enabled);
		if (var::visuals::esp::box::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("box color"), var::visuals::esp::box::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			gui::Checkbox(xorstr("box corner"), &var::visuals::esp::box::corner);
			gui::Checkbox(xorstr("box fill"), &var::visuals::esp::box::fill);
			if (var::visuals::esp::box::fill) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("fill color"), var::visuals::esp::box::fill_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::SameLine(0, 3);
				gui::ColorEdit4(xorstr("fill color2"), var::visuals::esp::box::fill_color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			}
		}
		gui::Checkbox(xorstr("weapon"), &var::visuals::esp::weapon::enabled);
		if (var::visuals::esp::weapon::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("weapon color"), var::visuals::esp::weapon::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("ammo bar"), &var::visuals::esp::ammo::enabled);
		if (var::visuals::esp::ammo::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("ammo color"), var::visuals::esp::ammo::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			gui::SameLine(0, 3);
			gui::ColorEdit4(xorstr("ammo color2"), var::visuals::esp::ammo::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("health bar"), &var::visuals::esp::health::enabled);
		if (var::visuals::esp::health::enabled) {
			gui::Checkbox(xorstr("override color"), &var::visuals::esp::health::override_color);
			if (var::visuals::esp::health::override_color) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("health color"), var::visuals::esp::health::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::SameLine(0, 3);
				gui::ColorEdit4(xorstr("health color2"), var::visuals::esp::health::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			}
		}
		gui::Checkbox(xorstr("flags"), &var::visuals::esp::flags::enabled);
		if (var::visuals::esp::flags::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("flags color"), var::visuals::esp::flags::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			gui::SameLine(0, 3);
			gui::ColorEdit4(xorstr("flags color2"), var::visuals::esp::flags::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			if (gui::BeginCombo(xorstr("type"), xorstr("...")))
			{
				gui::Selectable(xorstr("health"), &var::visuals::esp::flags::health, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("money"), &var::visuals::esp::flags::money, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("distance"), &var::visuals::esp::flags::distance, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("armor"), &var::visuals::esp::flags::armor, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("flashed"), &var::visuals::esp::flags::flashed, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("scoped"), &var::visuals::esp::flags::scoped, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("bomb"), &var::visuals::esp::flags::bomb, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("defusing"), &var::visuals::esp::flags::defusing, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("kit"), &var::visuals::esp::flags::kit, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::Selectable(xorstr("bot"), &var::visuals::esp::flags::bot, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
				gui::EndCombo();
			}
		}
		gui::Checkbox(xorstr("snap lines"), &var::visuals::esp::snaplines::enabled);
		if (var::visuals::esp::snaplines::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("snap lines color"), var::visuals::esp::snaplines::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("viewangles"), &var::visuals::esp::viewangles::enabled);
		if (var::visuals::esp::viewangles::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("viewangles color"), var::visuals::esp::viewangles::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			gui::SliderInt(xorstr("line length"), &var::visuals::esp::viewangles::length, 50, 150, xorstr("%d"), ImGuiSliderFlags_NoInput);
		}
		gui::Checkbox(xorstr("skeleton"), &var::visuals::esp::skeleton::enabled);
		if (var::visuals::esp::skeleton::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("skeleton color"), var::visuals::esp::skeleton::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("head"), &var::visuals::esp::head::enabled);
		if (var::visuals::esp::head::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("head color"), var::visuals::esp::head::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("dlight"), &var::visuals::esp::dlight::enabled);
		if (var::visuals::esp::dlight::enabled) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("dlight color"), var::visuals::esp::dlight::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
			gui::SliderInt(xorstr("dlight radius"), &var::visuals::esp::dlight::radius, 100, 200, xorstr("%d"), ImGuiSliderFlags_NoInput);
		}
	}
}

void menu::tabs::esp_model() {
	gui::Checkbox(xorstr("chams"), &var::visuals::chams::enabled);
	if (var::visuals::chams::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("chams bind"), &var::visuals::chams::keybind, &var::visuals::chams::kb_style);
		gui::Combo(xorstr("chams type"), &chams_type, cham_types, IM_ARRAYSIZE(cham_types));
		if (chams_type == 0) {
			gui::Checkbox(xorstr("visible chams"), &var::visuals::chams::visible::enabled);
			if (var::visuals::chams::visible::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("visible chams color"), var::visuals::chams::visible::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("visible"), &var::visuals::chams::visible::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("occluded chams"), &var::visuals::chams::occluded::enabled);
			if (var::visuals::chams::occluded::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("occluded chams color"), var::visuals::chams::occluded::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("occluded"), &var::visuals::chams::occluded::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("visible overlay"), &var::visuals::chams::visible_overlay::enabled);
			if (var::visuals::chams::visible_overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("visible overlay color"), var::visuals::chams::visible_overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("visible##overlay"), &var::visuals::chams::visible_overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
			}
			gui::Checkbox(xorstr("occluded overlay"), &var::visuals::chams::occluded_overlay::enabled);
			if (var::visuals::chams::occluded_overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("occluded overlay color"), var::visuals::chams::occluded_overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("occluded##overlay"), &var::visuals::chams::occluded_overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
			}
			if (var::visuals::chams::visible_overlay::enabled || var::visuals::chams::occluded_overlay::enabled)
				gui::Checkbox(xorstr("wireframe overlay"), &var::visuals::chams::wireframe_overlay);
			gui::Checkbox(xorstr("disable model occlusion"), &var::visuals::chams::model_occlusion);
		}
		else if (chams_type == 1) {
			gui::Checkbox(xorstr("arm chams"), &var::visuals::chams::arms::enabled);
			if (var::visuals::chams::arms::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("arm chams color"), var::visuals::chams::arms::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("material"), &var::visuals::chams::arms::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("arm overlay"), &var::visuals::chams::arms::overlay::enabled);
			if (var::visuals::chams::arms::overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("overlay color"), var::visuals::chams::arms::overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("overlay"), &var::visuals::chams::arms::overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
				gui::Checkbox(xorstr("wireframe overlay"), &var::visuals::chams::arms::overlay::wireframe);
			}
			if (var::visuals::chams::arms::enabled || var::visuals::chams::arms::overlay::enabled) {
				gui::Checkbox(xorstr("occluded"), &var::visuals::chams::arms::occluded);
				gui::Checkbox(xorstr("draw original model"), &var::visuals::chams::arms::draw_original);
			}
			gui::Checkbox(xorstr("remove sleeves"), &var::visuals::chams::arms::remove_sleeves);
		}
		else if (chams_type == 2) {
			gui::Checkbox(xorstr("weapon chams"), &var::visuals::chams::weapon::enabled);
			if (var::visuals::chams::weapon::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("weapon chams color"), var::visuals::chams::weapon::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("material"), &var::visuals::chams::weapon::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("weapon overlay"), &var::visuals::chams::weapon::overlay::enabled);
			if (var::visuals::chams::weapon::overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("overlay color"), var::visuals::chams::weapon::overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("overlay"), &var::visuals::chams::weapon::overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
				gui::Checkbox(xorstr("wireframe overlay"), &var::visuals::chams::weapon::overlay::wireframe);
			}
			if (var::visuals::chams::weapon::enabled || var::visuals::chams::weapon::overlay::enabled) {
				gui::Checkbox(xorstr("occluded"), &var::visuals::chams::weapon::occluded);
				gui::Checkbox(xorstr("draw original model"), &var::visuals::chams::weapon::draw_original);
			}
		}
	}
	gui::Checkbox(xorstr("glow"), &var::visuals::glow::enabled);
	if (var::visuals::glow::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("glow bind"), &var::visuals::glow::keybind, &var::visuals::glow::kb_style);
		gui::Checkbox(xorstr("players"), &var::visuals::glow::player);
		if (var::visuals::glow::player) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("players color"), var::visuals::glow::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("bomb"), &var::visuals::glow::bomb);
		if (var::visuals::glow::bomb) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("bomb color"), var::visuals::glow::bomb_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("chickens"), &var::visuals::glow::chicken);
		if (var::visuals::glow::chicken) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("chickens color"), var::visuals::glow::chicken_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Checkbox(xorstr("weapons"), &var::visuals::glow::weapon);
		if (var::visuals::glow::weapon) {
			gui::SameLine();
			gui::ColorEdit4(xorstr("weapons color"), var::visuals::glow::weapon_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		}
		gui::Combo(xorstr("glow style"), &var::visuals::glow::style, glow_style, IM_ARRAYSIZE(glow_style));
	}
}

void menu::tabs::misc() {
	if (gui::BeginCombo(xorstr("event logs"), xorstr("...")))
	{
		gui::Selectable(xorstr("hit logs"), &var::misc::event_logs, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("chat logs"), &var::misc::chat_logs, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("vote reveal"), &var::misc::vote_reveal, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("movement notify"), &var::misc::movement_notify, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::EndCombo();
	}
	gui::Checkbox(xorstr("auto weapons"), &var::misc::autoweapon);
	gui::Checkbox(xorstr("auto accept"), &var::misc::autoaccept);
	gui::Checkbox(xorstr("rank reveal"), &var::misc::rank_reveal);
	gui::Checkbox(xorstr("unlock inventory"), &var::misc::unlock_inventory);
	gui::Checkbox(xorstr("clantag"), &var::misc::clantag);
	gui::Checkbox(xorstr("kill say"), &var::misc::killsay);
	gui::Checkbox(xorstr("use spammer"), &var::misc::doorspammer::enabled);
	if (var::misc::doorspammer::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("door spam bind"), &var::misc::doorspammer::keybind, &var::misc::doorspammer::kb_style);
	}
	if (gui::BeginCombo(xorstr("effects"), xorstr("...")))
	{
		gui::Selectable(xorstr("kill boost"), &var::misc::effects::hit_boost, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("kill sparks"), &var::misc::effects::hit_sparks, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("kill beam"), &var::misc::effects::hit_beam, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("detect boost"), &var::misc::effects::detection_boost, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("detect sparks"), &var::misc::effects::detection_sparks, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::Selectable(xorstr("detect beam"), &var::misc::effects::detection_beam, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
		gui::EndCombo();
	}
	if (var::misc::effects::detection_beam || var::misc::effects::hit_beam) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("beam color"), var::misc::effects::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Combo(xorstr("hit sound"), &var::misc::hit_sound, sounds, IM_ARRAYSIZE(sounds));
	gui::Combo(xorstr("detect sound"), &var::misc::detection_sound, sounds, IM_ARRAYSIZE(sounds));
	gui::Checkbox(xorstr("detection indicator"), &var::misc::detection_indicator::enabled);
	if (var::misc::detection_indicator::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("detect color"), var::misc::detection_indicator::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
}

void menu::tabs::misc_movement() {
	gui::Checkbox(xorstr("bunnyhop"), &var::movement::bunnyhop::enabled);
	if (var::movement::bunnyhop::enabled) {
		gui::SliderInt(xorstr("bhop chance"), &var::movement::bunnyhop::hitchance, 1, 100, xorstr("%d%%"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("edgebug assist"), &var::movement::edgebug::enabled);
	if (var::movement::edgebug::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("eb bind"), &var::movement::edgebug::keybind, &var::movement::edgebug::kb_style);
	}
	gui::Checkbox(xorstr("pixel surf assist"), &var::movement::pixelsurf::enabled);
	if (var::movement::pixelsurf::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("ps bind"), &var::movement::pixelsurf::keybind, &var::movement::pixelsurf::kb_style);
	}
	if (var::movement::edgebug::enabled || var::movement::pixelsurf::enabled) {
		gui::SliderInt(xorstr("assist ticks"), &var::movement::ticks, 1, 64, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::SliderFloat(xorstr("assist lock factor"), &var::movement::lock_factor, 0.f, 1.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("auto align"), &var::movement::autoalign);
	gui::Checkbox(xorstr("jumpbug"), &var::movement::jumpbug::enabled);
	if (var::movement::jumpbug::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("jumpbug bind"), &var::movement::jumpbug::keybind, &var::movement::jumpbug::kb_style);
	}
	gui::Checkbox(xorstr("edge jump"), &var::movement::edgejump::enabled);
	if (var::movement::edgejump::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("edge jump bind"), &var::movement::edgejump::keybind, &var::movement::edgejump::kb_style);
	}
	gui::Checkbox(xorstr("long jump"), &var::movement::longjump::enabled);
	if (var::movement::longjump::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("long jump bind"), &var::movement::longjump::keybind, &var::movement::longjump::kb_style);
	}
	gui::Checkbox(xorstr("mini jump"), &var::movement::minijump::enabled);
	if (var::movement::minijump::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("mini jump bind"), &var::movement::minijump::keybind, &var::movement::minijump::kb_style);
	}
	gui::Checkbox(xorstr("ladder glide"), &var::movement::ladderglide::enabled);
	if (var::movement::ladderglide::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("ladder glide bind"), &var::movement::ladderglide::keybind, &var::movement::ladderglide::kb_style);
	}
	gui::Checkbox(xorstr("stamina hop"), &var::movement::staminahop::enabled);
	if (var::movement::staminahop::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("stamina hop bind"), &var::movement::staminahop::keybind, &var::movement::staminahop::kb_style);
	}
	gui::Checkbox(xorstr("fake backwards"), &var::movement::fakebackwards::enabled);
	if (var::movement::fakebackwards::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("fake backwards bind"), &var::movement::fakebackwards::keybind, &var::movement::fakebackwards::kb_style);
		gui::Combo(xorstr("fake backwards angle"), &var::movement::fakebackwards::angle, fb_angles, IM_ARRAYSIZE(fb_angles));
	}
	gui::Checkbox(xorstr("blockbot"), &var::movement::blockbot::enabled);
	if (var::movement::blockbot::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("blockbot bind"), &var::movement::blockbot::keybind, &var::movement::blockbot::kb_style);
	}
	gui::Checkbox(xorstr("checkpoint"), &var::movement::checkpoint::enabled);
	if (var::movement::checkpoint::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("checkpoint bind"), &var::movement::checkpoint::keybind);
		gui::Text(xorstr("teleport"));
		gui::SameLine();
		gui::KeyBind(xorstr("teleport bind"), &var::movement::checkpoint::keybind_teleport);
	}
	gui::Checkbox(xorstr("fast duck"), &var::movement::fastduck);
	gui::Checkbox(xorstr("fast stop"), &var::movement::faststop);
	gui::Checkbox(xorstr("slide walk"), &var::movement::slidewalk);
}

void menu::tabs::config() {
	gui::Combo(xorstr("config"), &current_config, configs, IM_ARRAYSIZE(configs));
	if (gui::Button(xorstr("load"))) {
		config::reset();
		config::load(configs[current_config]);
		interfaces::clientstate->full_update();
		notify::run(xorstr("loaded config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
	}
	gui::SameLine();
	if (gui::Button(xorstr("save"))) gui::OpenPopup(xorstr("save popup"));
	gui::SameLine();
	if (gui::Button(xorstr("reset"))) {
		config::reset();
		notify::run(xorstr("reset config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
	}
	if (gui::Button(xorstr("import"))) config::import_cfg();
	gui::SameLine();
	if (gui::Button(xorstr("export"))) config::export_cfg();
	if (gui::Button(xorstr("config folder"))) ShellExecuteA(0, xorstr("open"), xorstr("C:\\Users\\Public\\Documents"), NULL, NULL, SW_NORMAL);

	if (gui::BeginPopup(xorstr("save popup"))) {
		if (gui::Button(xorstr("save config"))) {
			gui::CloseCurrentPopup();
			config::save(configs[current_config]);
			notify::run(xorstr("saved config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
		}
		gui::SameLine();
		if (gui::Button(xorstr("cancel"))) { gui::CloseCurrentPopup(); }
		gui::EndPopup();
	}
}

void menu::tabs::config_extra() {
	gui::Text(xorstr("last update: %s"), __DATE__);
	gui::Text(xorstr("menu key"));
	gui::SameLine();
	gui::KeyBind(xorstr("menu bind"), &var::menu::keybind);
	gui::Text(xorstr("menu accent"));
	gui::SameLine();
	gui::ColorEdit4(xorstr("menu accent"), var::menu::accent, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	gui::Checkbox(xorstr("background"), &var::menu::background);
	if (var::menu::background) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("background color"), var::menu::background_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("background effect"), &var::menu::background_effect);
	if (var::menu::background_effect) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("effect color"), var::menu::background_effect_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Combo(xorstr("knife model"), &var::misc::knife::model, knifes, IM_ARRAYSIZE(knifes));
	gui::Combo(xorstr("knife skin"), &var::misc::knife::skin, [](void* data, int idx, const char** out_text) {
		*out_text = parser_skins[idx].name.c_str();
		return true;
		}, nullptr, parser_skins.size(), 10);
	gui::Checkbox(xorstr("knife color"), &var::misc::knife::custom_color);
	if (var::misc::knife::custom_color) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 1"), var::misc::knife::color1, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 2"), var::misc::knife::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 3"), var::misc::knife::color3, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 4"), var::misc::knife::color4, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Combo(xorstr("glove model"), &var::misc::glove::model, gloves, IM_ARRAYSIZE(gloves));
	gui::Combo(xorstr("glove skin"), &var::misc::glove::skin, [](void* data, int idx, const char** out_text) {
		*out_text = parser_gloves[idx].name.c_str();
		return true;
		}, nullptr, parser_gloves.size(), 10);
	//if (gui::Button(xorstr("full update"))) interfaces::clientstate->full_update();
    #ifdef _DEBUG
	if (gui::Button(xorstr("unload cheat"))) gui::OpenPopup(xorstr("unload popup"));
	if (gui::BeginPopup(xorstr("unload popup"))) {
		if (gui::Button(xorstr("unload"))) {
			gui::CloseCurrentPopup();
			var::unload::enabled = true;
		}
		gui::SameLine();
		if (gui::Button(xorstr("cancel"))) { gui::CloseCurrentPopup(); }
		gui::EndPopup();
    
	}
    #endif
}
