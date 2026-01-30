#include "jeu.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

#define SCROLL_SPEED 7 //vitesse de defilement


//on met deux background avec un afficher au debut et l'autre non comme ca ca glisse et quand on est a -background_width pour un on le remet a gauche
//definir le: if (jeu == 1)  on est dans le game et le scroll peut commencer, le fond ne défilera pas tant qu'on est pas dans le bool true du jeu


void init_fond(fond * bg1, fond * bg2, SDL_Texture* bg_texture){
    //premiere fenetre : initialisée a 0, occupe la fenetre
    
    bg1->texture = bg_texture;
    bg1->x=0;
    bg1->y=0;
    bg1->w=1000;
    bg1->h=700;
    
    //deuxieme fenetre : initialisée à droite de la fenetre 

    bg2->texture = bg_texture;
    bg2->x = WINDOW_WIDTH;
    bg2->y = 0;
    bg2->w = 1000;
    bg2->h = 700;
}

void afficher_fond(SDL_Renderer* renderer, fond * bg){
    SDL_Rect dest = {bg->x, bg->y, bg->w, bg->h}; //afficher notre texture sur la fenetre
    SDL_RenderCopy(renderer, bg->texture, NULL, &dest);
}

void maj_affichage_bg(fond *bg1, fond *bg2){
    bg1->x -= SCROLL_SPEED; // on veut que le fond avance vers la gauche a une vitesse definie plus haut
    bg2->x -= SCROLL_SPEED;

    if(bg1->x + WINDOW_WIDTH <= 0){ // si le premier fond est a gauche de la fenetre (coin gauche pris comme reference pour la position, donc si fenetre <=0)
        bg1->x=bg2->x + WINDOW_WIDTH;//on ajoute au coin gauche, le fond 2 et la fenetre, pour passer a droite de l'ecran
    }
    if(bg2->x + WINDOW_WIDTH <= 0){ // pareil pour le fond 2
        bg2->x=bg1->x + WINDOW_WIDTH;
    }

    // SDL_RenderClear(renderer);
    // afficher_fond(renderer, bg1);
    // afficher_fond(renderer, bg2);
    // SDL_RenderPresent(renderer);
    
}



