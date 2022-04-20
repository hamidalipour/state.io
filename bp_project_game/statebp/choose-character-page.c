//
// Created by Hamidreza on 1/26/22.
//

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include "function.h"
//
int if_on_picture(SDL_Rect picture_position, int x, int y){
    if(x > picture_position.x && x < picture_position.x + picture_position.w && y > picture_position.y && y < picture_position.y + picture_position.h)
        return 1;
    return 0;
}
//if quit button is pushed this function returns -1 otherwise it returns the id of player which was chosen
int choose_character_page(TTF_Font * font3, TTF_Font * font4,
                           SDL_Renderer *sdlRenderer,
                           SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position, struct Character * dictators
                ,char username[], int coin){
    //image initialization
    SDL_Rect napeleon_image_position = {150,300,200,200};
    SDL_Rect caesar_image_position = {375,300,200,200};
    SDL_Rect jumong_image_position = {600,300,200,200};
    SDL_Rect hitler_image_position = {825,300,200,200};
    SDL_Rect stalin_image_position = {1050,300,200,200};
    //names initialization
    SDL_Rect napeleon_name_position = {150,500,200,40};
    SDL_Rect caesar_name_position = {375,500,200,40};
    SDL_Rect jumong_name_position = {600,500,200,40};
    SDL_Rect hitler_name_position = {825,500,200,40};
    SDL_Rect stalin_name_position = {1050,500,200,40};
    //
    SDL_Surface * qustion_surface = TTF_RenderText_Solid(font3,"choose your character", white);
    SDL_Texture * question_texture = SDL_CreateTextureFromSurface(sdlRenderer, qustion_surface);
    SDL_Rect question_position = {350,150,700,50};
    SDL_Surface * lead_surface = TTF_RenderText_Solid(font3,"leadership", white);
    SDL_Texture * lead_texture = SDL_CreateTextureFromSurface(sdlRenderer, lead_surface);
    SDL_Rect lead_position = {1000,700,300,50};
    SDL_Surface * user_surface = TTF_RenderText_Solid(font4,username, white);
    SDL_Texture * user_texture = SDL_CreateTextureFromSurface(sdlRenderer, user_surface);
    SDL_Rect user_position = {30,30, strlen(username)*12,40};
    char c[20];
    sprintf(c,"coin: %d",coin);
    SDL_Surface * coin_surface = TTF_RenderText_Solid(font4,c, white);
    SDL_Texture * coin_texture = SDL_CreateTextureFromSurface(sdlRenderer, coin_surface);
    SDL_Rect coin_position = {1100,30, strlen(c)*12,40};
    //
    SDL_Event event;
    bool quit = false;
    int output = -1;
    while (!quit){
        //music
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(main_play_list[rand()%3],0);
        }
        //state BP header
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);
        //images
        SDL_RenderCopy(sdlRenderer, dictators[0].image_texture, NULL, &napeleon_image_position);
        SDL_RenderCopy(sdlRenderer, dictators[1].image_texture, NULL, &caesar_image_position);
        SDL_RenderCopy(sdlRenderer, dictators[2].image_texture, NULL, &jumong_image_position);
        SDL_RenderCopy(sdlRenderer, dictators[3].image_texture, NULL, &hitler_image_position);
        SDL_RenderCopy(sdlRenderer, dictators[4].image_texture, NULL, &stalin_image_position);
        //names
        SDL_RenderCopy(sdlRenderer, dictators[0].name_tuxture, NULL, &napeleon_name_position);
        SDL_RenderCopy(sdlRenderer, dictators[1].name_tuxture, NULL, &caesar_name_position);
        SDL_RenderCopy(sdlRenderer, dictators[2].name_tuxture, NULL, &jumong_name_position);
        SDL_RenderCopy(sdlRenderer, dictators[3].name_tuxture, NULL, &hitler_name_position);
        SDL_RenderCopy(sdlRenderer, dictators[4].name_tuxture, NULL, &stalin_name_position);
        //
        SDL_RenderCopy(sdlRenderer, question_texture, NULL, &question_position);
        SDL_RenderCopy(sdlRenderer, lead_texture, NULL, &lead_position);
        SDL_RenderCopy(sdlRenderer, user_texture, NULL, &user_position);
        SDL_RenderCopy(sdlRenderer, coin_texture, NULL, &coin_position);
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
                    if (if_on_picture(napeleon_image_position, event.button.x, event.button.y)) {
                        output = 0;
                        quit = true;
                    }
                    if (if_on_picture(caesar_image_position, event.button.x, event.button.y)) {
                        output = 1;
                        quit = true;
                    }
                    if (if_on_picture(jumong_image_position, event.button.x, event.button.y)) {
                        output = 2;
                        quit = true;
                    }
                    if (if_on_picture(hitler_image_position, event.button.x, event.button.y)) {
                        output = 3;
                        quit = true;
                    }
                    if (if_on_picture(stalin_image_position, event.button.x, event.button.y)) {
                        output = 4;
                        quit = true;
                    }
                    if (if_in_text(lead_position,event.button.x,event.button.y)){
                        output = -2;
                        quit = true;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (if_in_text(lead_position,event.motion.x,event.motion.y)){
                        lead_surface = TTF_RenderText_Solid(font3,"leadership", red);
                        lead_texture = SDL_CreateTextureFromSurface(sdlRenderer, lead_surface);
                    } else{
                        lead_surface = TTF_RenderText_Solid(font3,"leadership", white);
                        lead_texture = SDL_CreateTextureFromSurface(sdlRenderer, lead_surface);
                    }
                    break;
            }
        }
    }

    //======================================
    //end and destroy
    SDL_DestroyTexture(question_texture);
    SDL_FreeSurface(qustion_surface);
    SDL_DestroyTexture(lead_texture);
    SDL_FreeSurface(lead_surface);
    SDL_DestroyTexture(user_texture);
    SDL_FreeSurface(user_surface);
    SDL_DestroyTexture(coin_texture);
    SDL_FreeSurface(coin_surface);
    return output;
}