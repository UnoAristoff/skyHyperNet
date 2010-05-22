#ifndef _C_SERVSND_H
#define _C_SERVSND_H

#include "TService.h"
#include <string>
#include <stdio.h>

#include "SDL/SDL_mixer.h"

class CServSnd: public TService<CServSnd> {

    public:
//    bool CallFunc( void* ptr, long size );
        const char *getName(){ return "ServSnd"; }
        tServType getType(){ return tServSnd; }
        void Release(){ delete this; }

	bool PlayFX( ahn_command_head& head, void* data );
	bool PlayMusic( ahn_command_head& head, void* data );

        CServSnd();
        ~CServSnd();

    protected:

    bool SoundEnabled;
    Mix_Music *CurrentMusic;

};

#endif
