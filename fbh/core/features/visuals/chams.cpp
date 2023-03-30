#include <pch.h>
#include "../features.hpp"

i_material* mat_regular;
i_material* mat_flat;
i_material* mat_crystal;
i_material* mat_pearlescent;
i_material* mat_reverse_pearlescent;
i_material* mat_fog;
i_material* mat_damascus;
i_material* mat_model;
i_material* mat_overlay_glow;
i_material* mat_overlay_outline;
i_material* mat_overlay_metallic;
i_material* mat_overlay_snow;

i_material* create_material(std::string name, std::string type, std::string material) {
	auto kv = static_cast<c_key_values*>(malloc(36));
	kv->init(type.c_str());
	kv->load_from_buffer(name.c_str(), material.c_str());
	return interfaces::material_system->create_material(name.c_str(), kv);
}

void override_material(bool ignorez, bool wireframe, int type, color clr) {
	i_material* material = nullptr;

	// Set material
	switch (type) {
		case 0: material = mat_regular; break;
		case 1: material = mat_flat; break;
		case 2: material = mat_crystal; break;
		case 3: material = mat_pearlescent; break;
		case 4: material = mat_reverse_pearlescent; break;
		case 5: material = mat_fog; break;
		case 6: material = mat_damascus; break;
		case 7: material = mat_model; break;
	}

	// Material flags
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);

	// Color modulate
	material->color_modulate(clr.r / 255.0f, clr.g / 255.0f, clr.b / 255.0f);
	material->alpha_modulate(clr.a / 255.0f);
	interfaces::model_render->override_material(material);
}

void override_overlay_material(bool ignorez, bool wireframe, int type, color clr) {
	i_material* material = nullptr;

	// Set material
	switch (type) {
		case 0: material = mat_overlay_glow; break;
		case 1: material = mat_overlay_outline; break;
		case 2: material = mat_overlay_metallic; break;
		case 3: material = mat_overlay_snow; break;
	}

	// Material flags
	material->set_material_var_flag(material_var_ignorez, ignorez);
	material->set_material_var_flag(material_var_wireframe, wireframe);

	// Overlay color
	auto overlay = material->find_var(xorstr("$envmaptint"), nullptr);
	overlay->SetVector(clr.r / 255.0f, clr.g / 255.0f, clr.b / 255.0f);

	// Color modulate
	material->color_modulate(clr.r / 255.0f, clr.g / 255.0f, clr.b / 255.0f);
	material->alpha_modulate(clr.a / 255.0f);
	interfaces::model_render->override_material(material);
}

void features::visuals::chams::initialize() {
	// Regular
	mat_regular = interfaces::material_system->find_material(xorstr("debug/debugambientcube"), TEXTURE_GROUP_MODEL);
	mat_regular->increment_reference_count();

	// Flat
	mat_flat = interfaces::material_system->find_material(xorstr("debug/debugdrawflat"), TEXTURE_GROUP_MODEL);
	mat_flat->increment_reference_count();

	// Glow outline
	mat_overlay_outline = interfaces::material_system->find_material(xorstr("dev/glow_armsrace"), TEXTURE_GROUP_MODEL);
	mat_overlay_outline->increment_reference_count();

	// Pearlescent 
	mat_pearlescent = create_material(xorstr("pearlescent.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$model" "1"
	"$phong" "1"
	"$pearlescent" "1"
	"$basemapalphaphongmask" "1" })#"));

	// Reverse pearlescent
	mat_reverse_pearlescent = create_material(xorstr("pearlescent.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$model" "1"
	"$phong" "1"
	"$pearlescent" "-1"
	"$basemapalphaphongmask" "1" })#"));

	// Crystal 
	mat_crystal = create_material(xorstr("crystal.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$bumpmap" "models/weapons/customization/materials/origamil_camo"
	"$model" "1" })#"));

	// Esoterik glow
	mat_overlay_glow = create_material(xorstr("glow.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$additive" "1"
	"$envmap" "models/effects/cube_white"
	"$envmaptint" "[1 1 1]"
	"$envmapfresnel" "1" })#"));

	// Metallic
	mat_overlay_metallic = create_material(xorstr("metallic.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$additive" "1"
	"$envmap" "env_cubemap"
	"$envmaptint" "[1 1 1]"
	"$envmapfresnel" "1" })#"));

	// Animated fog
	mat_fog = create_material(xorstr("fog.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$basetexture" "dev/zone_warning"
 	"$model" "1"
    Proxies {
		TextureScroll {
			"texturescrollvar" "$baseTextureTransform"
			"texturescrollrate" "0.10"
			"texturescrollangle" "90"
        }
    } })#"));

	// Animated snow
	mat_overlay_snow = create_material(xorstr("snow.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
    "$basetexture" "dev/snowfield"
	"$additive" "1"
    Proxies {
		TextureScroll {
			"texturescrollvar" "$baseTextureTransform"
            "texturescrollrate" "0.10"
            "texturescrollangle" "90"
        }
    } })#"));

	// Animated damascus
	mat_damascus = create_material(xorstr("damascus.vmt"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
	"$basetexture" "models\weapons\customization\paints\antiqued\damascus"
 	"$model" "1"
    Proxies {
		TextureScroll {
			"texturescrollvar" "$baseTextureTransform"
			"texturescrollrate" "0.10"
			"texturescrollangle" "90"
        }
    } })#"));

	// Model 
	mat_model = create_material(xorstr("model.vmt"), xorstr("Modulate"), xorstr(R"#("Modulate" {
	"$basetexture" "vgui/white_additive"
	"$model" "1" })#"));

	console::log(xorstr("cham materials initialized\n"));
}

void features::visuals::chams::run(void* thisptr, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix, hooks::draw_model_execute::fn orig) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Models
	const model_t* model = info.model;
	bool is_nuke = strstr(model->name, xorstr("nuke_cargo_elevator_arms")) != nullptr;
	bool is_arm = strstr(model->name, xorstr("arms")) != nullptr && !is_nuke;
	bool is_weapon = strstr(model->name, xorstr("weapons/v_")) != nullptr && !is_arm;
	bool is_player = strstr(model->name, xorstr("models/player")) != nullptr;
	bool is_sleeve = strstr(model->name, xorstr("sleeve")) != nullptr;
	auto ent = interfaces::entity_list->get_client_entity(info.entity_index);

	// Render player chams
	if (is_player && util::bind(var::visuals::chams::keybind, var::visuals::chams::kb_style)) {
		// Cast entity to player
		player_t* player = reinterpret_cast<player_t*>(ent);

		// Check for player
		if (!player || !player->is_alive() || player->dormant() || player == csgo::local_player || player->team() == csgo::local_player->team()) return;

		if (var::visuals::chams::occluded::enabled) {
			// Render occluded chams
			override_material(true, false, var::visuals::chams::occluded::material, color(var::visuals::chams::occluded::color));
			orig(thisptr, edx, ctx, state, info, matrix);
		}
		if (var::visuals::chams::occluded_overlay::enabled) {
			// Render occluded overlay chams
			override_overlay_material(true, var::visuals::chams::wireframe_overlay, var::visuals::chams::occluded_overlay::material, color(var::visuals::chams::occluded_overlay::color));
			orig(thisptr, edx, ctx, state, info, matrix);
		}
		interfaces::model_render->override_material(nullptr);

		if (var::visuals::chams::visible::enabled) {
			// Render visible chams
			orig(thisptr, edx, ctx, state, info, matrix);
			override_material(false, false, var::visuals::chams::visible::material, color(var::visuals::chams::visible::color));
		}
		if (var::visuals::chams::visible_overlay::enabled) {
			// Render visible overlay chams
			orig(thisptr, edx, ctx, state, info, matrix);
			override_overlay_material(false, var::visuals::chams::wireframe_overlay, var::visuals::chams::visible_overlay::material, color(var::visuals::chams::visible_overlay::color));
		}
	}
	else if (is_arm) {
		// Render arm chams
		if (var::visuals::chams::arms::enabled) {
			if (var::visuals::chams::arms::draw_original) orig(thisptr, edx, ctx, state, info, matrix);
			override_material(var::visuals::chams::arms::occluded, false, var::visuals::chams::arms::material, color(var::visuals::chams::arms::color));
		}

		// Render arm overlay
		if (var::visuals::chams::arms::overlay::enabled) {
			if (var::visuals::chams::arms::draw_original || var::visuals::chams::arms::enabled) orig(thisptr, edx, ctx, state, info, matrix);
			override_overlay_material(var::visuals::chams::arms::occluded, var::visuals::chams::arms::overlay::wireframe, var::visuals::chams::arms::overlay::material, color(var::visuals::chams::arms::overlay::color));
		}
	}
	else if (is_weapon) {
		// Render weapon chams
		if (var::visuals::chams::weapon::enabled) {
			if (var::visuals::chams::weapon::draw_original) orig(thisptr, edx, ctx, state, info, matrix);
			override_material(var::visuals::chams::weapon::occluded, false, var::visuals::chams::weapon::material, color(var::visuals::chams::weapon::color));
		}

		// Render weapon overlay
		if (var::visuals::chams::weapon::overlay::enabled) {
			if (var::visuals::chams::weapon::draw_original || var::visuals::chams::weapon::enabled) orig(thisptr, edx, ctx, state, info, matrix);
			override_overlay_material(var::visuals::chams::weapon::occluded, var::visuals::chams::weapon::overlay::wireframe, var::visuals::chams::weapon::overlay::material, color(var::visuals::chams::weapon::overlay::color));
		}
	}
}
