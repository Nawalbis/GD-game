#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include "main.h"
#include "background.h"
#include "menu.h"
#include "levels.h"
#include "jeu.h"
#include "cube.h"
#include "obstacles.h" 
#include "audio.h"
#include "win.h"

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000


int main(int argc, char* argv[]) {
    srand(time(NULL));

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* background = NULL;
    SDL_Texture* perso = NULL;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur initialisation SDL : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur initialisation SDL_image : %s", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Geometry Dash", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!window || !renderer) {
        printf("Erreur création fenêtre ou renderer : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (!init_audio()) {
        return 1;
    }
    play_music();

    int continuer = 1;
    int niveau = 0;
    int jeu = 0;
    int niveau_actuel_jeu = 0; // Pour savoir quel niveau est en cours

    background = chargerBackground(renderer, niveau);
    if (background == NULL) {
        printf("Erreur chargement background.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    fond bg1, bg2;
    init_fond(&bg1, &bg2, background);

    SDL_Surface* temp_surface = IMG_Load("images/image_perso/rouge.png");
    if (!temp_surface) {
        printf("Erreur chargement image cube : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    perso = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    if (!perso) {
        printf("Erreur création texture personnage : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    cube carre;
    init_cube(&carre, perso);

    obstacle* obstacles = NULL;
    int nb_obstacles = 0;

    SDL_Texture* textures[6];
    for (int i = 0; i < 6; i++) {
        textures[i] = charger_texture(renderer, i);
        if (!textures[i]) {
            printf("Erreur chargement texture type %d\n", i);
        }
    }

    int scrollX = 0;

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                continuer = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                int ancien_niveau = niveau; 
                niveau = clic_niveau(event, niveau);

                if (x < 600 && x > 400 && y < 450 && y > 350) {
                    if (niveau == 0) {
                        niveau = 1;
                    } else if (niveau >= 1 && niveau <= 3) {
                        // Charger les obstacles du niveau choisi
                        nb_obstacles = charger_obstacles_niveau(&obstacles, niveau);
                        niveau_actuel_jeu = niveau;
                        
                        SDL_DestroyTexture(background);
                        background = chargerFondNiveau(renderer, niveau);
                        init_fond(&bg1, &bg2, background);
                        init_cube(&carre, perso);
                        scrollX = 0;
                        jeu = 1;
                        continue;
                    }
                }

                if (ancien_niveau != niveau)
                    maj_affichage(&background, renderer, window, niveau);
            }

            if (jeu == 1)
                gerer_saut(&carre, &event);
        }

        if (jeu == 1) {
            int previous_y = carre.y;
            int y_sol = hauteur_sol_sous_cube(&carre, obstacles, nb_obstacles, scrollX);
            update_saut(&carre, y_sol);

            maj_affichage_bg(&bg1, &bg2);
            scrollX += 5;

            int resultat_collision = detecter_collision(&carre, obstacles, nb_obstacles, scrollX, previous_y);

            if (resultat_collision == 1) {
                printf("GAME OVER - Niveau %d\n", niveau_actuel_jeu);

                jeu = 0;
                scrollX = 0;
                niveau = 0;

                SDL_DestroyTexture(background);
                background = chargerBackground(renderer, niveau);
                if (background == NULL) {
                    printf("Erreur de rechargement du fond niveau 0.\n");
                    continuer = 0;
                    break;
                }

                init_fond(&bg1, &bg2, background);
                init_cube(&carre, perso);
            } else if (resultat_collision == 2) {
                printf("BRAVO - Niveau %d terminé!\n", niveau_actuel_jeu);
                SDL_DestroyTexture(background);
                texture_win(renderer, window);
                jeu = 0;
                scrollX = 0;
                niveau = 0;
                background = chargerBackground(renderer, niveau);
                if (background == NULL) {
                    printf("Erreur de rechargement du fond niveau 0.\n");
                    continuer = 0;
                    break;
                }
                init_fond(&bg1, &bg2, background);
                init_cube(&carre, perso);
            }
        }

        SDL_RenderClear(renderer);

        if (jeu == 1) {
            afficher_fond(renderer, &bg1);
            afficher_fond(renderer, &bg2);

            for (int i = 0; i < nb_obstacles; i++) {
                int x_ecran = obstacles[i].x - scrollX;

                if (x_ecran + obstacles[i].w > 0 && x_ecran < WINDOW_WIDTH) {
                    SDL_Rect dest = {
                        x_ecran,
                        obstacles[i].y,
                        obstacles[i].w,
                        obstacles[i].h
                    };
                    SDL_RenderCopy(renderer, textures[obstacles[i].type], NULL, &dest);
                }   
            }

            afficher_cube(renderer, &carre);
        } else {
            afficherBackground(renderer, background);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    for (int i = 0; i < 6; i++) {
        if (textures[i]) SDL_DestroyTexture(textures[i]);
    }
    
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    clean_audio();
    SDL_Quit();

    return EXIT_SUCCESS;
}