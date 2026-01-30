#ifndef BACKGROUND_H
#define BACKGROUND_H
#include</opt/homebrew/include/SDL2/SDL_image.h>
#include <stdio.h>
#include<stdlib.h>
#define SPEED 2

/**
 * \brief On cree une texture pour y placer nos images de background, si la surface est deja occupée on la libere pour placer nos images
 * \property images en png
 * \property tableau de char d'une taille définie pour eviter les depassements de memoire
 */

SDL_Texture* creerTexture(SDL_Window* window, SDL_Renderer* renderer, char* filename);

void afficherBackground(SDL_Renderer* renderer, SDL_Texture* background);

SDL_Texture* chargerBackground(SDL_Renderer* renderer, int niveau);

#endif