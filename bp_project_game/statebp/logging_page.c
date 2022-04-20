//
// Created by Hamidreza on 2/4/22.
//
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "function.h"

//this function returns the index of username in the array users[] and -1 if quit button was pushed
int logging_page(TTF_Font * font3,TTF_Font * font4,
                 SDL_Renderer *sdlRenderer,
                 SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position, char username[],struct user users[], int * number_of_users){

    //
    //initialization
    SDL_Surface * username_surface = TTF_RenderText_Solid(font4,username,red);
    SDL_Texture * username_texture = SDL_CreateTextureFromSurface(sdlRenderer,username_surface);
    SDL_Surface * usr_surface = TTF_RenderText_Solid(font4,"enter username",red);
    SDL_Texture * usr_texture = SDL_CreateTextureFromSurface(sdlRenderer,usr_surface);
    SDL_Surface * background_surface = IMG_Load("log.jpeg");
    SDL_Texture * background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    //position
    SDL_Rect username_position = {500,450, (int)strlen(username)*10,50};
    SDL_Rect usr_position = {600,400, 200,30};
    //
    SDL_Event event;
    bool quit = false;
    while (!quit){
        //state BP header
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        //images
        SDL_RenderCopy(sdlRenderer,background_texture,NULL,NULL);
        //
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);

        //logging
        boxColor(sdlRenderer, 500, 450, 900, 500, 0x44ffffff);
        SDL_RenderCopy(sdlRenderer,username_texture,NULL,&username_position);
        SDL_RenderCopy(sdlRenderer,usr_texture,NULL,&usr_position);

        //

        //
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        //shall exit
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    return -1;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_DELETE) {
                        if (strlen(username) == 0){
                            break;
                        }
                        username[strlen(username)-1] = '\0';
                        username_surface = TTF_RenderText_Solid(font4,username,red);
                        username_texture = SDL_CreateTextureFromSurface(sdlRenderer,username_surface);
                        username_position.w = (int)strlen(username)*10;
                        break;
                    } else if (event.key.keysym.sym == SDLK_RETURN) {
                        quit = true;
                        break;
                    } else {
                        username[strlen(username)] = (char)event.key.keysym.sym;
                        if (username[strlen(username)-1] == ' ' || username[strlen(username)-1] == '\t'){
                            username[strlen(username)-1] = '\0';
                            break;
                        }
                        username_surface = TTF_RenderText_Solid(font4,username,red);
                        username_texture = SDL_CreateTextureFromSurface(sdlRenderer,username_surface);
                        username_position.w = (int)strlen(username)*10;
                        break;
                    }

            }
        }
    }

    //======================================
    //end and destroy
    SDL_DestroyTexture(username_texture);
    SDL_FreeSurface(username_surface);
    SDL_DestroyTexture(usr_texture);
    SDL_FreeSurface(usr_surface);
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);
    //================================================
    //
    int index_of_username = -1;
    FILE * fptr = fopen("usernames.txt","r");
    memset(users[*number_of_users].username,'\0',100);
    while( fscanf(fptr, "%s%d%*c", users[*number_of_users].username,&users[*number_of_users].coin) != EOF ){
        if (!strcmp(username,users[*number_of_users].username)){
            index_of_username = *number_of_users;
        }
        (*number_of_users)++;
        memset(users[*number_of_users].username,'\0',100);
    }
    if (index_of_username == -1){
        users[*number_of_users].coin = 0;
        for (int i = 0; i < strlen(username); ++i) {
            users[*number_of_users].username[i] = username[i];
        }
        index_of_username = *number_of_users;
        (*number_of_users)++;
    }
    fclose(fptr);
    return index_of_username;
}
