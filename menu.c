#include<stdio.h>
#include<stdlib.h>
#include "menu.h"
#include</opt/homebrew/include/SDL2/SDL.h>
#include "background.h"
#include "levels.h"

/**
 * @param event The SDL mouse click event
 * @param niveau The current level
 * @goal Handle navigation between levels via clicks
 */
int clic_niveau(SDL_Event event, int niveau) {
    int x = event.button.x;
    if (niveau >= 1 && niveau <= 3) {
        if (x < 300) {
            niveau--;
            if (niveau < 1) niveau = 1;
        } else if (x > 700) {
            niveau++;
            if (niveau > 3) niveau = 3;
        }
    }
    return niveau;
}

/**
 * @param background Pointer to the background texture to update
 * @param renderer The SDL renderer
 * @param window The SDL window
 * @param niveau The level to display
 * @goal Update the background display based on the chosen level
 */
void maj_affichage(SDL_Texture** background, SDL_Renderer* renderer, SDL_Window* window, int niveau){
    SDL_DestroyTexture(*background);
    *background = chargerBackground(renderer, niveau);
    if (*background == NULL) {
        printf("Erreur lors du chargement du background du niveau %d.\n", niveau);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}