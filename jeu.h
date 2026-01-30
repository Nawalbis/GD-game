#ifndef JEU_H
#define JEU_H
#include</opt/homebrew/include/SDL2/SDL_image.h>

//scrolling du background (coordonnées, repeter le fond deux fois en horizontal le long du jeu, definir une vitesse)

//boucle reliant le cube, les obstacles et le fond
typedef struct {
    SDL_Texture* texture;
    int x;
    int y;
    int w;
    int h;
}fond;

void init_fond(fond * bg1, fond * bg2, SDL_Texture* bg_texture);

void afficher_fond(SDL_Renderer* renderer, fond * bg);

void maj_affichage_bg(fond *bg1, fond *bg2);


#endif

