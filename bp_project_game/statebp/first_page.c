//
// Created by Hamidreza on 1/26/22.
//


#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include "function.h"
//if quit button is pushed this function returns -1 otherwise it returns 0
int first_page(TTF_Font * font1, TTF_Font * font2, TTF_Font * font3, SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer){
    SDL_Surface * state_surface = TTF_RenderText_Solid(font1,"state", white);
    SDL_Surface * BP_surface = TTF_RenderText_Solid(font1,"BP",red);
    SDL_Surface * hamid_surface = TTF_RenderText_Solid(font2,"Developed By Hamidreza Alipour", white);
    SDL_Surface * loading_surface = TTF_RenderText_Solid(font3,"loading", white);
    SDL_Surface * image = IMG_Load("call-of-duty-black-ops-cover.jpeg");
    SDL_Texture * cod_texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_Texture * state_texture = SDL_CreateTextureFromSurface(sdlRenderer, state_surface);
    SDL_Texture * BP_texture = SDL_CreateTextureFromSurface(sdlRenderer, BP_surface);
    SDL_Texture * hamid_texture = SDL_CreateTextureFromSurface(sdlRenderer, hamid_surface);
    SDL_Texture * loading_texture = SDL_CreateTextureFromSurface(sdlRenderer, loading_surface);
    SDL_Surface * percent_surface;
    SDL_Texture * percent_texture;
    //==========================
    int output = 0;
    SDL_Event event;
    bool quit = false;
    while (!quit){
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        SDL_Rect state_position = {620,300,130,30};
        SDL_Rect BP_position = {760,300,40,30};
        SDL_Rect hamid_position = {500,650,400,40};
        SDL_Rect loading_position = {650,500,100,20};
        SDL_RenderCopy(sdlRenderer, cod_texture, NULL, NULL);
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);
        SDL_RenderCopy(sdlRenderer, loading_texture, NULL, &loading_position);
        SDL_RenderCopy(sdlRenderer, hamid_texture, NULL, &hamid_position);
        //loading
        SDL_Rect percent_position = {900,460,60,50};
        sprintf(loding_percent,"%d",percent);
        percent_surface = TTF_RenderText_Solid(font3, loding_percent, white);
        percent_texture = SDL_CreateTextureFromSurface(sdlRenderer, percent_surface);
        SDL_RenderCopy(sdlRenderer,percent_texture,NULL,&percent_position);
        boxColor(sdlRenderer, 500, 460, (percent*4)+500, 500, 0xffffffff);
        percent =counter/5;
        if(percent == 99) {
            SDL_Delay(3000);
            break;
        }
        //
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);

        //shall exit
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) {
                quit = true;
                output = -1;
            }
        }
        counter++;

    }
    //========================================
    //end and destroy
    SDL_DestroyTexture(BP_texture);
    SDL_DestroyTexture(hamid_texture);
    SDL_DestroyTexture(state_texture);
    SDL_DestroyTexture(percent_texture);
    SDL_DestroyTexture(loading_texture);
    SDL_FreeSurface(hamid_surface);
    SDL_FreeSurface(BP_surface);
    SDL_FreeSurface(state_surface);
    SDL_FreeSurface(loading_surface);
    SDL_FreeSurface(percent_surface);
    SDL_DestroyTexture(cod_texture);
    SDL_FreeSurface(image);
    return output;
}
