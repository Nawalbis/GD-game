#ifndef LEVELS_H
#define LEVELS_H
#include </opt/homebrew/include/SDL2/SDL_image.h>


/**
 * \brief Chargement des fonds de chaque niveau (une fois le jeu lancé) sans avoir a creer une texture ou une surface car on appelle l'unique fonction dans le main 
 * \property SDL_texture
 * \property SDL_Surface
 * \property 1 image png par niveau (3) 
 */

SDL_Texture* chargerFondNiveau(SDL_Renderer* renderer, int level);


#endif