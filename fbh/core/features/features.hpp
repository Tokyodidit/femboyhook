#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/menu.hpp"
#include "../menu/variables.hpp"
#include "visuals/esp.hpp"
#include "prediction/engine_prediction.hpp"
#include "events/events.hpp"
#include "legit/legit.hpp"
#include "skins/skins.hpp"

namespace features {
	namespace legit {
		namespace aimbot {
			inline bool has_target = false;
			void run(c_usercmd* cmd);
			void draw_fov();
		}
		namespace backtrack {
			void initialize();
			void run(c_usercmd* cmd);
			void update();
		}
		namespace triggerbot {
			void run(c_usercmd* cmd);
		}
		namespace autowall {
			bool run(player_t* local_player, entity_t* entity, vec3_t& destination, weapon_info_t* weapon_data);
		}
	}

	namespace visuals {
		namespace esp {
			void run();
			void name(player_t* player, esp_info& info);
			void bounding_box(player_t* player, esp_info& info);
			void weapon(player_t* player, esp_info& info);
			void ammo(player_t* player, esp_info& info);
			void health(player_t* player, esp_info& info);
			void flags(player_t* player, esp_info& info);
			void snaplines(player_t* player, esp_info& info);
			void viewangles(player_t* player);
			void skeleton(player_t* player);
			void head(player_t* player);
			void dlight(player_t* player);
			bool get_box(player_t* player, box_info& b);
		}
		namespace glow {
			void run();
		}
		namespace chams {
			void run(void* thisptr, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix, hooks::draw_model_execute::fn orig);
			void initialize();
		}

		void motionblur_render(view_setup_t* setup);
		void motionblur_run();
		void speclist();
		void skybox();
		void local_dlight();
		void trail();
		void watermark();
		void flash_opacity();
		void wireframe_smoke();
		void disable_postprocess();
		void remove_scope();
		void sniper_crosshair();
		void recoil_crosshair();
		void indicators();
	}

	namespace misc {
		void clantag();
		void auto_weapon(c_usercmd* cmd);
		void rank_reveal(c_usercmd* cmd);
		void door_spammer(c_usercmd* cmd);
		void knife();
		void glove();
		void animation_hook();
		void animation_unhook();
	}

	namespace movement {
		void bunnyhop(c_usercmd* cmd);
		void fast_duck(c_usercmd* cmd);
		void fast_stop(c_usercmd* cmd);
		void slide_walk(c_usercmd* cmd);
		void longjump(c_usercmd* cmd);
		void ladderglide(c_usercmd* cmd);
		void staminahop(c_usercmd* cmd);
		void fakebackwards(c_usercmd* cmd);
		void fakebackwards_render();
		void autoalign(c_usercmd* cmd);
		void blockbot(c_usercmd* cmd);
		void jumpbug(c_usercmd* cmd, int pre_flags);
		void edgejump(c_usercmd* cmd, int pre_flags);
		void minijump(c_usercmd* cmd, int pre_flags);
		void checkpoint();

		namespace edgebug {
			void run(c_usercmd* cmd);
			void lock(c_usercmd* cmd);
			bool is_detected();
			void draw();
		}
		namespace pixelsurf {
			void run(c_usercmd* cmd);
			void lock(c_usercmd* cmd);
			bool is_detected();
			void draw();
		}
	}

	namespace discord {
		void initialize();
		void release();
	}
}