//
// Created by Hamidreza on 2/4/22.
//
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "function.h"

int leadership_page(TTF_Font * font3,TTF_Font * font4,
                    SDL_Renderer *sdlRenderer,
                    SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position, struct user users[],int number_of_users){
    //

    SDL_Surface * back_surface = TTF_RenderText_Solid(font3,"back", white);
    SDL_Texture * back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);
    SDL_Surface * background_surface = IMG_Load("leadership.jpg");
    SDL_Texture * background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
    SDL_Rect back_position = {1000,700,200,50};
    //
    SDL_Event event;
    bool quit = false;
    int output = -1;
    SDL_Surface * username_surface;
    SDL_Texture * username_texture;
    SDL_Surface * coin_surface;
    SDL_Texture * coin_texture;
    while (!quit){
        //music
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(main_play_list[rand()%3],0);
        }
        //state BP header
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,background_texture,NULL,NULL);
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);
        //
        for (int i = 0; i < number_of_users; ++i) {
            username_surface = TTF_RenderText_Solid(font4,users[i].username,red);
            username_texture = SDL_CreateTextureFromSurface(sdlRenderer,username_surface);
            char c[10];
            sprintf(c,"%d",users[i].coin);
            coin_surface = TTF_RenderText_Solid(font4,c,red);
            coin_texture = SDL_CreateTextureFromSurface(sdlRenderer,coin_surface);
            SDL_Rect username_position = {50,100 + (i * 50), (int)strlen(users[i].username)*12,40};
            SDL_Rect coin_position = {350,100 + (i * 50), (int)strlen(c)*12,40};
            SDL_RenderCopy(sdlRenderer,username_texture,NULL,&username_position);
            SDL_RenderCopy(sdlRenderer,coin_texture,NULL,&coin_position);
        }
        //
        SDL_RenderCopy(sdlRenderer, back_texture, NULL, &back_position);
        //
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        //shall exit
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (if_in_text(back_position,event.button.x,event.button.y)){
                        output = 0;
                        quit = true;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (if_in_text(back_position,event.motion.x,event.motion.y)){
                        back_surface = TTF_RenderText_Solid(font3,"back", red);
                        back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);
                    } else{
                        back_surface = TTF_RenderText_Solid(font3,"back", white);
                        back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);
                    }
                    break;
            }
        }
    }

    //======================================
    //end and destroy
    SDL_DestroyTexture(back_texture);
    SDL_FreeSurface(back_surface);
    SDL_DestroyTexture(username_texture);
    SDL_FreeSurface(username_surface);
    SDL_DestroyTexture(coin_texture);
    SDL_FreeSurface(coin_surface);
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);
    return output;

}