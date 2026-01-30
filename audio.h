#ifndef AUDIO_H
#define AUDIO_H
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>


int init_audio();
void play_music();
void play_saut();
void clean_audio();

#endif