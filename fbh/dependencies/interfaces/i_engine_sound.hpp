#pragma once
#include <cstdint>
#include "../../source-sdk/classes/convar.hpp"
#include "../../source-sdk/math/vector3d.hpp"
#include "../../source-sdk/math/vector2d.hpp"
#include "../../source-sdk/math/view_matrix.hpp"
#include "../../source-sdk/classes/net_channel.hpp"
#include "../../dependencies/utilities/utilities.hpp"

struct sound_info_t {
	int m_nGuid;
	void* m_filenameHandle;
	int m_nSoundSource;
	int m_nChannel;
	int m_nSpeakerEntity;
	float m_flVolume;
	float m_flLastSpatializedVolume;
	float m_flRadius;
	int m_nPitch;
	vec3_t* m_pOrigin;
	vec3_t* m_pDirection;
	bool m_bUpdatePositions;
	bool m_bIsSentence;
	bool m_bDryMix;
	bool m_bSpeaker;
	bool m_bSpecialDSP;
	bool m_bFromServer;
};

class i_engine_sound {
	public:
	void get_active_sounds(utl_vector<sound_info_t>& sndlist) {
		return util::call_virtual<void(__thiscall*)(void*, utl_vector<sound_info_t>&)>(this, 19)(this, sndlist);
	}
};