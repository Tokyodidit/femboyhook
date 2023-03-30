#include <pch.h>
#include "skins.hpp"

bool apply_knife_model(attributable_item_t* weapon, const char* model) {
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player) return false;

	auto viewmodel = reinterpret_cast<base_view_model_t*>(interfaces::entity_list->get_client_entity_handle(local_player->view_model()));
	if (!viewmodel) return false;

	auto h_view_model_weapon = viewmodel->weapon();
	if (!h_view_model_weapon) return false;

	auto view_model_weapon = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(h_view_model_weapon));
	if (view_model_weapon != weapon) return false;

	viewmodel->model_index() = interfaces::model_info->get_model_index(model);

	auto world_model_handle = view_model_weapon->world_model_handle();
	if (!world_model_handle) return false;

	const auto world_model = reinterpret_cast<base_view_model_t*>(interfaces::entity_list->get_client_entity_handle(world_model_handle));
	if (!world_model) return false;
	world_model->model_index() = interfaces::model_info->get_model_index(model) + 1;

	return true;
}

bool apply_knife_skin(attributable_item_t* weapon, int item_definition_index, int model_index, int paint_kit) {
	weapon->item_definition_index() = item_definition_index;
	weapon->fallback_paint_kit() = paint_kit;
	weapon->model_index() = model_index;
	weapon->entity_quality() = 3;
	weapon->fallback_wear() = 0.000000001f;

	return true;
}

void features::misc::knife() {
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player) return;

	auto model_bayonet = "models/weapons/v_knife_bayonet.mdl";
	auto model_m9 = "models/weapons/v_knife_m9_bay.mdl";
	auto model_karambit = "models/weapons/v_knife_karam.mdl";
	auto model_butterfly = "models/weapons/v_knife_butterfly.mdl";
	auto model_bowie = "models/weapons/v_knife_survival_bowie.mdl";
	auto model_falchion = "models/weapons/v_knife_falchion_advanced.mdl";
	auto model_flip = "models/weapons/v_knife_flip.mdl";
	auto model_gut = "models/weapons/v_knife_gut.mdl";
	auto model_huntsman = "models/weapons/v_knife_tactical.mdl";
	auto model_shadow_daggers = "models/weapons/v_knife_push.mdl";
	auto model_navaja = "models/weapons/v_knife_gypsy_jackknife.mdl";
	auto model_stiletto = "models/weapons/v_knife_stiletto.mdl";
	auto model_talon = "models/weapons/v_knife_widowmaker.mdl";
	auto model_ursus = "models/weapons/v_knife_ursus.mdl";
	auto model_nomad = "models/weapons/v_knife_outdoor.mdl";
	auto model_skeleton = "models/weapons/v_knife_skeleton.mdl";
	auto model_survival = "models/weapons/v_knife_canis.mdl";
	auto model_paracord = "models/weapons/v_knife_cord.mdl";
	auto model_css = "models/weapons/v_knife_css.mdl";

	auto index_bayonet = interfaces::model_info->get_model_index("models/weapons/v_knife_bayonet.mdl");
	auto index_m9 = interfaces::model_info->get_model_index("models/weapons/v_knife_m9_bay.mdl");
	auto index_karambit = interfaces::model_info->get_model_index("models/weapons/v_knife_karam.mdl");
	auto index_butterfly = interfaces::model_info->get_model_index("models/weapons/v_knife_butterfly.mdl");
	auto index_bowie = interfaces::model_info->get_model_index("models/weapons/v_knife_survival_bowie.mdl");
	auto index_falchion = interfaces::model_info->get_model_index("models/weapons/v_knife_falchion_advanced.mdl");
	auto index_flip = interfaces::model_info->get_model_index("models/weapons/v_knife_flip.mdl");
	auto index_gut = interfaces::model_info->get_model_index("models/weapons/v_knife_gut.mdl");
	auto index_huntsman = interfaces::model_info->get_model_index("models/weapons/v_knife_tactical.mdl");
	auto index_shadow_daggers = interfaces::model_info->get_model_index("models/weapons/v_knife_push.mdl");
	auto index_navaja = interfaces::model_info->get_model_index("models/weapons/v_knife_gypsy_jackknife.mdl");
	auto index_stiletto = interfaces::model_info->get_model_index("models/weapons/v_knife_stiletto.mdl");
	auto index_talon = interfaces::model_info->get_model_index("models/weapons/v_knife_widowmaker.mdl");
	auto index_ursus = interfaces::model_info->get_model_index("models/weapons/v_knife_ursus.mdl");
	auto index_nomad = interfaces::model_info->get_model_index("models/weapons/v_knife_outdoor.mdl");
	auto index_skeleton = interfaces::model_info->get_model_index("models/weapons/v_knife_skeleton.mdl");
	auto index_survival = interfaces::model_info->get_model_index("models/weapons/v_knife_canis.mdl");
	auto index_paracord = interfaces::model_info->get_model_index("models/weapons/v_knife_cord.mdl");
	auto index_css = interfaces::model_info->get_model_index("models/weapons/v_knife_css.mdl");

	auto active_weapon = local_player->active_weapon();
	if (!active_weapon) return;

	static int stored_knife = 0;
	static int stored_skin = 0;
	if (stored_knife != var::misc::knife::model || stored_skin != var::misc::knife::skin || var::unload::enabled) {
		interfaces::clientstate->full_update();
		stored_knife = var::misc::knife::model;
		stored_skin = var::misc::knife::skin;
	}

	if (var::misc::knife::model == 0) return;

	auto my_weapons = local_player->get_weapons();
	for (size_t i = 0; my_weapons[i] != 0xFFFFFFFF; i++) {
		auto weapon = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(my_weapons[i]));
		if (!weapon) return;

		if (active_weapon->client_class()->class_id == class_ids::cknife) {
			switch (stored_knife) {
			case 0:
				break;
			case 1:
				apply_knife_model(weapon, model_bayonet);
				break;
			case 2:
				apply_knife_model(weapon, model_m9);
				break;
			case 3:
				apply_knife_model(weapon, model_karambit);
				break;
			case 4:
				apply_knife_model(weapon, model_butterfly);
				break;
			case 5:
				apply_knife_model(weapon, model_bowie);
				break;
			case 6:
				apply_knife_model(weapon, model_falchion);
				break;
			case 7:
				apply_knife_model(weapon, model_flip);
				break;
			case 8:
				apply_knife_model(weapon, model_gut);
				break;
			case 9:
				apply_knife_model(weapon, model_huntsman);
				break;
			case 10:
				apply_knife_model(weapon, model_shadow_daggers);
				break;
			case 11:
				apply_knife_model(weapon, model_navaja);
				break;
			case 12:
				apply_knife_model(weapon, model_stiletto);
				break;
			case 13:
				apply_knife_model(weapon, model_talon);
				break;
			case 14:
				apply_knife_model(weapon, model_ursus);
				break;
			case 15:
				apply_knife_model(weapon, model_nomad);
				break;
			case 16:
				apply_knife_model(weapon, model_skeleton);
				break;
			case 17:
				apply_knife_model(weapon, model_survival);
				break;
			case 18:
				apply_knife_model(weapon, model_paracord);
				break;
			case 19:
				apply_knife_model(weapon, model_css);
				break;
			}
		}

		if (weapon->client_class()->class_id == class_ids::cknife) {
			switch (stored_knife) {
			case 0:
				break;
			case 1:
				apply_knife_skin(weapon, WEAPON_KNIFE_BAYONET, index_bayonet, parser_skins[var::misc::knife::skin].id);
				break;
			case 2:
				apply_knife_skin(weapon, WEAPON_KNIFE_M9_BAYONET, index_m9, parser_skins[var::misc::knife::skin].id);
				break;
			case 3:
				apply_knife_skin(weapon, WEAPON_KNIFE_KARAMBIT, index_karambit, parser_skins[var::misc::knife::skin].id);
				break;
			case 4:
				apply_knife_skin(weapon, WEAPON_KNIFE_BUTTERFLY, index_butterfly, parser_skins[var::misc::knife::skin].id);
				break;
			case 5:
				apply_knife_skin(weapon, WEAPON_KNIFE_SURVIVAL_BOWIE, index_bowie, parser_skins[var::misc::knife::skin].id);
				break;
			case 6:
				apply_knife_skin(weapon, WEAPON_KNIFE_FALCHION, index_falchion, parser_skins[var::misc::knife::skin].id);
				break;
			case 7:
				apply_knife_skin(weapon, WEAPON_KNIFE_FLIP, index_flip, parser_skins[var::misc::knife::skin].id);
				break;
			case 8:
				apply_knife_skin(weapon, WEAPON_KNIFE_GUT, index_gut, parser_skins[var::misc::knife::skin].id);
				break;
			case 9:
				apply_knife_skin(weapon, WEAPON_KNIFE_TACTICAL, index_huntsman, parser_skins[var::misc::knife::skin].id);
				break;
			case 10:
				apply_knife_skin(weapon, WEAPON_KNIFE_PUSH, index_shadow_daggers, parser_skins[var::misc::knife::skin].id);
				break;
			case 11:
				apply_knife_skin(weapon, WEAPON_KNIFE_GYPSY_JACKKNIFE, index_navaja, parser_skins[var::misc::knife::skin].id);
				break;
			case 12:
				apply_knife_skin(weapon, WEAPON_KNIFE_STILETTO, index_stiletto, parser_skins[var::misc::knife::skin].id);
				break;
			case 13:
				apply_knife_skin(weapon, WEAPON_KNIFE_WIDOWMAKER, index_talon, parser_skins[var::misc::knife::skin].id);
				break;
			case 14:
				apply_knife_skin(weapon, WEAPON_KNIFE_URSUS, index_ursus, parser_skins[var::misc::knife::skin].id);
				break;
			case 15:
				apply_knife_skin(weapon, WEAPON_KNIFE_OUTDOOR, index_nomad, parser_skins[var::misc::knife::skin].id);
				break;
			case 16:
				apply_knife_skin(weapon, WEAPON_KNIFE_SKELETON, index_skeleton, parser_skins[var::misc::knife::skin].id);
				break;
			case 17:
				apply_knife_skin(weapon, WEAPON_KNIFE_CANIS, index_survival, parser_skins[var::misc::knife::skin].id);
				break;
			case 18:
				apply_knife_skin(weapon, WEAPON_KNIFE_CORD, index_paracord, parser_skins[var::misc::knife::skin].id);
				break;
			case 19:
				apply_knife_skin(weapon, WEAPON_KNIFE_CSS, index_css, parser_skins[var::misc::knife::skin].id);
				break;
			}
		}
		weapon->original_owner_xuid_low() = 0;
		weapon->original_owner_xuid_high() = 0;
		weapon->fallback_seed() = 69;
		weapon->item_id_high() = -1;
	}
}

typedef void(*recv_var_proxy_fn)(const c_recv_proxy_data* p_data, void* p_struct, void* p_out);

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12
#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15
#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13
#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12
#define SEQUENCE_BOWIE_IDLE1 1
#define	LIFE_ALIVE 0
#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

recv_var_proxy_fn sequence_proxy_fn = nullptr;
recv_var_proxy_fn recv_model_index;

void hooked_recvproxy_viewmodel(c_recv_proxy_data* p_data, void* p_struct, void* p_out) {
	int index_default_t = interfaces::model_info->get_model_index("models/weapons/v_knife_default_t.mdl");
	int index_default_ct = interfaces::model_info->get_model_index("models/weapons/v_knife_default_ct.mdl");
	int index_bayonet = interfaces::model_info->get_model_index("models/weapons/v_knife_bayonet.mdl");
	int index_m9 = interfaces::model_info->get_model_index("models/weapons/v_knife_m9_bay.mdl");
	int index_karambit = interfaces::model_info->get_model_index("models/weapons/v_knife_karam.mdl");
	int index_butterfly = interfaces::model_info->get_model_index("models/weapons/v_knife_butterfly.mdl");
	int index_bowie = interfaces::model_info->get_model_index("models/weapons/v_knife_survival_bowie.mdl");
	int index_falchion = interfaces::model_info->get_model_index("models/weapons/v_knife_falchion_advanced.mdl");
	int index_flip = interfaces::model_info->get_model_index("models/weapons/v_knife_flip.mdl");
	int index_gut = interfaces::model_info->get_model_index("models/weapons/v_knife_gut.mdl");
	int index_huntsman = interfaces::model_info->get_model_index("models/weapons/v_knife_tactical.mdl");
	int index_shadow_daggers = interfaces::model_info->get_model_index("models/weapons/v_knife_push.mdl");
	int index_navaja = interfaces::model_info->get_model_index("models/weapons/v_knife_gypsy_jackknife.mdl");
	int index_stiletto = interfaces::model_info->get_model_index("models/weapons/v_knife_stiletto.mdl");
	int index_talon = interfaces::model_info->get_model_index("models/weapons/v_knife_widowmaker.mdl");
	int index_ursus = interfaces::model_info->get_model_index("models/weapons/v_knife_ursus.mdl");
	int index_nomad = interfaces::model_info->get_model_index("models/weapons/v_knife_outdoor.mdl");
	int index_skeleton = interfaces::model_info->get_model_index("models/weapons/v_knife_skeleton.mdl");
	int index_survival = interfaces::model_info->get_model_index("models/weapons/v_knife_canis.mdl");
	int index_paracord = interfaces::model_info->get_model_index("models/weapons/v_knife_cord.mdl");
	int index_classic = interfaces::model_info->get_model_index("models/weapons/v_knife_css.mdl");

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (var::misc::knife::model > 0 && (local_player && local_player->is_alive())) {
		if (p_data->value.m_int == index_default_t ||
			p_data->value.m_int == index_default_ct ||
			p_data->value.m_int == index_bayonet ||
			p_data->value.m_int == index_m9 ||
			p_data->value.m_int == index_karambit ||
			p_data->value.m_int == index_butterfly ||
			p_data->value.m_int == index_bowie ||
			p_data->value.m_int == index_falchion ||
			p_data->value.m_int == index_flip ||
			p_data->value.m_int == index_gut ||
			p_data->value.m_int == index_huntsman ||
			p_data->value.m_int == index_shadow_daggers ||
			p_data->value.m_int == index_navaja ||
			p_data->value.m_int == index_stiletto ||
			p_data->value.m_int == index_talon ||
			p_data->value.m_int == index_ursus ||
			p_data->value.m_int == index_nomad ||
			p_data->value.m_int == index_skeleton ||
			p_data->value.m_int == index_survival ||
			p_data->value.m_int == index_paracord ||
			p_data->value.m_int == index_classic) {
			if (var::misc::knife::model == 1)
				p_data->value.m_int = index_bayonet;
			else if (var::misc::knife::model == 2)
				p_data->value.m_int = index_m9;
			else if (var::misc::knife::model == 3)
				p_data->value.m_int = index_karambit;
			else if (var::misc::knife::model == 4)
				p_data->value.m_int = index_butterfly;
			else if (var::misc::knife::model == 5)
				p_data->value.m_int = index_bowie;
			else if (var::misc::knife::model == 6)
				p_data->value.m_int = index_falchion;
			else if (var::misc::knife::model == 7)
				p_data->value.m_int = index_flip;
			else if (var::misc::knife::model == 8)
				p_data->value.m_int = index_gut;
			else if (var::misc::knife::model == 9)
				p_data->value.m_int = index_huntsman;
			else if (var::misc::knife::model == 10)
				p_data->value.m_int = index_shadow_daggers;
			else if (var::misc::knife::model == 11)
				p_data->value.m_int = index_navaja;
			else if (var::misc::knife::model == 12)
				p_data->value.m_int = index_stiletto;
			else if (var::misc::knife::model == 13)
				p_data->value.m_int = index_talon;
			else if (var::misc::knife::model == 14)
				p_data->value.m_int = index_ursus;
			else if (var::misc::knife::model == 15)
				p_data->value.m_int = index_nomad;
			else if (var::misc::knife::model == 16)
				p_data->value.m_int = index_skeleton;
			else if (var::misc::knife::model == 17)
				p_data->value.m_int = index_survival;
			else if (var::misc::knife::model == 18)
				p_data->value.m_int = index_paracord;
			else if (var::misc::knife::model == 19)
				p_data->value.m_int = index_classic;
		}
	}
	recv_model_index(p_data, p_struct, p_out);
}

void set_view_model_sequence(const c_recv_proxy_data* pDataConst, void* p_struct, void* p_out) {
	c_recv_proxy_data* p_data = const_cast<c_recv_proxy_data*>(pDataConst);
	base_view_model_t* player_view_model = static_cast<base_view_model_t*>(p_struct);

	if (player_view_model) {
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
		player_t* p_owner = static_cast<player_t*>(interfaces::entity_list->get_client_entity(player_view_model->owner() & 0xFFF));
		if (p_owner == local_player) {
			std::string sz_model = interfaces::model_info->get_model_name(interfaces::model_info->get_model(player_view_model->model_index()));
			int m_nSequence = p_data->value.m_int;
			if (sz_model == "models/weapons/v_knife_butterfly.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
					break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
					break;
				default:
					m_nSequence++;
				}
			}
			else if (sz_model == "models/weapons/v_knife_falchion_advanced.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
					break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
					break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence--;
				}
			}
			else if (sz_model == "models/weapons/v_knife_push.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
				case SEQUENCE_DEFAULT_LIGHT_MISS1:
				case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
					break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
					break;
				case SEQUENCE_DEFAULT_HEAVY_HIT1:
				case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence += 2;
				}
			}
			else if (sz_model == "models/weapons/v_knife_survival_bowie.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_BOWIE_IDLE1;
					break;
				default:
					m_nSequence--;
				}
			}
			else if (sz_model == "models/weapons/v_knife_ursus.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
					break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
					break;
				default:
					m_nSequence++;
					break;
				}
			}
			else if (sz_model == "models/weapons/v_knife_stiletto.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(12, 13);
					break;
				}
			}
			else if (sz_model == "models/weapons/v_knife_widowmaker.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(14, 15);
					break;
				}
			}
			else if (sz_model == "models/weapons/v_knife_css.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = 15;
					break;
				}
			}
			else if (sz_model == "models/weapons/v_knife_css.mdl") {
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = 15;
					break;
				}
			}
			else if (sz_model == "models/weapons/v_knife_cord.mdl" || sz_model == "models/weapons/v_knife_canis.mdl" || sz_model == "models/weapons/v_knife_outdoor.mdl" || sz_model == "models/weapons/v_knife_skeleton.mdl") {
				switch (m_nSequence)
				{
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
					break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
					break;
				default:
					m_nSequence++;
				}
			}
			p_data->value.m_int = m_nSequence;
		}
	}
	sequence_proxy_fn(p_data, p_struct, p_out);
}

static auto get_wearable_create_fn() -> create_client_class_fn {
	auto client_class = interfaces::client->get_client_classes();

	for (client_class = interfaces::client->get_client_classes();
		client_class; client_class = client_class->next_ptr) {

		if (client_class->class_id == (int)class_ids::ceconwearable) {
			return client_class->create_fn;
		}
	}
}

static auto make_glove(int entry, int serial) -> attributable_item_t* {
	static auto create_wearable_fn = get_wearable_create_fn();
	create_wearable_fn(entry, serial);

	const auto glove = static_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity(entry));
	assert(glove); {
		static auto set_abs_origin_addr = util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
		const auto set_abs_origin_fn = reinterpret_cast<void(__thiscall*)(void*, const std::array<float, 3>&)>(set_abs_origin_addr);
		static constexpr std::array<float, 3> new_pos = { 10000.f, 10000.f, 10000.f };
		set_abs_origin_fn(glove, new_pos);
	}
	return glove;
}

bool apply_glove_model(attributable_item_t* glove, const char* model) noexcept {
	player_info_t info;
	interfaces::engine->get_player_info(interfaces::engine->get_local_player(), &info);
	glove->account_id() = info.xuidlow;
	*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;
	return true;
}

bool apply_glove_skin(attributable_item_t* glove, int item_definition_index, int model_index, int paint_kit) {
	glove->item_definition_index() = item_definition_index;
	glove->fallback_paint_kit() = paint_kit;
	glove->set_model_index(model_index);
	glove->entity_quality() = 3;
	glove->fallback_wear() = 0.000000001f;
	return true;
}

void features::misc::glove() {
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player) return;

	auto model_blood = "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
	auto model_sport = "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
	auto model_slick = "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
	auto model_leath = "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
	auto model_moto = "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
	auto model_speci = "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
	auto model_hydra = "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl";
	auto model_fang = "models/weapons/v_models/arms/anarchist/v_glove_anarchist.mdl";

	auto index_blood = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
	auto index_sport = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
	auto index_slick = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
	auto index_leath = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
	auto index_moto = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
	auto index_speci = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
	auto index_hydra = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
	auto index_fang = interfaces::model_info->get_model_index(("models/weapons/v_models/arms/anarchist/v_glove_anarchist.mdl"));

	uintptr_t* const wearables = local_player->get_wearables();
	if (!wearables) return;

	static uintptr_t glove_handle = uintptr_t(0);
	auto glove = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(wearables[0]));

	static int stored_glove = 0;
	static int stored_skin = 0;
	if (stored_glove != var::misc::glove::model || stored_skin != var::misc::glove::skin) {
		interfaces::clientstate->full_update();
		stored_glove = var::misc::glove::model;
		stored_skin = var::misc::glove::skin;
	}

	if (var::misc::glove::model == 0) return;

	if (!local_player->is_alive() || var::unload::enabled) {
		if (glove) {
			glove->net_set_destroyed_on_recreate_entities();
			glove->net_release();
		}
		return;
	}
	if (!glove)
	{
		const auto our_glove = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(glove_handle));
		if (our_glove)
		{
			wearables[0] = glove_handle;
			glove = our_glove;
		}

		const auto entry = interfaces::entity_list->get_highest_index() + 1;
		const auto serial = rand() % 0x1000;
		glove = make_glove(entry, serial);
		wearables[0] = entry | serial << 16;
		glove_handle = wearables[0];
	}
	if (glove)
	{
		switch (stored_glove) {
		case 0:
			break;
		case 1:
			apply_glove_model(glove, model_blood);
			break;
		case 2:
			apply_glove_model(glove, model_sport);
			break;
		case 3:
			apply_glove_model(glove, model_slick);
			break;
		case 4:
			apply_glove_model(glove, model_leath);
			break;
		case 5:
			apply_glove_model(glove, model_moto);
			break;
		case 6:
			apply_glove_model(glove, model_speci);
			break;
		case 7:
			apply_glove_model(glove, model_hydra);
			break;
		case 8:
			apply_glove_model(glove, model_fang);
			break;
		}

		switch (stored_glove) {
		case 0:
			break;
		case 1:
			apply_glove_skin(glove, GLOVE_STUDDED_BLOODHOUND, index_blood, parser_gloves[var::misc::glove::skin].id);
			break;
		case 2:
			apply_glove_skin(glove, GLOVE_SPORTY, index_sport, parser_gloves[var::misc::glove::skin].id);
			break;
		case 3:
			apply_glove_skin(glove, GLOVE_SLICK, index_slick, parser_gloves[var::misc::glove::skin].id);
			break;
		case 4:
			apply_glove_skin(glove, GLOVE_LEATHER_WRAP, index_leath, parser_gloves[var::misc::glove::skin].id);
			break;
		case 5:
			apply_glove_skin(glove, GLOVE_MOTORCYCLE, index_moto, parser_gloves[var::misc::glove::skin].id);
			break;
		case 6:
			apply_glove_skin(glove, GLOVE_SPECIALIST, index_speci, parser_gloves[var::misc::glove::skin].id);
			break;
		case 7:
			apply_glove_skin(glove, GLOVE_HYDRA, index_hydra, parser_gloves[var::misc::glove::skin].id);
			break;
		case 8:
			apply_glove_skin(glove, GLOVE_STUDDED_BROKENFANG, index_hydra, parser_gloves[var::misc::glove::skin].id);
			break;
		}

		glove->item_id_high() = -1;
		glove->fallback_seed() = 0;
		glove->fallback_stattrak() = -1;
		glove->net_pre_data_update(DATA_UPDATE_CREATED);
	}
}

void features::misc::animation_hook() {
	c_client_class* pClass = interfaces::client->get_client_classes();
	while (pClass)
	{
		const char* pszName = pClass->recvtable_ptr->table_name;
		if (!strcmp(pszName, xorstr("DT_BaseViewModel"))) {
			recv_table* pClassTable = pClass->recvtable_ptr;

			for (int nIndex = 0; nIndex < pClass->recvtable_ptr->props_count; nIndex++) {
				recv_prop* pProp = &(pClass->recvtable_ptr->props[nIndex]);

				if (!pProp || strcmp(pProp->prop_name, xorstr("m_nSequence"))) continue;

				sequence_proxy_fn = (recv_var_proxy_fn)pProp->proxy_fn;

				pProp->proxy_fn = (recv_var_proxy_fn)set_view_model_sequence;
			}
		}

		if (!strcmp(pszName, xorstr("DT_BaseViewModel")))
		{
			for (int i = 0; i < pClass->recvtable_ptr->props_count; i++)
			{
				recv_prop* pProp = &(pClass->recvtable_ptr->props[i]);
				const char* name = pProp->prop_name;

				if (!strcmp(name, xorstr("m_nModelIndex")))
				{
					recv_model_index = (recv_var_proxy_fn)pProp->proxy_fn;
					pProp->proxy_fn = (recv_var_proxy_fn)hooked_recvproxy_viewmodel;
				}
			}
		}
		pClass = pClass->next_ptr;
	}
	printf(xorstr("knife animations initialized\n"));
}

void features::misc::animation_unhook() {
	for (c_client_class* pClass = interfaces::client->get_client_classes(); pClass; pClass = pClass->next_ptr) {
		if (!strcmp(pClass->network_name, xorstr("CBaseViewModel"))) {
			recv_table* pClassTable = pClass->recvtable_ptr;

			for (int nIndex = 0; nIndex < pClassTable->props_count; nIndex++) {
				recv_prop* pProp = &pClassTable->props[nIndex];

				if (!pProp || strcmp(pProp->prop_name, xorstr("m_nSequence"))) continue;

				pProp->proxy_fn = sequence_proxy_fn;

				break;
			}
			break;
		}
	}

	for (c_client_class* pClass = interfaces::client->get_client_classes(); pClass; pClass = pClass->next_ptr) {
		if (!strcmp(pClass->network_name, xorstr("CBaseViewModel"))) {
			recv_table* pClassTable = pClass->recvtable_ptr;

			for (int nIndex = 0; nIndex < pClassTable->props_count; nIndex++) {
				recv_prop* pProp = &pClassTable->props[nIndex];

				if (!pProp || strcmp(pProp->prop_name, xorstr("m_nModelIndex"))) continue;

				pProp->proxy_fn = recv_model_index;

				break;
			}
			break;
		}
	}
}