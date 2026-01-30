#include "background.h"
#include<stdio.h>
#include<stdlib.h>


SDL_Texture* creerTexture(SDL_Window* window, SDL_Renderer* renderer, char* filename) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(filename);

    if (surface != NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, surface); 
        SDL_FreeSurface(surface);
        
        if (texture != NULL) {
            return texture;
        }else{
            printf("Erreur de création de la texture : %s\n", SDL_GetError());
        }
    } else {
        printf("Erreur de chargement d'image (%s) : %s\n", filename, IMG_GetError());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void afficherBackground(SDL_Renderer* renderer, SDL_Texture* background) {
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

SDL_Texture* chargerBackground(SDL_Renderer* renderer, int niveau) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    char chemin[100];

    if (renderer == NULL) {
        printf("Erreur, renderer non valide : %s\n", SDL_GetError());
        return NULL;
    }

    switch (niveau) { //images png assimilées à des int pour pouvoir changer d'image facilement une fois dans la boucle if
        //fonds menu
        case 0:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/fond_accueil.png"); //snprintf pour definir une taille max grace a un tableau et eviter les depassements de memoire
            break;
        case 1:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/level1.png");
            break;
        case 2:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/level2.png");
            break;
        case 3:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/level3.png");
            break;
        default:
            printf("Erreur : niveau invalide (%d).\n", niveau);
            return NULL;
    }

    surface = IMG_Load(chemin);
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

