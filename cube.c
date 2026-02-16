#include <stdio.h>
#include <stdlib.h>
#include "cube.h"
#include "obstacles.h"
#include "win.h"

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000

/**
 * @param carre Pointer to the cube structure
 * @param cube_texture The texture for the cube
 * @goal Initialize the cube's position, size, and physics properties
 */
void init_cube(cube *carre, SDL_Texture* cube_texture) {
    carre->x = 75;
    carre->y = 600;
    carre->w = 40;
    carre->h = 40;
    carre->texture = cube_texture;
    carre->vitesse_y = 0;
    carre->en_saut = 0;
}

/**
 * @param renderer The SDL renderer
 * @param carre Pointer to the cube structure
 * @goal Display the cube on screen
 */
void afficher_cube(SDL_Renderer* renderer, cube* carre) {
    SDL_Rect dest = {carre->x, carre->y, carre->w, carre->h};
    SDL_RenderCopy(renderer, carre->texture, NULL, &dest);
}

/**
 * @param carre Pointer to the cube structure
 * @param event Pointer to the SDL event
 * @goal Handle jump input when space key is pressed
 */
void gerer_saut(cube *carre, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_SPACE && !carre->en_saut) {
            carre->vitesse_y = -17;
            carre->en_saut = 1;
        }
    }
}

/**
 * @param carre Pointer to the cube structure
 * @param y_sol The ground level position
 * @goal Update cube's vertical position with gravity and landing
 */
void update_saut(cube *carre, int y_sol) {
    if (carre->en_saut) {
        carre->vitesse_y += 1;
        carre->y += carre->vitesse_y;
        if (carre->y >= y_sol) {
            carre->y = y_sol;
            carre->vitesse_y = 0;
            carre->en_saut = 0;
        }
    }
}

/**
 * @param carre Pointer to the cube structure
 * @param obstacle The obstacle rectangle
 * @goal Check if the cube collides with the given obstacle
 */
int check_collision(cube* carre, SDL_Rect obstacle) {
    SDL_Rect cube_rect = {carre->x, carre->y, carre->w, carre->h};
    if (SDL_HasIntersection(&cube_rect, &obstacle)) {
        return 1;
    }
    return 0;
}

/**
 * @param carre Pointer to the cube structure
 * @param obstacles Array of obstacles
 * @param nb_obstacles Number of obstacles in the array
 * @param scrollX The current scroll offset
 * @goal Calculate the ground level beneath the cube (platforms or floor)
 */
int hauteur_sol_sous_cube(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX) {
    int y_sol = 600;
    SDL_Rect cube_rect = {carre->x, carre->y, carre->w, carre->h};
    for (int i = 0; i < nb_obstacles; i++) {
        int x_ecran = obstacles[i].x - scrollX;
        SDL_Rect obs_rect = {
            x_ecran,
            obstacles[i].y,
            obstacles[i].w,
            obstacles[i].h
        };
        if (cube_rect.x + cube_rect.w > obs_rect.x &&
            cube_rect.x < obs_rect.x + obs_rect.w &&
            cube_rect.y + cube_rect.h <= obs_rect.y &&
            obs_rect.y < y_sol) {
            y_sol = obs_rect.y;
        }
    }
    return y_sol;
}

/**
 * @param carre Pointer to the cube structure
 * @param obstacles Array of obstacles
 * @param nb_obstacles Number of obstacles in the array
 * @param scrollX The current scroll offset
 * @param previous_y The cube's previous Y position
 * @goal Detect collisions and return game state (0=none, 1=game over, 2=win)
 */
int detecter_collision(cube* carre, obstacle* obstacles, int nb_obstacles, int scrollX, int previous_y) {
    SDL_Rect rect_cube = { carre->x, carre->y, carre->w, carre->h };
    for (int i = 0; i < nb_obstacles; i++) {
        SDL_Rect rect_obs = {
            obstacles[i].x - scrollX,
            obstacles[i].y,
            obstacles[i].w,
            obstacles[i].h
        };
       
        if (obstacles[i].type == 3 || obstacles[i].type == 4) {
            if (SDL_HasIntersection(&rect_cube, &rect_obs)) {
                return 1;
            }
        }
        else if (obstacles[i].type == 2 || obstacles[i].type == 1) {
            if (SDL_HasIntersection(&rect_cube, &rect_obs)) {
                if (previous_y + carre->h <= obstacles[i].y && carre->vitesse_y >= 0) {
                    carre->y = obstacles[i].y - carre->h;
                    carre->vitesse_y = 0;
                    carre->en_saut = 0;
                    continue;
                } else {
                    return 1;
                }
            }
        }
        else if(obstacles[i].type == 5){
            if(SDL_HasIntersection(&rect_cube, &rect_obs)){
                return 2;
            }
        }
    }
    return 0;
}