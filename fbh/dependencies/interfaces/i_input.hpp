#pragma once
#include "../../source-sdk/classes/c_usercmd.hpp"

class i_input {
public:
	std::byte pad0[0xC];            
	bool track_ir_available;      
	bool mouse_initialized;        
	bool mouse_active;           
	std::byte pad1[0x9A];           
	bool camera_in_third_person;    
	std::byte pad2[0x2];           
	vec3_t camera_offset;        
	std::byte pad3[0x38];            
	c_usercmd* m_pcommands;          

	c_usercmd *get_user_cmd( int slot, int sequence_num ) {
		using fn = c_usercmd * ( __thiscall * )( void *, int, int );
		return ( *( fn ** ) this )[ 8 ]( this, slot, sequence_num );
	}
};
