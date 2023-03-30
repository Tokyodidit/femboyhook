#pragma once
#include "../../source-sdk/math/vector3d.hpp"
#include "../interfaces/i_trace.hpp"

enum {
	TE_BEAMPOINTS = 0x00,		
	TE_SPRITE = 0x01,	
	TE_BEAMDISK = 0x02,	
	TE_BEAMCYLINDER = 0x03,		
	TE_BEAMFOLLOW = 0x04,		
	TE_BEAMRING = 0x05,		
	TE_BEAMSPLINE = 0x06,
	TE_BEAMRINGPOINT = 0x07,
	TE_BEAMLASER = 0x08,		
	TE_BEAMTESLA = 0x09,
};
enum {
	FBEAM_STARTENTITY = 0x00000001,
	FBEAM_ENDENTITY = 0x00000002,
	FBEAM_FADEIN = 0x00000004,
	FBEAM_FADEOUT = 0x00000008,
	FBEAM_SINENOISE = 0x00000010,
	FBEAM_SOLID = 0x00000020,
	FBEAM_SHADEIN = 0x00000040,
	FBEAM_SHADEOUT = 0x00000080,
	FBEAM_ONLYNOISEONCE = 0x00000100,		
	FBEAM_NOTILE = 0x00000200,
	FBEAM_USE_HITBOXES = 0x00000400,		
	FBEAM_STARTVISIBLE = 0x00000800,		
	FBEAM_ENDVISIBLE = 0x00001000,		    
	FBEAM_ISACTIVE = 0x00002000,
	FBEAM_FOREVER = 0x00004000,
	FBEAM_HALOBEAM = 0x00008000,		   
	FBEAM_REVERSED = 0x00010000,
	NUM_BEAM_FLAGS = 17	                  
};
struct BeamTrail_t {
	BeamTrail_t* next;
	float			die;
	vec3_t			org;
	vec3_t			vel;
};
#define NOISE_DIVISIONS		128
#define MAX_BEAM_ENTS		10
typedef int pixelvis_handle_t;

class Beam_t {
public:
	Beam_t();
	virtual const vec3_t& GetRenderOrigin(void) = 0;
	virtual const vec3_t& GetRenderAngles(void) = 0;
	virtual const matrix_t& RenderableToWorldTransform() = 0;
	virtual void GetRenderBounds(vec3_t& mins, vec3_t& maxs) = 0;
	virtual bool ShouldDraw(void) = 0;
	virtual bool IsTransparent(void) = 0;
	virtual int	DrawModel(int flags) = 0;
	virtual void ComputeFxBlend() = 0;
	virtual int	GetFxBlend() = 0;
	void Reset();
	void ComputeBounds();
	vec3_t m_Mins;
	vec3_t m_Maxs;
	pixelvis_handle_t* m_queryHandleHalo;
	float m_haloProxySize;
	Beam_t* next;
	int	type;
	int	flags;
	int	numAttachments;
	vec3_t attachment[MAX_BEAM_ENTS];
	vec3_t delta;
	float t;
	float freq;
	float die;
	float width;
	float endWidth;
	float fadeLength;
	float amplitude;
	float life;
	float r, g, b;
	float brightness;
	float speed;
	float frameRate;
	float frame;
	int segments;
	HANDLE entity[MAX_BEAM_ENTS];
	int	attachmentIndex[MAX_BEAM_ENTS];
	int	modelIndex;
	int	haloIndex;
	float haloScale;
	int frameCount;
	float rgNoise[NOISE_DIVISIONS + 1];
	BeamTrail_t* trail;
	float start_radius;
	float end_radius;
	bool m_bCalculatedNoise;
	float m_flHDRColorScale;
};

struct BeamInfo_t {
	int	m_nType;
	player_t* m_pStartEnt;
	int	m_nStartAttachment;
	player_t* m_pEndEnt;
	int	m_nEndAttachment;
	vec3_t m_vecStart;
	vec3_t m_vecEnd;
	int	m_nModelIndex;
	const char* m_pszModelName;
	int	m_nHaloIndex;
	const char* m_pszHaloName;
	float m_flHaloScale;
	float m_flLife;
	float m_flWidth;
	float m_flEndWidth;
	float m_flFadeLength;
	float m_flAmplitude;
	float m_flBrightness;
	float m_flSpeed;
	int	m_nStartFrame;
	float m_flFrameRate;
	float m_flRed;
	float m_flGreen;
	float m_flBlue;
	bool m_bRenderable;
	int	m_nSegments;
	int	m_nFlags;
	vec3_t m_vecCenter;
	float m_flStartRadius;
	float m_flEndRadius;

	BeamInfo_t() {
		m_nType = TE_BEAMPOINTS;
		m_nSegments = -1;
		m_pszModelName = NULL;
		m_pszHaloName = NULL;
		m_nModelIndex = -1;
		m_nHaloIndex = -1;
		m_bRenderable = true;
		m_nFlags = 0;
	}
};

class C_Beam;

class i_view_render_beams {
public:
	virtual void init_beams(void) = 0;
	virtual void shutdown_beams(void) = 0;
	virtual void clear_beams(void) = 0;
	virtual void update_temp_ent_beams() = 0;
	virtual void draw_beam(C_Beam* pbeam, trace_filter* pEntityBeamTraceFilter = NULL) = 0;
	virtual void draw_beam(Beam_t* pbeam) = 0;
	virtual void kill_dead_beams(player_t* pEnt) = 0;
	virtual Beam_t* create_beam_ents(BeamInfo_t& beamInfo) = 0;
	virtual Beam_t* create_beam_ent_point(BeamInfo_t& beamInfo) = 0;
	virtual	Beam_t* create_beam_point(BeamInfo_t& beamInfo) = 0;
	virtual Beam_t* create_beam_ring(BeamInfo_t& beamInfo) = 0;
	virtual Beam_t* create_beam_ring_point(BeamInfo_t& beamInfo) = 0;
	virtual Beam_t* create_beam_circle_point(BeamInfo_t& beamInfo) = 0;
	virtual Beam_t* create_beam_follow(BeamInfo_t& beamInfo) = 0;
	virtual void free_beam(Beam_t* pBeam) = 0;
	virtual void update_beam_info(Beam_t* pBeam, BeamInfo_t& beamInfo) = 0;
	virtual void create_beam_ents(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b, int type = -1) = 0;
	virtual void create_beam_ent_point(int	nStartEntity, const vec3_t* pStart, int nEndEntity, const vec3_t* pEnd, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b) = 0;
	virtual void create_beam_point(vec3_t& start, vec3_t& end, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b) = 0;
	virtual void create_beam_ring(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b, int flags = 0) = 0;
	virtual void create_beam_ring_point(const vec3_t& center, float start_radius, float end_radius, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b, int flags = 0) = 0;
	virtual void create_beam_circle_point(int type, vec3_t& start, vec3_t& end, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b) = 0;
	virtual void create_beam_follow(int startEnt, int modelIndex, int haloIndex, float haloScale, float life, float width, float m_nEndWidth, float m_nFadeLength, float r, float g, float b, float brightness) = 0;
};
