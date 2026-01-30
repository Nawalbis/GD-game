#include "win.h"
#include "stdio.h"
#include <stdlib.h>

void texture_win(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_Texture* win = NULL;
    SDL_Surface* temp_surface = IMG_Load("images/images_backgrounds/win.png");
    
    if (!temp_surface) {
        printf("Erreur chargement image win : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    
    win = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    
    if (!win) {
        printf("Erreur création texture win : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    // Affichage de l'écran de victoire
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, win, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    // Attendre 3 secondes avant de revenir au menu
    SDL_Delay(3000);
    
    SDL_DestroyTexture(win);
}