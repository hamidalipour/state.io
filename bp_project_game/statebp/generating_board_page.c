//
// Created by Hamidreza on 2/2/22.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include "function.h"

int if_in_text(SDL_Rect position,int x,int y){
    if (x > position.x && x < position.x + position.w && y > position.y && y < position.y + position.h){
        return 1;
    }
    return 0;
}
//
int is_valid_new_base(struct Military_base ** military_bases, int i, int j){
    for(int k = 0; k < j; k++){
        if((military_bases[i][j].x - military_bases[i][k].x) * (military_bases[i][j].x - military_bases[i][k].x) + (military_bases[i][j].y - military_bases[i][k].y) * (military_bases[i][j].y - military_bases[i][k].y) < 1500)
            return 0;
    }
    return 1;
}
//
void map1(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[0][0].x = 466;military_bases[0][0].y = 431; military_bases[0][1].x = 497;military_bases[0][1].y = 219; military_bases[0][2].x = 509;military_bases[0][2].y = 335;
    military_bases[1][0].x = 721;military_bases[1][0].y = 422; military_bases[1][1].x = 617;military_bases[1][1].y = 387;military_bases[1][2].x = 712;military_bases[1][2].y = 350;
    military_bases[2][0].x = 960;military_bases[2][0].y = 433;military_bases[2][1].x = 891;military_bases[2][1].y = 480;military_bases[2][2].x = 900;military_bases[2][2].y = 407;
    military_bases[3][0].x = 610;military_bases[3][0].y = 244;military_bases[3][1].x = 675;military_bases[3][1].y = 279;military_bases[3][2].x = 642;military_bases[3][2].y = 221;
    military_bases[4][0].x = 1071;military_bases[4][0].y = 177;military_bases[4][1].x = 920;military_bases[4][1].y = 259;military_bases[4][2].x = 851;military_bases[4][2].y = 148;
    military_bases[5][0].x = 798;military_bases[5][0].y = 400;military_bases[5][1].x = 786;military_bases[5][1].y = 467;
    military_bases[6][0].x = 720;military_bases[6][0].y = 555;military_bases[6][1].x = 494;military_bases[6][1].y = 547;military_bases[6][2].x = 705;military_bases[6][2].y = 621;military_bases[6][3].x = 576;military_bases[6][3].y = 560;
    military_bases[7][0].x = 977;military_bases[7][0].y = 526;military_bases[7][1].x = 1042;military_bases[7][1].y = 648;military_bases[7][2].x = 1081;military_bases[7][2].y = 578;military_bases[7][3].x = 1017;military_bases[7][3].y = 618;
}
//
void map2(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[0][0].x = 481;military_bases[0][0].y = 238; military_bases[0][1].x = 480;military_bases[0][1].y = 386; military_bases[0][2].x = 555;military_bases[0][2].y = 244;
    military_bases[1][0].x = 698;military_bases[1][0].y = 415; military_bases[1][1].x = 646;military_bases[1][1].y = 401;military_bases[1][2].x = 675;military_bases[1][2].y = 366;
    military_bases[2][0].x = 920;military_bases[2][0].y = 369;military_bases[2][1].x = 1020;military_bases[2][1].y = 338;military_bases[2][2].x = 973;military_bases[2][2].y = 386;
    military_bases[3][0].x = 661;military_bases[3][0].y = 250;military_bases[3][1].x = 639;military_bases[3][1].y = 288;military_bases[3][2].x = 616;military_bases[3][2].y = 244;
    military_bases[4][0].x = 1064;military_bases[4][0].y = 280;military_bases[4][1].x = 1136;military_bases[4][1].y = 240;military_bases[4][2].x = 980;military_bases[4][2].y = 241;
    military_bases[5][0].x = 811;military_bases[5][0].y = 386;military_bases[5][1].x = 799;military_bases[5][1].y = 335;
    military_bases[6][0].x = 511;military_bases[6][0].y = 615;military_bases[6][1].x = 605;military_bases[6][1].y = 490;military_bases[6][2].x = 661;military_bases[6][2].y = 616;military_bases[6][3].x = 715;military_bases[6][3].y = 532;
    military_bases[7][0].x = 963;military_bases[7][0].y = 653;military_bases[7][1].x = 1062;military_bases[7][1].y = 711;military_bases[7][2].x = 947;military_bases[7][2].y = 708;military_bases[7][3].x = 1119;military_bases[7][3].y = 666;
}
//
void map3(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[3][0].x = 619;military_bases[3][0].y = 500;
    military_bases[4][0].x = 800;military_bases[4][0].y = 400;military_bases[4][1].x = 875;military_bases[4][1].y = 146;
    military_bases[4][2].x = 600;military_bases[4][2].y = 200;military_bases[4][3].x = 1037;military_bases[4][3].y = 170;
    military_bases[4][4].x = 650;military_bases[4][4].y = 235;military_bases[4][5].x = 860;military_bases[4][5].y = 250;
    military_bases[4][6].x = 900;military_bases[4][6].y = 235;military_bases[4][7].x = 620;military_bases[4][7].y = 300;
    military_bases[4][8].x = 1000;military_bases[4][8].y = 235;military_bases[4][9].x = 1100;military_bases[4][9].y = 300;

}
//
void map4(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[0][0].x = 481;military_bases[0][0].y = 385; military_bases[0][1].x = 509;military_bases[0][1].y = 279;
    military_bases[1][0].x = 726;military_bases[1][0].y = 423; military_bases[1][1].x = 619;military_bases[1][1].y = 371;
    military_bases[2][0].x = 990;military_bases[2][0].y = 464;military_bases[2][1].x = 977;military_bases[2][1].y = 377;
    military_bases[3][0].x = 703;military_bases[3][0].y = 228;military_bases[3][1].x = 663;military_bases[3][1].y = 243;
    military_bases[4][0].x = 813;military_bases[4][0].y = 265;military_bases[4][1].x = 1066;military_bases[4][1].y = 230;
    military_bases[5][0].x = 831;military_bases[5][0].y = 405;military_bases[5][1].x = 843;military_bases[5][1].y = 329;
    military_bases[6][0].x = 671;military_bases[6][0].y = 513;military_bases[6][1].x = 587;military_bases[6][1].y = 538;military_bases[6][2].x = 613;military_bases[6][2].y = 487;military_bases[6][3].x = 583;military_bases[6][3].y = 599;
    military_bases[7][0].x = 1077;military_bases[7][0].y = 625;military_bases[7][1].x = 1001;military_bases[7][1].y = 593;military_bases[7][2].x = 955;military_bases[7][2].y = 599;military_bases[7][3].x = 962;military_bases[7][3].y = 668;
}
//
void map5(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[0][0].x = 481;military_bases[0][0].y = 258; military_bases[0][1].x = 507;military_bases[0][1].y = 413;
    military_bases[1][0].x = 721;military_bases[1][0].y = 408; military_bases[1][1].x = 663;military_bases[1][1].y = 426;
    military_bases[2][0].x = 920;military_bases[2][0].y = 467;military_bases[2][1].x = 934;military_bases[2][1].y = 420;
    military_bases[3][0].x = 596;military_bases[3][0].y = 222;military_bases[3][1].x = 741;military_bases[3][1].y = 255;
    military_bases[4][0].x = 1004;military_bases[4][0].y = 186;military_bases[4][1].x = 1128;military_bases[4][1].y = 176;
    military_bases[5][0].x = 839;military_bases[5][0].y = 400;
    military_bases[6][0].x = 600;military_bases[6][0].y = 610;military_bases[6][1].x = 608;military_bases[6][1].y = 479;military_bases[6][2].x = 559;military_bases[6][2].y = 492;
    military_bases[7][0].x = 1056;military_bases[7][0].y = 625;military_bases[7][1].x = 1043;military_bases[7][1].y = 533;military_bases[7][2].x = 966;military_bases[7][2].y = 648;
}
//
void map6(struct Military_base** military_bases, int number_of_military_base[]){
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
        }
    }
    military_bases[0][0].x = 481;military_bases[0][0].y = 304;
    military_bases[1][0].x = 634;military_bases[1][0].y = 354;
    military_bases[2][0].x = 1012;military_bases[2][0].y = 465;
    military_bases[3][0].x = 684;military_bases[3][0].y = 282;
    military_bases[4][0].x = 1172;military_bases[4][0].y = 179;
    military_bases[5][0].x = 851;military_bases[5][0].y = 341;
    military_bases[6][0].x = 675;military_bases[6][0].y = 508;
    military_bases[7][0].x = 1040;military_bases[7][0].y = 652;
}
//
void generate_random_military_base(struct Military_base ** military_bases, int i, int j){
    military_bases[i][j].x = rand()%(regions[i].x2 - regions[i].x1) + regions[i].x1;
    military_bases[i][j].y = rand()%(regions[i].y2 - regions[i].y1) + regions[i].y1;
}

//if quit button is pushed this function returns -1 otherwise it returns 0
int generating_board_page(TTF_Font * font3, SDL_Window *sdlWindow,
                          SDL_Renderer *sdlRenderer,
                          SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position,int number_of_military_base[8]
        ,int player_id, struct Military_base** military_bases){

    //text_initialization
    SDL_Surface * random_surface = TTF_RenderText_Solid(font3,"generate random map", white);
    SDL_Texture * random_texture = SDL_CreateTextureFromSurface(sdlRenderer, random_surface);
    SDL_Surface * map_surface = TTF_RenderText_Solid(font3,"choose one of the maps below", white);
    SDL_Texture * map_texture = SDL_CreateTextureFromSurface(sdlRenderer, map_surface);
    //image initialization
    SDL_Surface * map1_surface = IMG_Load("map1.png");
    SDL_Texture * map1_texture = SDL_CreateTextureFromSurface(sdlRenderer, map1_surface);
    SDL_Surface * map2_surface = IMG_Load("map2.png");
    SDL_Texture * map2_texture = SDL_CreateTextureFromSurface(sdlRenderer, map2_surface);
    SDL_Surface * map3_surface = IMG_Load("map3.png");
    SDL_Texture * map3_texture = SDL_CreateTextureFromSurface(sdlRenderer, map3_surface);
    SDL_Surface * map4_surface = IMG_Load("map4.png");
    SDL_Texture * map4_texture = SDL_CreateTextureFromSurface(sdlRenderer, map4_surface);
    SDL_Surface * map5_surface = IMG_Load("map5.png");
    SDL_Texture * map5_texture = SDL_CreateTextureFromSurface(sdlRenderer, map5_surface);
    SDL_Surface * map6_surface = IMG_Load("map6.png");
    SDL_Texture * map6_texture = SDL_CreateTextureFromSurface(sdlRenderer, map6_surface);
    //position
    SDL_Rect random_position = {950,700,400,50};
    SDL_Rect map_position = {100,100,1200,50};

    SDL_Rect map1_position = {50,200,300,200};
    SDL_Rect map2_position = {550,200,300,200};
    SDL_Rect map3_position = {1050,200,300,200};
    SDL_Rect map4_position = {50,430,300,200};
    SDL_Rect map5_position = {550,430,300,200};
    SDL_Rect map6_position = {1050,430,300,200};
    //
    //

    //
    SDL_Event event;
    bool quit = false;
    bool random_generate = false;
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
        //choose message
        SDL_RenderCopy(sdlRenderer,map_texture,NULL,&map_position);
        //images
        SDL_RenderCopy(sdlRenderer,map1_texture,NULL,&map1_position);
        SDL_RenderCopy(sdlRenderer,map2_texture,NULL,&map2_position);
        SDL_RenderCopy(sdlRenderer,map3_texture,NULL,&map3_position);
        SDL_RenderCopy(sdlRenderer,map4_texture,NULL,&map4_position);
        SDL_RenderCopy(sdlRenderer,map5_texture,NULL,&map5_position);
        SDL_RenderCopy(sdlRenderer,map6_texture,NULL,&map6_position);
        //random
        SDL_RenderCopy(sdlRenderer,random_texture,NULL,&random_position);
        //
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        //shall exit
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    return -1;
                case SDL_MOUSEBUTTONDOWN:
                    if (if_in_text(random_position,event.button.x,event.button.y)){
                        quit = true;
                        random_generate = true;
                    }
                    if (if_in_text(map1_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 3;number_of_military_base[1] = 3;number_of_military_base[2] = 3;number_of_military_base[3] = 3;number_of_military_base[4] = 3;number_of_military_base[5] = 2;number_of_military_base[6] = 4;number_of_military_base[7] = 4;
                        map1(military_bases,number_of_military_base);
                    }
                    if (if_in_text(map2_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 3;number_of_military_base[1] = 3;number_of_military_base[2] = 3;number_of_military_base[3] = 3;number_of_military_base[4] = 3;number_of_military_base[5] = 2;number_of_military_base[6] = 4;number_of_military_base[7] = 4;
                        map2(military_bases,number_of_military_base);
                    }
                    if (if_in_text(map3_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 0;number_of_military_base[1] = 0;number_of_military_base[2] = 0;number_of_military_base[3] = 1;number_of_military_base[4] = 10;number_of_military_base[5] = 0;number_of_military_base[6] = 0;number_of_military_base[7] = 0;
                        map3(military_bases,number_of_military_base);
                    }
                    if (if_in_text(map4_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 2;number_of_military_base[1] = 2;number_of_military_base[2] = 2;number_of_military_base[3] = 2;number_of_military_base[4] = 2;number_of_military_base[5] = 2;number_of_military_base[6] = 4;number_of_military_base[7] = 4;
                        map4(military_bases,number_of_military_base);
                    }
                    if (if_in_text(map5_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 2;number_of_military_base[1] = 2;number_of_military_base[2] = 2;number_of_military_base[3] = 2;number_of_military_base[4] = 2;number_of_military_base[5] = 1;number_of_military_base[6] = 3;number_of_military_base[7] = 3;
                        map5(military_bases,number_of_military_base);
                    }
                    if (if_in_text(map6_position,event.button.x,event.button.y)){
                        quit = true;
                        number_of_military_base[0] = 1;number_of_military_base[1] = 1;number_of_military_base[2] = 1;number_of_military_base[3] = 1;number_of_military_base[4] = 1;number_of_military_base[5] = 1;number_of_military_base[6] = 1;number_of_military_base[7] = 1;
                        map6(military_bases,number_of_military_base);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (if_in_text(random_position,event.motion.x,event.motion.y)){
                        random_surface = TTF_RenderText_Solid(font3,"generate random map", red);
                        random_texture = SDL_CreateTextureFromSurface(sdlRenderer, random_surface);
                    } else{
                        random_surface = TTF_RenderText_Solid(font3,"generate random map", white);
                        random_texture = SDL_CreateTextureFromSurface(sdlRenderer, random_surface);
                    }
            }
        }
    }
    //========================================================================================
    //exit and destroy
    SDL_DestroyTexture(random_texture);
    SDL_FreeSurface(random_surface);
    SDL_DestroyTexture(map_texture);
    SDL_FreeSurface(map_surface);
    SDL_DestroyTexture(map1_texture);
    SDL_FreeSurface(map1_surface);
    SDL_DestroyTexture(map2_texture);
    SDL_FreeSurface(map2_surface);
    SDL_DestroyTexture(map3_texture);
    SDL_FreeSurface(map3_surface);
    SDL_DestroyTexture(map4_texture);
    SDL_FreeSurface(map4_surface);
    SDL_DestroyTexture(map5_texture);
    SDL_FreeSurface(map5_surface);
    SDL_DestroyTexture(map6_texture);
    SDL_FreeSurface(map6_surface);
    //========================================================================================
    if (!random_generate){
        return 0;
    }
    //random generation
    //intialization
    SDL_Surface * choose_surface = TTF_RenderText_Solid(font3,"choose the number of military bases for each person or region", white);
    SDL_Texture * choose_texture = SDL_CreateTextureFromSurface(sdlRenderer, choose_surface);
    SDL_Surface * napeleon_surface = TTF_RenderText_Solid(font3,"napeleon", red);
    SDL_Texture * napeleon_texture = SDL_CreateTextureFromSurface(sdlRenderer, napeleon_surface);
    SDL_Surface * caesar_surface = TTF_RenderText_Solid(font3,"caesar", red);
    SDL_Texture * caesar_texture = SDL_CreateTextureFromSurface(sdlRenderer, caesar_surface);
    SDL_Surface * jumong_surface = TTF_RenderText_Solid(font3,"jumong", red);
    SDL_Texture * jumong_texture = SDL_CreateTextureFromSurface(sdlRenderer, jumong_surface);
    SDL_Surface * hitler_surface = TTF_RenderText_Solid(font3,"hitler", red);
    SDL_Texture * hitler_texture = SDL_CreateTextureFromSurface(sdlRenderer, hitler_surface);
    SDL_Surface * stalin_surface = TTF_RenderText_Solid(font3,"stalin", red);
    SDL_Texture * stalin_texture = SDL_CreateTextureFromSurface(sdlRenderer, stalin_surface);
    SDL_Surface * central_asia_surface = TTF_RenderText_Solid(font3,"central asia", white);
    SDL_Texture * central_asia_texture = SDL_CreateTextureFromSurface(sdlRenderer, central_asia_surface);
    SDL_Surface * africa_surface = TTF_RenderText_Solid(font3,"africa", white);
    SDL_Texture * africa_texture = SDL_CreateTextureFromSurface(sdlRenderer, africa_surface);
    SDL_Surface * australia_surface = TTF_RenderText_Solid(font3,"australia", white);
    SDL_Texture * australia_texture = SDL_CreateTextureFromSurface(sdlRenderer, australia_surface);
    SDL_Surface * generate_surface = TTF_RenderText_Solid(font3,"generate", white);
    SDL_Texture * generate_texture = SDL_CreateTextureFromSurface(sdlRenderer, generate_surface);
    //initialization of background picture
    SDL_Surface * background_surface;
    SDL_Texture * background_texture;
    if (player_id == 0){
        background_surface = IMG_Load("napeleon_generate.jpeg");
        background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    }
    if (player_id == 1){
        background_surface = IMG_Load("caesar_generate.jpeg");
        background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    }
    if (player_id == 2){
        background_surface = IMG_Load("jumong_generate.jpeg");
        background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    }
    if (player_id == 3){
        background_surface = IMG_Load("hitler_generate.jpeg");
        background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    }
    if (player_id == 4){
        background_surface = IMG_Load("stalin_generate.jpeg");
        background_texture = SDL_CreateTextureFromSurface(sdlRenderer,background_surface);
    }
    //position
    SDL_Rect choose_position = {100,100,1200,50};
    SDL_Rect napeleon_position = {70,200,200,50};
    SDL_Rect caesar_position = {70,270,200,50};
    SDL_Rect jumong_position = {70,340,200,50};
    SDL_Rect hitler_position = {70,410,200,50};
    SDL_Rect stalin_position = {70,480,200,50};
    SDL_Rect central_asia_position = {70,550,200,50};
    SDL_Rect africa_position = {70,620,200,50};
    SDL_Rect australia_position = {70,690,200,50};
    SDL_Rect generate_position = {950,700,400,50};
    //
    //initialization of numbers
    struct number id_numbers[8][5];
    int id_number_limit[8] = {4,4,4,4,4,3,5,5};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < id_number_limit[i]; ++j) {
            char n[2];
            sprintf(n,"%d",j);
            id_numbers[i][j].number_surface = TTF_RenderText_Solid(font3,n, white);
            id_numbers[i][j].number_texture = SDL_CreateTextureFromSurface(sdlRenderer, id_numbers[i][j].number_surface);
            id_numbers[i][j].number_position.x = 300 + (70*j);
            id_numbers[i][j].number_position.y = 200 + (70*i);
            id_numbers[i][j].number_position.h = 50;
            id_numbers[i][j].number_position.w = 50;
        }
    }
    //
    quit = false;
    while (!quit){
        //music
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(main_play_list[rand()%3],0);
        }
        //
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(sdlRenderer);
        //background
        SDL_RenderCopy(sdlRenderer,background_texture,NULL,NULL);
        //state BP header
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);
        //choose message
        SDL_RenderCopy(sdlRenderer,choose_texture,NULL,&choose_position);
        //names
        SDL_RenderCopy(sdlRenderer,napeleon_texture,NULL,&napeleon_position);
        SDL_RenderCopy(sdlRenderer,caesar_texture,NULL,&caesar_position);
        SDL_RenderCopy(sdlRenderer,jumong_texture,NULL,&jumong_position);
        SDL_RenderCopy(sdlRenderer,hitler_texture,NULL,&hitler_position);
        SDL_RenderCopy(sdlRenderer,stalin_texture,NULL,&stalin_position);
        SDL_RenderCopy(sdlRenderer,central_asia_texture,NULL,&central_asia_position);
        SDL_RenderCopy(sdlRenderer,africa_texture,NULL,&africa_position);
        SDL_RenderCopy(sdlRenderer,australia_texture,NULL,&australia_position);
        //
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < id_number_limit[i]; ++j) {
                SDL_RenderCopy(sdlRenderer,id_numbers[i][j].number_texture,NULL,&id_numbers[i][j].number_position);
            }
        }
        //generate
        SDL_RenderCopy(sdlRenderer,generate_texture,NULL,&generate_position);
        //
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        //shall exit
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    return -1;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < id_number_limit[i]; ++j) {
                            if (if_in_text(id_numbers[i][j].number_position, event.button.x, event.button.y)){
                                int n[2];
                                sprintf(n,"%d",j);
                                id_numbers[i][j].number_surface = TTF_RenderText_Solid(font3,n, red);
                                id_numbers[i][j].number_texture = SDL_CreateTextureFromSurface(sdlRenderer, id_numbers[i][j].number_surface);
                                if (j != number_of_military_base[i]){
                                    sprintf(n,"%d",number_of_military_base[i]);
                                    id_numbers[i][number_of_military_base[i]].number_surface = TTF_RenderText_Solid(font3,n, white);
                                    id_numbers[i][number_of_military_base[i]].number_texture = SDL_CreateTextureFromSurface(sdlRenderer, id_numbers[i][number_of_military_base[i]].number_surface);
                                    number_of_military_base[i] = j;
                                }
                            }

                        }
                    }
                    if (if_in_text(generate_position,event.button.x,event.button.y)){
                        for (int i = 0; i < 5; ++i) {
                            if (i == player_id)
                                continue;
                            if (number_of_military_base[i] && number_of_military_base[player_id]){
                                quit = true;
                                break;
                            }
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (if_in_text(generate_position,event.motion.x,event.motion.y)){
                        generate_surface = TTF_RenderText_Solid(font3,"generate", red);
                        generate_texture = SDL_CreateTextureFromSurface(sdlRenderer, generate_surface);
                    } else{
                        generate_surface = TTF_RenderText_Solid(font3,"generate", white);
                        generate_texture = SDL_CreateTextureFromSurface(sdlRenderer, generate_surface);
                    }
            }
        }
    }

    //======================================
    for(int i = 0 ; i < 8; i++){
        military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
    }
    //generating the bases
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            military_bases[i][j].color = military_base_colors[i];
            military_bases[i][j].being_attacked = false;
            military_bases[i][j].activated = true;
            if(i > 4){
                military_bases[i][j].limitation_of_soldiers = 30;
                military_bases[i][j].number_of_soldiers = 30;
                military_bases[i][j].soldier_producing_speed = 50;
            } else{
                military_bases[i][j].limitation_of_soldiers = 50;
                military_bases[i][j].number_of_soldiers = 0;
                military_bases[i][j].soldier_producing_speed = 50;
            }
            do{
                generate_random_military_base(military_bases,i,j);
            } while (!is_valid_new_base(military_bases,i,j));
        }
    }
    //end and destroy
    SDL_DestroyTexture(choose_texture);
    SDL_FreeSurface(choose_surface);
    SDL_DestroyTexture(napeleon_texture);
    SDL_FreeSurface(napeleon_surface);
    SDL_DestroyTexture(caesar_texture);
    SDL_FreeSurface(caesar_surface);
    SDL_DestroyTexture(jumong_texture);
    SDL_FreeSurface(jumong_surface);
    SDL_DestroyTexture(hitler_texture);
    SDL_FreeSurface(hitler_surface);
    SDL_DestroyTexture(stalin_texture);
    SDL_FreeSurface(stalin_surface);
    SDL_DestroyTexture(central_asia_texture);
    SDL_FreeSurface(central_asia_surface);
    SDL_DestroyTexture(africa_texture);
    SDL_FreeSurface(africa_surface);
    SDL_DestroyTexture(australia_texture);
    SDL_FreeSurface(australia_surface);
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < id_number_limit[i]; ++j) {
            SDL_DestroyTexture(id_numbers[i][j].number_texture);
            SDL_FreeSurface(id_numbers[i][j].number_surface);
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            printf("%d and %d ----",military_bases[i][j].x,military_bases[i][j].y);
        }
        printf("\n");
    }
    return 0;
}