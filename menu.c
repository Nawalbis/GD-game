#include<stdio.h>
#include<stdlib.h>
#include "menu.h"
#include</opt/homebrew/include/SDL2/SDL.h>
#include "background.h"
#include "levels.h"

int clic_niveau(SDL_Event event, int niveau) {
    int x = event.button.x;
    if (niveau >= 1 && niveau <= 3) { //avancer dans les niveaux en fonction de l'endroit ou on appuie
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

void maj_affichage(SDL_Texture** background, SDL_Renderer* renderer, SDL_Window* window, int niveau){
    SDL_DestroyTexture(*background); //mise a jour de l'affichage en fonction du niveau choisi
    *background = chargerBackground(renderer, niveau);
    if (*background == NULL) {
        printf("Erreur lors du chargement du background du niveau %d.\n", niveau);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

//fonction retour une fois sur le fond d'un niveau pour aller en arriere / a voir si le niveau commence direct et on peut revenir en arrière que si une fois qu'on a perdu



