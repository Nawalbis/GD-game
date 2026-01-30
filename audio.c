#include "audio.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>

Mix_Music *musique = NULL;
Mix_Chunk *saut = NULL;

int init_audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur initialisation audio : %s\n", Mix_GetError());
        return 0;
    }

    // Charger les sons
    musique = Mix_LoadMUS("audio/gd.mp3");
    if (!musique) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
    }

    saut = Mix_LoadWAV("audio/saut.wav");
    if (!saut) {
        printf("Erreur chargement son : %s\n", Mix_GetError());
    }

    return 1;
}

void play_music() {
    if (musique) {
        Mix_PlayMusic(musique, -1); // Boucle infinie
    }
}

void play_saut() {
    if (saut) {
        Mix_PlayChannel(-1, saut, 0);
    }
}

void clean_audio() {
    if (musique) Mix_FreeMusic(musique);
    if (saut) Mix_FreeChunk(saut);
    Mix_CloseAudio();
}