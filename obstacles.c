#include "obstacles.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// NIVEAU 1 - TRÈS FACILE : obstacles bien espacés, parfait pour screenshot
// Design : progression douce et claire, idéal pour montrer les mécaniques
static obstacle obstacles_niveau1[] = {
    // Introduction douce - premiers obstacles bien espacés
    {900, 595, 45, 45, 2},   // Premier carré
    
    {1300, 595, 45, 45, 3},  // Premier triangle
    
    // Petit trou facile
    {1700, 595, 80, 45, 4},  // Trou
    
    {1900, 595, 45, 45, 2},  // Carré après trou
    
    // Petite montée simple (2 blocs)
    {2300, 595, 45, 45, 1},  // Barre au sol
    {2300, 550, 45, 45, 2},  // Carré dessus
    
    {2700, 595, 45, 45, 3},  // Triangle
    
    // Bloc large stable
    {3100, 590, 150, 50, 1}, // Grand bloc
    
    {3500, 595, 45, 45, 2},  // Carré
    
    // Deuxième trou
    {3900, 595, 80, 45, 4},  // Trou
    
    {4100, 595, 45, 45, 2},  // Carré
    
    // Série de 3 carrés espacés (joli pour screenshot)
    {4500, 595, 45, 45, 2},
    {4800, 595, 45, 45, 2},
    {5100, 595, 45, 45, 2},
    
    // Petit escalier montant (3 marches)
    {5500, 595, 45, 45, 2},  // Marche 1
    {5650, 570, 45, 70, 2},  // Marche 2 (30px plus haut)
    {5800, 545, 45, 95, 2},  // Marche 3 (60px plus haut)
    
    // Grand bloc stable pour repos
    {6100, 590, 200, 50, 1}, // Très grand bloc
    
    {6500, 595, 45, 45, 3},  // Triangle
    
    // Dernière section simple
    {6900, 595, 45, 45, 2},  // Carré
    
    {7200, 590, 150, 50, 1}, // Bloc large
    
    {7500, 595, 45, 45, 3},  // Dernier triangle
    
    // Triangle de victoire - bien visible
    {7900, 615, 25, 25, 5},
};

// NIVEAU 2 - FACILE AUSSI : un peu plus d'obstacles mais toujours simple
// Design : rythme un peu plus soutenu, joli visuellement
static obstacle obstacles_niveau2[] = {
    // Début avec quelques obstacles
    {700, 595, 45, 45, 3},   // Triangle
    {900, 595, 45, 45, 2},   // Carré
    
    {1200, 595, 70, 45, 4},  // Petit trou
    
    {1400, 595, 45, 45, 2},  // Carré
    
    // Série de 2 blocs empilés (joli)
    {1800, 595, 45, 45, 1},  // Barre sol
    {1800, 550, 45, 45, 2},  // Carré dessus
    
    {2100, 595, 45, 45, 3},  // Triangle
    
    // Zone avec bloc large
    {2500, 590, 150, 50, 1}, // Bloc large
    
    {2800, 595, 45, 45, 2},  // Carré
    
    // Deux trous espacés
    {3200, 595, 70, 45, 4},  // Trou 1
    {3500, 595, 70, 45, 4},  // Trou 2
    
    // Plateformes entre les trous
    {3270, 560, 40, 80, 2},  // Petite plateforme
    {3570, 560, 40, 80, 2},  // Petite plateforme
    
    // Série jolie de 3 triangles
    {3900, 595, 45, 45, 3},
    {4100, 595, 45, 45, 3},
    {4300, 595, 45, 45, 3},
    
    // Escalier montant (4 marches)
    {4700, 595, 45, 45, 2},
    {4850, 575, 45, 65, 2},
    {5000, 555, 45, 85, 2},
    {5150, 535, 45, 105, 2},
    
    // Grande plateforme en hauteur
    {5350, 535, 200, 45, 1}, // Plateforme haute
    
    // Descente
    {5600, 560, 45, 80, 2},
    {5750, 585, 45, 55, 2},
    
    // Bloc large au sol
    {6000, 590, 150, 50, 1},
    
    {6300, 595, 45, 45, 3},  // Triangle
    
    // Série finale
    {6700, 595, 45, 45, 2},
    {6950, 595, 45, 45, 2},
    
    {7200, 590, 150, 50, 1}, // Dernier bloc large
    
    {7500, 595, 45, 45, 3},  // Dernier triangle
    
    // Triangle de victoire
    {7900, 615, 25, 25, 5},
};

// NIVEAU 3 - MOYEN : plus d'obstacles mais toujours jouable et esthétique
// Design : sections variées, visuellement intéressant pour screenshots
static obstacle obstacles_niveau3[] = {
    // Début dynamique
    {600, 595, 45, 45, 3},   // Triangle
    {750, 595, 45, 45, 3},   // Triangle
    
    {1000, 595, 60, 45, 4},  // Trou
    
    {1200, 595, 45, 45, 2},  // Carré
    
    // Petite tour (3 blocs)
    {1500, 595, 45, 45, 1},  // Sol
    {1500, 550, 45, 45, 1},  // +45px
    {1500, 505, 45, 45, 2},  // +90px
    
    {1750, 595, 60, 45, 4},  // Trou
    
    // Section avec blocs surélevés (joli visuellement)
    {2000, 570, 80, 70, 1},
    {2150, 570, 80, 70, 1},
    {2300, 570, 80, 70, 1},
    
    // Obstacles sur les blocs
    {2010, 525, 45, 45, 3},
    {2160, 525, 45, 45, 3},
    {2310, 525, 45, 45, 3},
    
    // Série de trous avec plateformes (section signature)
    {2700, 595, 70, 45, 4},  // Trou 1
    {2850, 595, 70, 45, 4},  // Trou 2
    {3000, 595, 70, 45, 4},  // Trou 3
    
    // Plateformes entre les trous
    {2770, 560, 40, 80, 2},
    {2920, 560, 40, 80, 2},
    {3070, 560, 40, 80, 2},
    
    // Escalier progressif (5 marches)
    {3400, 595, 45, 45, 2},
    {3550, 575, 45, 65, 2},
    {3700, 555, 45, 85, 2},
    {3850, 535, 45, 105, 2},
    {4000, 515, 45, 125, 2},
    
    // Grande plateforme haute
    {4200, 515, 250, 45, 1}, // Très grande plateforme
    
    // Obstacles sur la plateforme
    {4250, 470, 45, 45, 3},
    {4400, 470, 45, 45, 3},
    
    // Descente progressive
    {4500, 540, 45, 100, 2},
    {4650, 565, 45, 75, 2},
    {4800, 590, 45, 50, 2},
    
    // Zone de blocs larges
    {5100, 590, 150, 50, 1},
    {5300, 560, 150, 80, 1},
    {5500, 590, 150, 50, 1},
    
    // Quelques triangles
    {5750, 595, 45, 45, 3},
    {5900, 595, 45, 45, 3},
    
    // Section finale avec carrés
    {6200, 595, 45, 45, 2},
    {6400, 595, 45, 45, 2},
    {6600, 595, 45, 45, 2},
    
    // Dernier trou
    {6900, 595, 80, 45, 4},
    
    // Plateforme avant la fin
    {7100, 590, 200, 50, 1},
    
    {7450, 595, 45, 45, 3},  // Dernier triangle
    
    // Triangle de victoire
    {7800, 615, 25, 25, 5},
};

// Fonction pour charger les obstacles en fonction du niveau
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