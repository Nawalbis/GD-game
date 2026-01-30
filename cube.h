#ifndef CUBE_H
#define CUBE_H
#include</opt/homebrew/include/SDL2/SDL_image.h>
#include "obstacles.h"


typedef struct{
    int x;
    int y;
    int w;
    int h;
    int vitesse_y;
    int en_saut;
    SDL_Texture* texture;
}cube;

void init_cube(cube *carre, SDL_Texture* cube_texture);

void afficher_cube(SDL_Renderer* renderer, cube* carre);

void gerer_saut(cube *carre, SDL_Event *event);

void update_saut(cube *carre, int y_sol);

int check_collision(cube* carre, SDL_Rect obstacle);

int hauteur_sol_sous_cube(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX);

int detecter_collision(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX, int previous_y);

// void gerer_collisions_obstacles(cube* carre, obstacle* obstacles, int nb_obstacles, int* jeu, int scrollX);


// void gerer_collisions_obstacles(cube* cube, obstacle* obstacles, int nb_obstacles, int* jeu, int scrollX);

// void deplacement_cube(cube * carre, SDL_Event * event, int y_initial);

#endif