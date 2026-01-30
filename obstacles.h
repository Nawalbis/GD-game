#ifndef OBSTACLES_H
#define OBSTACLES_H

#include </opt/homebrew/include/SDL2/SDL_image.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;
    int type;
} obstacle;

// Fonction pour charger les obstacles d'un niveau spécifique
int charger_obstacles_niveau(obstacle** out_obstacles, int niveau);

// Fonction pour charger une texture
SDL_Texture* charger_texture(SDL_Renderer* renderer, int type);

#endif