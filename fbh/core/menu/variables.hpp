#pragma once
#include <string>

namespace var {
	namespace unload {
		inline bool enabled = false;
	}

	namespace menu {
		inline float accent[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
		inline bool background = false;
		inline float background_color[4] = { 0.f, 0.f, 0.f, 0.1f };
		inline bool background_effect = false;
		inline float background_effect_color[4] = { 1.f, 1.f, 1.f, 1.f };
		inline int keybind = 0x2D;
	}

	namespace legit {
		namespace aimbot {
			inline bool enabled = false;
			inline int keybind = 0x01;
			inline int kb_style = 2;
			inline int fov = 2;
			inline int smooth = 20;
			inline int rcs = 1;
			inline bool aimlock = false;
			inline bool autowall = false;
			inline bool silent = false;
			inline bool head = true;
			inline bool chest = false;
			inline bool stomach = false;
			inline bool draw_fov = false;
			inline float fov_color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace backtrack {
			inline bool enabled = false;
			inline int keybind = 0x01;
			inline int kb_style = 1;
			inline int length = 200;
		}
		namespace triggerbot {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace exploit {
			inline bool enabled = false;

		}
	}

	namespace visuals {
		namespace esp {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 1;
			inline bool radar = false;
			namespace name {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace box {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline bool corner = false;
				inline bool fill = false;
				inline float fill_color[4] = { 1.f, 1.f, 1.f, 0.1f };
				inline float fill_color2[4] = { 1.f, 1.f, 1.f, 0.1f };
			}
			namespace weapon {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace ammo {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline float color2[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
			}
			namespace health {
				inline bool enabled = false;
				inline bool override_color = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline float color2[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
			}
			namespace flags {
				inline bool enabled = false;
				inline float color[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
				inline float color2[4] = { 1.f, 1.f, 1.f, 1.f };
				inline bool health = false;
				inline bool armor = false;
				inline bool distance = false;
				inline bool money = false;
				inline bool flashed = false;
				inline bool scoped = false;
				inline bool bomb = false;
				inline bool defusing = false;
				inline bool kit = false;
				inline bool bot = false;
			}
			namespace snaplines {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace viewangles {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline int length = 100;
			}
			namespace skeleton {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace head {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace dlight {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline int radius = 100;
			}
		}

		namespace glow {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 1;
			inline bool player = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int style = 0;
			inline bool bomb = false;
			inline float bomb_color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline bool chicken = false;
			inline float chicken_color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline bool weapon = false;
			inline float weapon_color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace chams {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 1;
			inline bool model_occlusion = false;
			inline bool wireframe_overlay = false;
			namespace visible {
				inline bool enabled = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace occluded {
				inline bool enabled = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace visible_overlay {
				inline bool enabled = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace occluded_overlay {
				inline bool enabled = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			}
			namespace arms {
				inline bool enabled = false;
				inline bool occluded = false;
				inline bool draw_original = false;
				inline bool remove_sleeves = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				namespace overlay {
					inline bool enabled = false;
					inline bool wireframe = false;
					inline int material = 0;
					inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				}
			}
			namespace weapon {
				inline bool enabled = false;
				inline bool occluded = false;
				inline bool draw_original = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				namespace overlay {
					inline bool enabled = false;
					inline bool wireframe = false;
					inline int material = 0;
					inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				}
			}
		}

		namespace trail {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int life = 1;
		}
		namespace local_dlight {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int radius = 100;
		}
		namespace bullet_tracers {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace bullet_impacts {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace snipercrosshair {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace recoilcrosshair {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace view {
			inline int fov = 90;
			inline int angle = 0;
			inline int model = 60;
			inline float aspect = 0.f;
		}
		namespace motionblur {
			inline bool enabled = false;
			inline float strength = 1;
		}
		namespace fog_changer {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int start = 0;
		}
		namespace nightmode {
			inline bool enabled = false;
			inline float color[4] = { 0.1f, 0.1f, 0.1f, 1.f };
			inline int brightness = 99;
		}
		namespace particles {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color2[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace indicators {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color2[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
			inline bool velocity = false;
			inline bool stamina = false;
			inline bool pre = false;
			inline bool loss = false;
			inline bool keybinds = false;
			inline bool fade = false;
			inline int font = 0;
		}
		namespace thirdperson {
			inline int keybind = 0;
			inline int kb_style = 3;
			inline int distance = 100;
		}
		namespace remove_scope {
			inline bool enabled = false;
			inline float color[4] = { 0.f, 0.f, 0.f, 1.f };
		}
		inline int sky_changer = 0;
		inline bool disable_postprocess = false;
		inline bool fullbright = false;
		inline bool watermark = false;
		inline bool speclist = false;
		inline bool wireframe_smoke = false;
		inline int flash_opacity = 100;
	}

	namespace misc {
		inline bool clantag = false;
		inline bool killsay = false;
		inline bool event_logs = false;
		inline bool chat_logs = false;
		inline bool vote_reveal = false;
		inline bool movement_notify = false;
		inline int hit_sound = 0;
		inline int detection_sound = 0;
		inline bool autoweapon = false;
		inline bool autoaccept = false;
		inline bool rank_reveal = false;
		inline bool unlock_inventory = false;
		namespace doorspammer {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace effects {
			inline bool hit_boost = false;
			inline bool hit_sparks = false;
			inline bool hit_beam = false;
			inline bool detection_boost = false;
			inline bool detection_sparks = false;
			inline bool detection_beam = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace detection_indicator {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace knife {
			inline int model = 0;
			inline int skin = 0;
			inline bool custom_color = false;
			inline float color1[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color2[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color3[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color4[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace glove {
			inline int model = 0;
			inline int skin = 0;
		}
	}

	namespace movement {
		namespace bunnyhop {
			inline bool enabled = false;
			inline int hitchance = 100;
		}
		namespace edgebug {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace pixelsurf {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace jumpbug {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace edgejump {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace minijump {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace longjump {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace ladderglide {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace staminahop {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace fakebackwards {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int angle = 0;
			inline int kb_style = 2;
		}
		namespace blockbot {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		namespace checkpoint {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int keybind_teleport = 0;
		}
		inline int ticks = 32;
		inline float lock_factor = 0.5f;
		inline bool fastduck = false;
		inline bool faststop = false;
		inline bool slidewalk = false;
		inline bool autoalign = false;
	}
}