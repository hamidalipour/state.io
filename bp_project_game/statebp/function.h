//
// Created by Hamidreza on 1/26/22.
//

#ifndef STATEBP_FUNCTION_H
#define STATEBP_FUNCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct Character{
    SDL_Surface * image;
    SDL_Texture * image_texture;
    SDL_Surface * name;
    SDL_Texture * name_tuxture;
};
struct Military_base{
    Uint32 color;
    int x;
    int y;
    int number_of_soldiers;
    int limitation_of_soldiers;
    int soldier_producing_speed;
    bool being_attacked;
    bool activated;
};
struct region{
    int x1;
    int y1;
    int x2;
    int y2;
};
struct soldier{
    int x;
    int y;
    bool in_destination;
    bool killed;
};
struct march{
    bool finished;
    int destination_x;
    int destination_y;
    int number_of_soldiers;
    int number_of_killed_soldiers;
    int number_of_soldiers_in_destination;
    int number_of_soldiers_to_move;
    struct soldier * soldiers;
    int id;
    int destination_place[2];
};
struct move{
    int x;
    int y;
};
struct march_from_to{
    int i1;
    int j1;
    int i2;
    int j2;
};
struct number{
    SDL_Surface * number_surface;
    SDL_Texture * number_texture;
    SDL_Rect number_position;
};
struct user{
    char username[100];
    int coin;
};
struct potion{
    int x;
    int y;
    //a potion is activated the first time it appears on the map and when a user finished using it it is diactivated again
    bool activated;
    bool being_used;
    int time;
    int id;
};
static const int SCREEN_WIDTH = 1400;
static const int SCREEN_HEIGHT = 800;
static const int FPS = 60;
static SDL_Color white = { 255, 255, 255};
static SDL_Color red = {255,0,0,0};
static SDL_Color green = {0,255,0,0};
static SDL_Color black = {0,0,0,0};
static SDL_Color purple = {255,0,255,0};
static int percent = 0;
static int counter = 0;
static char loding_percent[6];
static struct region regions[8] = {{466,216,564,434},
                                   {596,336,734,434},
                                   {886,316,1054,484},
                                   {596,216,754,304},
                                   {766,146,1184,284},
                                   {766,316,854,484},
                                   {466,466,734,634},
                                   {916,516,1134,734}};
//military_base_colors from 0 to 4 stands for each of the characters. the 5ht index to 7th stands for empty base and 8th for when the mouse clicks on a base
static Uint32 military_base_colors[9] = {0x88ff0000,
                                         0x8840ffff,
                                         0x880040c0,
                                         0x88808080,
                                         0x880000ff,
                                         0x88ffffff,
                                         0x88ffffff,
                                         0x88ffffff,
                                         0x88ff00ff};

//=====================================================================================
//music
Mix_Music * main_play_list[3];
Mix_Music * jumong_defeat_play_list[2];
Mix_Music * jumong_win_play_list[2];
Mix_Music * other_defeat_play_list[2];
Mix_Music * other_win_play_list[1];
Mix_Music * jumong_game_play_list[5];
Mix_Music * napeleon_game_play_list[2];
Mix_Music * caesar_game_play_list[4];
Mix_Music * hitler_game_play_list[2];
Mix_Music * stalin_game_play_list[3];
//======================================================================================
int first_page(TTF_Font * font1, TTF_Font * font2, TTF_Font * font3, SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

int choose_character_page(TTF_Font * font3, TTF_Font * font4,
                           SDL_Renderer *sdlRenderer,
                           SDL_Texture * state_texture, SDL_Texture * BP_texture
                           ,SDL_Rect state_position, SDL_Rect BP_position,struct Character * dictators
                                   ,char username[], int coin);
int game_page(TTF_Font * font3, SDL_Window *sdlWindow,
               SDL_Renderer *sdlRenderer,
               SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position,struct Character * dictators,int number_of_military_base[8]
                ,int player_id, struct Military_base ** military_bases);
int generating_board_page(TTF_Font * font3, SDL_Window *sdlWindow,
              SDL_Renderer *sdlRenderer,
              SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position,int number_of_military_base[8]
        ,int player_id,struct Military_base** military_bases);
int message_page(TTF_Font * font3, TTF_Font * font4,
                 SDL_Renderer *sdlRenderer, int game_status, int player_id);
int if_in_text(SDL_Rect position, int x, int y);
int logging_page(TTF_Font * font3,TTF_Font * font4,
                          SDL_Renderer *sdlRenderer,
                          SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position,char username[], struct user users[],int * number_of_users);
int leadership_page(TTF_Font * font3,TTF_Font * font4,
                 SDL_Renderer *sdlRenderer,
                 SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position, struct user users[],int number_of_users);
#endif //STATEBP_FUNCTION_H
