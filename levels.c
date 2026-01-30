#include "levels.h"
#include<stdio.h>
#include<stdlib.h>
#include "menu.h"


SDL_Texture* chargerFondNiveau(SDL_Renderer* renderer, int niveau) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    char chemin[100];

    if (renderer == NULL) {
        printf("Erreur, renderer non valide : %s\n", SDL_GetError());
        return NULL;
    }

    switch (niveau) {
        //association d'un int aux images de niveau
        case 1:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/fond_easy.png"); 
            break;
        case 2:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/fond_moyen.png");
            break;
        case 3:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/fond_hard.png");
            break;
        default:
            printf("Erreur : niveau invalide (%d).\n", niveau);
            return NULL;
    }

    surface = IMG_Load(chemin);//création de la surface transformée par la suite en texture 
    if (surface != NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == NULL) {
            printf("Erreur : %s\n", SDL_GetError());
        }
    } else {
        printf("Erreur de chargement de l'image (%s) : %s\n", chemin, IMG_GetError());
    }

    return texture;
}