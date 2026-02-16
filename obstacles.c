#include "obstacles.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

static obstacle obstacles_niveau1[] = {
    {900, 595, 45, 45, 2},
    {1300, 595, 45, 45, 3},
    {1700, 595, 80, 45, 4},
    {1900, 595, 45, 45, 2},
    {2300, 595, 45, 45, 1},
    {2300, 550, 45, 45, 2},
    {2700, 595, 45, 45, 3},
    {3100, 590, 150, 50, 1},
    {3500, 595, 45, 45, 2},
    {3900, 595, 80, 45, 4},
    {4100, 595, 45, 45, 2},
    {4500, 595, 45, 45, 2},
    {4800, 595, 45, 45, 2},
    {5100, 595, 45, 45, 2},
    {5500, 595, 45, 45, 2},
    {5650, 570, 45, 70, 2},
    {5800, 545, 45, 95, 2},
    {6100, 590, 200, 50, 1},
    {6500, 595, 45, 45, 3},
    {6900, 595, 45, 45, 2},
    {7200, 590, 150, 50, 1},
    {7500, 595, 45, 45, 3},
    {7900, 615, 25, 25, 5},
};

static obstacle obstacles_niveau2[] = {
    {700, 595, 45, 45, 3},
    {900, 595, 45, 45, 2},
    {1200, 595, 70, 45, 4},
    {1400, 595, 45, 45, 2},
    {1800, 595, 45, 45, 1},
    {1800, 550, 45, 45, 2},
    {2100, 595, 45, 45, 3},
    {2500, 590, 150, 50, 1},
    {2800, 595, 45, 45, 2},
    {3200, 595, 70, 45, 4},
    {3500, 595, 70, 45, 4},
    {3270, 560, 40, 80, 2},
    {3570, 560, 40, 80, 2},
    {3900, 595, 45, 45, 3},
    {4100, 595, 45, 45, 3},
    {4300, 595, 45, 45, 3},
    {4700, 595, 45, 45, 2},
    {4850, 575, 45, 65, 2},
    {5000, 555, 45, 85, 2},
    {5150, 535, 45, 105, 2},
    {5350, 535, 200, 45, 1},
    {5600, 560, 45, 80, 2},
    {5750, 585, 45, 55, 2},
    {6000, 590, 150, 50, 1},
    {6300, 595, 45, 45, 3},
    {6700, 595, 45, 45, 2},
    {6950, 595, 45, 45, 2},
    {7200, 590, 150, 50, 1},
    {7500, 595, 45, 45, 3},
    {7900, 615, 25, 25, 5},
};

static obstacle obstacles_niveau3[] = {
    {600, 595, 45, 45, 3},
    {750, 595, 45, 45, 3},
    {1000, 595, 60, 45, 4},
    {1200, 595, 45, 45, 2},
    {1500, 595, 45, 45, 1},
    {1500, 550, 45, 45, 1},
    {1500, 505, 45, 45, 2},
    {1750, 595, 60, 45, 4},
    {2000, 570, 80, 70, 1},
    {2150, 570, 80, 70, 1},
    {2300, 570, 80, 70, 1},
    {2010, 525, 45, 45, 3},
    {2160, 525, 45, 45, 3},
    {2310, 525, 45, 45, 3},
    {2700, 595, 70, 45, 4},
    {2850, 595, 70, 45, 4},
    {3000, 595, 70, 45, 4},
    {2770, 560, 40, 80, 2},
    {2920, 560, 40, 80, 2},
    {3070, 560, 40, 80, 2},
    {3400, 595, 45, 45, 2},
    {3550, 575, 45, 65, 2},
    {3700, 555, 45, 85, 2},
    {3850, 535, 45, 105, 2},
    {4000, 515, 45, 125, 2},
    {4200, 515, 250, 45, 1},
    {4250, 470, 45, 45, 3},
    {4400, 470, 45, 45, 3},
    {4500, 540, 45, 100, 2},
    {4650, 565, 45, 75, 2},
    {4800, 590, 45, 50, 2},
    {5100, 590, 150, 50, 1},
    {5300, 560, 150, 80, 1},
    {5500, 590, 150, 50, 1},
    {5750, 595, 45, 45, 3},
    {5900, 595, 45, 45, 3},
    {6200, 595, 45, 45, 2},
    {6400, 595, 45, 45, 2},
    {6600, 595, 45, 45, 2},
    {6900, 595, 80, 45, 4},
    {7100, 590, 200, 50, 1},
    {7450, 595, 45, 45, 3},
    {7800, 615, 25, 25, 5},
};

/**
 * @param out_obstacles Pointer to store the obstacle array
 * @param niveau The level number (1-3)
 * @goal Load the obstacle array for the specified level
 */
int charger_obstacles_niveau(obstacle** out_obstacles, int niveau) {
    switch(niveau) {
        case 1:
            *out_obstacles = obstacles_niveau1;
            return sizeof(obstacles_niveau1) / sizeof(obstacle);
        case 2:
            *out_obstacles = obstacles_niveau2;
            return sizeof(obstacles_niveau2) / sizeof(obstacle);
        case 3:
            *out_obstacles = obstacles_niveau3;
            return sizeof(obstacles_niveau3) / sizeof(obstacle);
        default:
            printf("Niveau invalide : %d\n", niveau);
            *out_obstacles = obstacles_niveau1;
            return sizeof(obstacles_niveau1) / sizeof(obstacle);
    }
}

/**
 * @param renderer The SDL renderer
 * @param type The obstacle type (0-5)
 * @goal Load and return the texture for the specified obstacle type
 */
SDL_Texture* charger_texture(SDL_Renderer* renderer, int type) {
    const char* paths[] = {
        "images/images_obstacles/barre.png",
        "images/images_obstacles/bloc.png",
        "images/images_obstacles/carre.png",
        "images/images_obstacles/triangle.png",
        "images/images_obstacles/trou.png",
        "images/images_obstacles/gagne.png"
    };
    if (type < 0 || type >= 6) {
        printf("Type de texture invalide : %d\n", type);
        return NULL;
    }
    SDL_Surface* surface = IMG_Load(paths[type]);
    if (!surface) {
        printf("Erreur chargement image %s : %s\n", paths[type], IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Erreur creation texture : %s\n", SDL_GetError());
    }
    return texture;
}