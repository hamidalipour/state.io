//
// Created by Hamidreza on 2/3/22.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include "function.h"

//

int message_page(TTF_Font * font3, TTF_Font * font4,
                 SDL_Renderer *sdlRenderer, int game_status, int player_id){
    //music
    if (game_status == 1){
        if (player_id == 2){
            Mix_PlayMusic(jumong_win_play_list[rand()%2],0);
        } else{
            Mix_PlayMusic(other_win_play_list[0],0);
        }
    } else{
        if (player_id == 2){
            Mix_PlayMusic(jumong_defeat_play_list[rand()%2],0);
        } else{
            Mix_PlayMusic(other_defeat_play_list[rand()%2],0);
        }
    }
    //image initialization
    SDL_Surface * background_surface;
    SDL_Texture * background_texture;
    SDL_Surface * message_surface;
    SDL_Texture * message_texture;
    SDL_Rect message_position = {300,550,800,60};
    if (player_id == 0){
        if (game_status == 0){
            background_surface = IMG_Load("napeleon_lose.jpeg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You'd better get out of my sight", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }else {
            background_surface = IMG_Load("napeleon_win.jpeg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
            message_surface = TTF_RenderText_Solid(font4,"Well done! I tip my hat to you", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }
    }
    if (player_id == 1){
        if (game_status == 0){
            background_surface = IMG_Load("caesar_lose.jpg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You are a disgrace to roman empire", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }else {
            background_surface = IMG_Load("caesar_win.jpeg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You are a man of courage.Zeus be with you", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }
    }
    if (player_id == 2){
        if (game_status == 0){
            background_surface = IMG_Load("jumong_lose.jpg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You let me down.No word can express my sadness", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }else {
            background_surface = IMG_Load("jumong_win.jpeg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You fought bravely and won! I admire your courage", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }
    }
    if (player_id == 3){
        if (game_status == 0){
            background_surface = IMG_Load("hitler_lose.jpg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
            message_surface = TTF_RenderText_Solid(font4,"You have got my troops kiled!consider yourself dead", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }else {
            background_surface = IMG_Load("hitler_win.webp");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
            message_surface = TTF_RenderText_Solid(font4,"Heil you!Reish is so proud of you", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }
    }
    if (player_id == 4){
        if (game_status == 0){
            background_surface = IMG_Load("stalin_lose.jpg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
            message_surface = TTF_RenderText_Solid(font4,"I don't really know what to say. you truly let me down", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
            message_position.x = 200;
            message_position.w = 1000;
        }else {
            background_surface = IMG_Load("stalin_win.jpeg");
            background_texture = SDL_CreateTextureFromSurface(sdlRenderer, background_surface);
            message_surface = TTF_RenderText_Solid(font4,"Well done!You have done me proud", red);
            message_texture = SDL_CreateTextureFromSurface(sdlRenderer, message_surface);
        }
    }
    //initia;ization of messages
    SDL_Surface * status_surface;
    SDL_Texture * status_texture;
    if (game_status == 1){
        status_surface = TTF_RenderText_Solid(font4,"you have won",red);
        status_texture = SDL_CreateTextureFromSurface(sdlRenderer,status_surface);
    } else {
        status_surface = TTF_RenderText_Solid(font4,"you have been defeated",red);
        status_texture = SDL_CreateTextureFromSurface(sdlRenderer,status_surface);
    }
    SDL_Surface * next_surface = TTF_RenderText_Solid(font3,"next game",white);
    SDL_Texture * next_texture = SDL_CreateTextureFromSurface(sdlRenderer,next_surface);

    //position
    SDL_Rect status_position = {550,700,300,30};
    SDL_Rect next_position = {1000,700,300,50};
    //

    SDL_Event event;
    bool quit = false;
    int output = -1;
    while (!quit){
        //music
        if (Mix_PlayingMusic() == 0){
            if (game_status == 1){
                if (player_id == 2){
                    Mix_PlayMusic(jumong_win_play_list[rand()%2],0);
                } else{
                    Mix_PlayMusic(other_win_play_list[0],0);
                }
            } else{
                if (player_id == 2){
                    Mix_PlayMusic(jumong_defeat_play_list[rand()%2],0);
                } else{
                    Mix_PlayMusic(other_defeat_play_list[rand()%2],0);
                }
            }
        }
        //state BP header
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        //images
        SDL_RenderCopy(sdlRenderer,background_texture,NULL,NULL);
        //messages
        SDL_RenderCopy(sdlRenderer,status_texture,NULL,&status_position);
        SDL_RenderCopy(sdlRenderer,message_texture,NULL,&message_position);
        SDL_RenderCopy(sdlRenderer,next_texture,NULL,&next_position);
        //

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
                    if (if_in_text(next_position,event.button.x,event.button.y)){
                        output = 0;
                        quit = true;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (if_in_text(next_position,event.motion.x,event.motion.y)){
                        next_surface = TTF_RenderText_Solid(font3,"next game", red);
                        next_texture = SDL_CreateTextureFromSurface(sdlRenderer, next_surface);
                    } else{
                        next_surface = TTF_RenderText_Solid(font3,"next game", white);
                        next_texture = SDL_CreateTextureFromSurface(sdlRenderer, next_surface);
                    }
                    break;
            }
        }
    }

    //======================================
    Mix_PlayMusic(main_play_list[rand()%3],0);
    //end and destroy
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);
    SDL_DestroyTexture(status_texture);
    SDL_FreeSurface(status_surface);
    SDL_DestroyTexture(message_texture);
    SDL_FreeSurface(message_surface);
    SDL_DestroyTexture(next_texture);
    SDL_FreeSurface(next_surface);
    return output;

}