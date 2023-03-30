#include <pch.h>
#include "../features.hpp"

static float motionblurvalues[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
void features::visuals::motionblur_render(view_setup_t* setup) {
    // Sanity checks
    if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

    float fallingmin = 10.f;
    float fallingmax = 10.f;
    float rotationintensity = 0.15f;
    float fallingintensity = 1.0f;
    float rollintensity = 0.3f;

    static motionblurhistory history;
    if (setup) {
        float timeelapsed = interfaces::globals->realtime - history.lasttimeupdate;
        float currentpitch = setup->angles.x;
        while (currentpitch > 180.0f)
            currentpitch -= 360.0f;
        while (currentpitch < -180.0f)
            currentpitch += 360.0f;

        float currentyaw = setup->angles.y;
        while (currentyaw > 180.0f)
            currentyaw -= 360.0f;
        while (currentyaw < -180.0f)
            currentyaw += 360.0f;

        vec3_t currentforward;
        vec3_t currentside;
        vec3_t currentup;
        math::angle_vectors(setup->angles, &currentforward, &currentside, &currentup);

        vec3_t currentposition = setup->origin;
        vec3_t positionchange = history.previouspositon - currentposition;
        if (positionchange.length() > 30.0f && timeelapsed >= 0.5f) {
            motionblurvalues[0] = 0.0f;
            motionblurvalues[1] = 0.0f;
            motionblurvalues[2] = 0.0f;
            motionblurvalues[3] = 0.0f;
        }
        else if (timeelapsed > (1.0f / 15.0f)) {
            motionblurvalues[0] = 0.0f;
            motionblurvalues[1] = 0.0f;
            motionblurvalues[2] = 0.0f;
            motionblurvalues[3] = 0.0f;
        }
        else if (positionchange.length() > 50.0f) {
            history.nomotionbluruntil = interfaces::globals->realtime + 1.0f;
        }
        else {
            float horizontalfov = setup->fov;
            float verticalfov = setup->aspectratio <= 0.0f ? setup->fov : setup->fov / setup->aspectratio;
            float viewmotion = currentforward.dot(positionchange);

            float sidemotion = currentside.dot(positionchange);
            float yawdifforiginal = history.previousyaw - currentyaw;
            if (((history.previousyaw - currentyaw > 180.0f) || (history.previousyaw - currentyaw < -180.0f)) && ((history.previousyaw + currentyaw > -180.0f) && (history.previousyaw + currentyaw < 180.0f)))
                yawdifforiginal = history.previousyaw + currentyaw;

            float yawdiffadjusted = yawdifforiginal + (sidemotion / 3.0f);
            if (yawdifforiginal < 0.0f)
                yawdiffadjusted = std::clamp(yawdiffadjusted, yawdifforiginal, 0.0f);
            else
                yawdiffadjusted = std::clamp(yawdiffadjusted, 0.0f, yawdifforiginal);

            float undampenedyaw = yawdiffadjusted / horizontalfov;
            motionblurvalues[0] = undampenedyaw * (1.0f - (fabsf(currentpitch) / 90.0f));

            float pitchcompensate = 1.0f - ((1.0f - fabsf(currentforward[2])) * (1.0f - fabsf(currentforward[2])));
            float pitchdifforiginal = history.previouspitch - currentpitch;
            float pitchdiffadjusted = pitchdifforiginal;
            if (currentpitch > 0.0f)
                pitchdiffadjusted = pitchdifforiginal - ((viewmotion / 2.0f) * pitchcompensate);
            else
                pitchdiffadjusted = pitchdifforiginal + ((viewmotion / 2.0f) * pitchcompensate);

            if (pitchdifforiginal < 0.0f)
                pitchdiffadjusted = std::clamp(pitchdiffadjusted, pitchdifforiginal, 0.0f);
            else
                pitchdiffadjusted = std::clamp(pitchdiffadjusted, 0.0f, pitchdifforiginal);

            motionblurvalues[1] = pitchdiffadjusted / verticalfov;
            motionblurvalues[3] = undampenedyaw;
            motionblurvalues[3] *= (fabs(currentpitch) / 90.0f) * (fabs(currentpitch) / 90.0f) * (fabs(currentpitch) / 90.0f);

            if (timeelapsed > 0.0f)
                motionblurvalues[2] /= timeelapsed * 30.0f;
            else
                motionblurvalues[2] = 0.0f;

            motionblurvalues[2] = std::clamp((fabsf(motionblurvalues[2]) - fallingmin) / (fallingmax - fallingmin), 0.0f, 1.0f) * (motionblurvalues[2] >= 0.0f ? 1.0f : -1.0f);
            motionblurvalues[2] /= 30.f;
            motionblurvalues[0] *= rotationintensity * var::visuals::motionblur::strength;
            motionblurvalues[1] *= rotationintensity * var::visuals::motionblur::strength;
            motionblurvalues[2] *= fallingintensity * var::visuals::motionblur::strength;
            motionblurvalues[3] *= rollintensity * var::visuals::motionblur::strength;

        }

        if (interfaces::globals->realtime < history.nomotionbluruntil) {
            motionblurvalues[0] = 0.0f;
            motionblurvalues[1] = 0.0f;
            motionblurvalues[3] = 0.0f;
        }
        else {
            history.nomotionbluruntil = 0.0f;
        }

        history.previouspositon = currentposition;
        history.previouspitch = currentpitch;
        history.previousyaw = currentyaw;
        history.lasttimeupdate = interfaces::globals->realtime;
        return;
    }
}

void draw_screen_effect(i_material* material) { 
    // Get screen size
    int w, h;
    interfaces::engine->get_screen_size(w, h);

    static auto fn = util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 E4 ? 83 EC ? 53 56 57 8D 44 24 ? 89 4C 24 ?"));
    _asm {
        push h
        push w
        push 0
        xor edx, edx
        mov ecx, material
        call fn
        add esp, 12
    }
}

void features::visuals::motionblur_run() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

    auto material = interfaces::material_system->find_material(xorstr("dev/motion_blur"), xorstr("RenderTargets"), false);
    auto motionblurinternal = material->find_var(xorstr("$MotionBlurInternal"), nullptr, false);
    auto motionblurviewport = material->find_var(xorstr("$MotionBlurViewportInternal"), nullptr, false);

    motionblurinternal->SetVectorComponent(motionblurvalues[0], 0);
    motionblurinternal->SetVectorComponent(motionblurvalues[1], 1);
    motionblurinternal->SetVectorComponent(motionblurvalues[2], 2);
    motionblurinternal->SetVectorComponent(motionblurvalues[3], 3);

    motionblurviewport->SetVectorComponent(0.0f, 0);
    motionblurviewport->SetVectorComponent(0.0f, 1);
    motionblurviewport->SetVectorComponent(1.0f, 2);
    motionblurviewport->SetVectorComponent(1.0f, 3);

    draw_screen_effect(material);
}