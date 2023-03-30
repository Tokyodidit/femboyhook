#pragma once
#include "../../../dependencies/utilities/csgo.hpp"

struct motionblurhistory {
    motionblurhistory() {
        lasttimeupdate = 0.0f;
        previouspitch = 0.0f;
        previousyaw = 0.0f;
        previouspositon = vec3_t{ 0.0f, 0.0f, 0.0f };
        nomotionbluruntil = 0.0f;
    }
    float lasttimeupdate;
    float previouspitch;
    float previousyaw;
    vec3_t previouspositon;
    float nomotionbluruntil;
};

struct box_info {
	float x, y, w, h;
	box_info() = default;
	box_info(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

struct esp_info {
	box_info box;
	int offset = 0;
};