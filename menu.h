#ifndef MENU_H
#define MENU_H
#include</opt/homebrew/include/SDL2/SDL_image.h>
#include "cube.h"

/**
 * \brief on gere les clics droits et gauches de l'utilisateur pour naviguer dans les différents niveaux en mettant a jour au fur et a mesure l'affichage
 * \property fichier background integré pour recuperer les images associées à la variable niveau
 * \property evenement en fonction de l'endroit de l'écran cliqué, si on clique a droite, le niveau augmente, si on clique a gauche, il baisse
 */

int clic_niveau(SDL_Event event,int niveau);

void maj_affichage(SDL_Texture** background, SDL_Renderer* renderer, SDL_Window* window, int niveau);


#endif