#include <stdio.h>
#include <stdlib.h>
#include "cube.h"
#include "obstacles.h"
#include "win.h"


#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000

void init_cube(cube *carre, SDL_Texture* cube_texture) {//initialisation de la position du cube, de sa hauteur et sa largeur
    carre->x = 75;
    carre->y = 600;
    carre->w = 40;
    carre->h = 40;
    carre->texture = cube_texture;
    carre->vitesse_y = 0;
    carre->en_saut = 0;
}

void afficher_cube(SDL_Renderer* renderer, cube* carre) {//affichage du cube
    SDL_Rect dest = {carre->x, carre->y, carre->w, carre->h};
    SDL_RenderCopy(renderer, carre->texture, NULL, &dest);
}

void gerer_saut(cube *carre, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {//event touche espace
        if (event->key.keysym.sym == SDLK_SPACE && !carre->en_saut) {
            carre->vitesse_y = -17; //on augmente la position en y (axe vers le bas donc valeur négative)
            carre->en_saut = 1;//temps en l'air
        }
    }
}

void update_saut(cube *carre, int y_sol) {
    if (carre->en_saut) {
        carre->vitesse_y += 1; //durée en l'air du cube
        carre->y += carre->vitesse_y;

        if (carre->y >= y_sol) {//si le cube est au sol, il n'a pas de vitesse en y et n'est pas en état de saut
            carre->y = y_sol;
            carre->vitesse_y = 0;
            carre->en_saut = 0;
        }
    }
}

int check_collision(cube* carre, SDL_Rect obstacle) {
    SDL_Rect cube_rect = {carre->x, carre->y, carre->w, carre->h};
    // Collision rectangle simple
    if (SDL_HasIntersection(&cube_rect, &obstacle)) {
        return 1; // collision
    }
    return 0;
}

int hauteur_sol_sous_cube(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX) {
    int y_sol = 600; // Par défaut, sol du bas

    SDL_Rect cube_rect = {carre->x, carre->y, carre->w, carre->h};

    for (int i = 0; i < nb_obstacles; i++) {
        int x_ecran = obstacles[i].x - scrollX;

        SDL_Rect obs_rect = {//en fonction de l'obstacle il s'adapte à sa position, stockés dans une struct 
            x_ecran,
            obstacles[i].y,
            obstacles[i].w,
            obstacles[i].h
        };

        // Si le cube est au-dessus de l'obstacle (en x) et qu’il peut se poser dessus
        if (cube_rect.x + cube_rect.w > obs_rect.x &&
            cube_rect.x < obs_rect.x + obs_rect.w &&
            cube_rect.y + cube_rect.h <= obs_rect.y &&
            obs_rect.y < y_sol) {
            y_sol = obs_rect.y; // Met à jour la hauteur du "sol"
        }
    }

    return y_sol;
}


int detecter_collision(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX, int previous_y) {
    SDL_Rect rect_cube = { carre->x, carre->y, carre->w, carre->h };

    for (int i = 0; i < nb_obstacles; i++) {
        SDL_Rect rect_obs = {
            obstacles[i].x - scrollX,//htibox autour de l'obstacle, pour prendre sa position et après détecter le contact entre le carré et l'obstacle
            obstacles[i].y,
            obstacles[i].w,
            obstacles[i].h
        };
       
        if (obstacles[i].type == 3 || obstacles[i].type == 4) { // Triangles ou trous : game over direct, peu importe la collision 
            if (SDL_HasIntersection(&rect_cube, &rect_obs)) {
                return 1; // Game over
            }
        }
        
        else if (obstacles[i].type == 2 || obstacles[i].type == 1) { // Carré (type 2) — on peut atterrir dessus, mais pas sur sa position latérale 
            if (SDL_HasIntersection(&rect_cube, &rect_obs)) {
                // Si le cube venait du dessus
                if (previous_y + carre->h <= obstacles[i].y && carre->vitesse_y >= 0) {//contact entre l'obstacle et le cube
                    carre->y = obstacles[i].y - carre->h;
                    carre->vitesse_y = 0;
                    carre->en_saut = 0;
                    continue; // pas de game over
                } else {
                    return 1; // s'il y a une collision latérale on renvoie un game over
                }
            }
        }

        else if(obstacles[i].type == 5){
            if(SDL_HasIntersection(&rect_cube, &rect_obs)){
                return 2;
            }
        }

        
    }

    return 0; // pas de collision mortelle
}

