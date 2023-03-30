#pragma once
#include "../../source-sdk/math/vector3d.hpp"
#include <minwindef.h>
class player_t;
#define	SURF_LIGHT		0x0001	
#define	SURF_SKY2D		0x0002		
#define	SURF_SKY		0x0004		
#define	SURF_WARP		0x0008		
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	
#define	SURF_TRIGGER	0x0040	
#define	SURF_NODRAW		0x0080	
#define	SURF_HINT		0x0100	
#define	SURF_SKIP		0x0200	
#define SURF_NOLIGHT	0x0400	
#define SURF_BUMPLIGHT	0x0800	
#define SURF_NOSHADOWS	0x1000	
#define SURF_NODECALS	0x2000	
#define SURF_NOPAINT	0x2000	
#define SURF_NOCHOP		0x4000	
#define SURF_HITBOX		0x8000	

#define CHAR_TEX_ANTLION		'A'
#define CHAR_TEX_BLOODYFLESH	'B'
#define	CHAR_TEX_CONCRETE		'C'
#define CHAR_TEX_DIRT			'D'
#define CHAR_TEX_EGGSHELL		'E' 
#define CHAR_TEX_FLESH			'F'
#define CHAR_TEX_GRATE			'G'
#define CHAR_TEX_ALIENFLESH		'H'
#define CHAR_TEX_CLIP			'I'
#define CHAR_TEX_UNUSED		    'J'
#define CHAR_TEX_SNOW			'K'
#define CHAR_TEX_PLASTIC		'L'
#define CHAR_TEX_METAL			'M'
#define CHAR_TEX_SAND			'N'
#define CHAR_TEX_FOLIAGE		'O'
#define CHAR_TEX_COMPUTER		'P'
#define CHAR_TEX_UNUSED		    'Q'
#define CHAR_TEX_REFLECTIVE		'R'
#define CHAR_TEX_SLOSH			'S'
#define CHAR_TEX_TILE			'T'
#define CHAR_TEX_CARDBOARD		'U'
#define CHAR_TEX_VENT			'V'
#define CHAR_TEX_WOOD			'W'
#define CHAR_TEX_UNUSED		    'X' 
#define CHAR_TEX_GLASS			'Y'
#define CHAR_TEX_WARPSHIELD		'Z' 

#define	CONTENTS_EMPTY			0		
#define	CONTENTS_SOLID			0x1		
#define	CONTENTS_WINDOW			0x2		
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_MIST			0x40
#define CONTENTS_OPAQUE			0x80		
#define	LAST_VISIBLE_CONTENTS	0x80
#define ALL_VISIBLE_CONTENTS 	(LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))
#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED5		0x200
#define CONTENTS_UNUSED6		0x4000
#define CONTENTS_TEAM1			0x800		
#define CONTENTS_TEAM2			0x1000		
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000		
#define CONTENTS_MOVEABLE		0x4000		
#define	CONTENTS_AREAPORTAL		0x8000		
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	
#define	CONTENTS_MONSTER		0x2000000	
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	
#define	CONTENTS_TRANSLUCENT	0x10000000	
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	

#define	MASK_ALL				(0xFFFFFFFF)
#define	MASK_SOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE) 			
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE) 	
#define	MASK_NPCSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE) 
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME) 							
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE) 							
#define MASK_OPAQUE_AND_NPCS	(MASK_OPAQUE|CONTENTS_MONSTER)										
#define	MASK_VISIBLE			(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE) 								
#define MASK_VISIBLE_AND_NPCS	(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE) 							
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX) 	
#define MASK_SHOT_HULL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE) 	
#define MASK_SHOT_PORTAL		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW) 							
#define MASK_SOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE) 					
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE) 			
#define MASK_NPCSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE) 			
#define MASK_NPCWORLDSTATIC		(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE) 					
#define MASK_SPLITAREAPORTAL	(CONTENTS_WATER|CONTENTS_SLIME) 									

class __declspec(align(16))VectorAligned : public vec3_t {
public:
	VectorAligned& operator=(const vec3_t& vOther) {
		init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

class IHandleEntity;

struct ray_t {
	VectorAligned m_start; 
	VectorAligned m_delta; 
	VectorAligned m_start_offset; 
	VectorAligned m_extents;
	const matrix_t* m_world_axis_transform;
	//const matrix_t *m_pWorldAxisTransform;
	bool m_is_ray; 
	bool m_is_swept;

	void initialize(const vec3_t& start, const vec3_t& end) {
		m_delta = end - start;

		m_is_swept = (m_delta.length_sqr() != 0);

		m_extents.x = m_extents.y = m_extents.z = 0.0f;
		m_is_ray = true;

		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;

		m_start = start;
	}

	void initialize(vec3_t & vecStart, vec3_t & vecEnd, vec3_t min, vec3_t max) {
		m_delta = vecEnd - vecStart;

		m_is_swept = (m_delta.length_sqr() != 0);

		m_extents.x = (max.x - min.x);
		m_extents.y = (max.y - min.y);
		m_extents.z = (max.z - min.z);
		m_is_ray = false;

		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;

		m_start = vecStart + ((max + min) * 0.5f);
	}

private:
};

struct csurface_t {
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

struct cplane_t {
	constexpr auto operator!=(const cplane_t& v) const noexcept
	{
		return normal.x != v.normal.x || normal.y != v.normal.y || normal.z != v.normal.z;
	}
	vec3_t normal;
	float m_dist;
	BYTE m_type;
	BYTE m_sign_bits;
	BYTE m_pad[2];
};

struct trace_t {
	vec3_t start;
	vec3_t end;
	cplane_t plane;
	float flFraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startSolid;
	float fractionLeftSolid;
	csurface_t surface;
	int hitgroup;
	short physicsBone;
	player_t* entity;
	int hitbox;

	bool did_hit() const {
		return flFraction < 1.f;
	}

	bool did_hit_world() const {
		return false;
	}

	bool did_hit_non_world_entity() const {
		return entity != NULL && !did_hit_world();
	}
};

enum TraceType_t {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, 
	TRACE_ENTITIES_ONLY, 
	TRACE_EVERYTHING_FILTER_PROPS,
};

class i_trace_filter {
public:
	virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class trace_filter : public i_trace_filter {
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return (pEntityHandle != skip);
	}

	TraceType_t GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void* skip;
};

class trace_filter_one_entity : public i_trace_filter {
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return (pEntityHandle == pEntity);
	}

	TraceType_t GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void* pEntity;
};

class trace_filter_one_entity2 : public i_trace_filter {
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return (pEntityHandle == pEntity);
	}

	TraceType_t GetTraceType() const {
		return TRACE_ENTITIES_ONLY;
	}

	void* pEntity;
};

class trace_filter_skip_two_entities : public i_trace_filter {
public:
	trace_filter_skip_two_entities(void* pPassEnt1, void* pPassEnt2) {
		passentity1 = pPassEnt1;
		passentity2 = pPassEnt2;
	}

	virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
	}

	virtual TraceType_t GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void* passentity1;
	void* passentity2;
};

class trace_filter_skip_one_entity : public i_trace_filter {
public:
	trace_filter_skip_one_entity(void* pPassEnt1) {
		passentity1 = pPassEnt1;
	}

	virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return !(pEntityHandle == passentity1);
	}

	virtual TraceType_t GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void* passentity1;
};

class trace_entity : public i_trace_filter {
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return !(pEntityHandle == pSkip1);
	}

	TraceType_t GetTraceType() const {
		return TRACE_ENTITIES_ONLY;
	}

	void* pSkip1;
};

class trace_world_only : public i_trace_filter {
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
		return false;
	}

	TraceType_t GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void* pSkip1;
};

class collideable_t;
class trace {
public:
	virtual int get_point_contents(const vec3_t& pos, int mask = MASK_ALL, IHandleEntity** ent = nullptr) = 0;
	virtual int get_point_contents_world(const vec3_t& pos, int mask = MASK_ALL) = 0;
	virtual int get_point_contents_collideable(collideable_t* collide, const vec3_t& pos) = 0;
	virtual void clip_ray_to_entity(const ray_t& ray, unsigned int mask, player_t* ent, trace_t* trace) = 0;
	virtual void clip_ray_to_collideable(const ray_t& ray, unsigned int mask, collideable_t* collide, trace_t* trace) = 0;
	virtual void run(const ray_t& ray, unsigned int mask, i_trace_filter* filter, trace_t* trace) = 0;
};