#include "background.h"
#include<stdio.h>
#include<stdlib.h>

/**
 * @param window The SDL window
 * @param renderer The SDL renderer
 * @param filename Path to the image file
 * @goal Create and return an SDL texture from an image file
 */
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

/**
 * @param renderer The SDL renderer
 * @param background The background texture to display
 * @goal Render the background texture to fill the entire screen
 */
void afficherBackground(SDL_Renderer* renderer, SDL_Texture* background) {
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

/**
 * @param renderer The SDL renderer
 * @param niveau The menu level number (0-3)
 * @goal Load and return the appropriate menu background texture
 */
SDL_Texture* chargerBackground(SDL_Renderer* renderer, int niveau) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    char chemin[100];
    if (renderer == NULL) {
        printf("Erreur, renderer non valide : %s\n", SDL_GetError());
        return NULL;
    }
    switch (niveau) {
        case 0:
            snprintf(chemin, sizeof(chemin), "images/images_backgrounds/fond_accueil.png");
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