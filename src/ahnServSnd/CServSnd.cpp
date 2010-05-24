#include "CServSnd.h"
#include <iostream>

#include "ahn_servsnd.h"
#include "SDL/SDL.h"

#include "ahn_function.h"

using namespace std;
IMicrocore* pCore;

//char buffer[ 80 ];

CServSnd::CServSnd(){

    cout << "ServSnd created.. " << endl;

    INI_FUNC( FServSndEndF );
    REG_FUNC( CServSnd, FPlayFX, PlayFX );
    REG_FUNC( CServSnd, FPlayMusic, PlayMusic );

    SoundEnabled = true;

  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;

  if ( SDL_InitSubSystem(SDL_INIT_AUDIO) < 0 ) {
        cout << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        SoundEnabled = false;
        }
  else {
        if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
              cout << "Unable to open audio! " << endl;
              SoundEnabled = false;
              } else {
              Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
              };
       };

};

CServSnd::~CServSnd(){

    cout << "ServSnd deleted.. " << endl;

};

bool CServSnd::PlayFX( ahn_command_head& head, void* data ){

//    cout << "ServSnd PlayFX: " << (const char*) data << endl;
    if (!SoundEnabled) return true;


    CurrentMusic = Mix_LoadMUS( (const char*) data );
    if (CurrentMusic) {
		Mix_PlayMusic( CurrentMusic , -1);
		return true;
		}

    cout << "Couldn't play " << (const char*) data << " : " << SDL_GetError() << endl;
	return false; //че-то не сработало :(

};

bool CServSnd::PlayMusic( ahn_command_head& head, void* data ){

//    pCore = myCore;
    LogMsg("ServSnd PlayMusic '%s'", (const char*) data );

//    cout << "ServSnd PlayMusic: " << (const char*) data << endl;
    if (!SoundEnabled) return true;

    CurrentMusic = Mix_LoadMUS( (const char*) data );
    if (CurrentMusic) {
		Mix_PlayMusic( CurrentMusic , -1);
		return true;
		}

    cout << "Couldn't play " << (const char*) data << " : " << SDL_GetError() << endl;
    return true;

};
