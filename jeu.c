#include "jeu.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define SCROLL_SPEED 7

/**
 * @param bg1 Pointer to the first background structure
 * @param bg2 Pointer to the second background structure
 * @param bg_texture The background texture to use
 * @goal Initialize two background structures for seamless scrolling
 */
void init_fond(fond * bg1, fond * bg2, SDL_Texture* bg_texture){
    bg1->texture = bg_texture;
    bg1->x=0;
    bg1->y=0;
    bg1->w=1000;
    bg1->h=700;
    bg2->texture = bg_texture;
    bg2->x = WINDOW_WIDTH;
    bg2->y = 0;
    bg2->w = 1000;
    bg2->h = 700;
}

/**
 * @param renderer The SDL renderer
 * @param bg Pointer to the background structure to display
 * @goal Render the background texture on screen
 */
void afficher_fond(SDL_Renderer* renderer, fond * bg){
    SDL_Rect dest = {bg->x, bg->y, bg->w, bg->h};
    SDL_RenderCopy(renderer, bg->texture, NULL, &dest);
}

/**
 * @param bg1 Pointer to the first background structure
 * @param bg2 Pointer to the second background structure
 * @goal Update background positions for scrolling effect and loop them
 */
void maj_affichage_bg(fond *bg1, fond *bg2){
    bg1->x -= SCROLL_SPEED;
    bg2->x -= SCROLL_SPEED;
    if(bg1->x + WINDOW_WIDTH <= 0){
        bg1->x=bg2->x + WINDOW_WIDTH;
    }
    if(bg2->x + WINDOW_WIDTH <= 0){
        bg2->x=bg1->x + WINDOW_WIDTH;
    }
}
