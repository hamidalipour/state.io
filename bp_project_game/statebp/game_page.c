//
// Created by Hamidreza on 1/28/22.
//
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "function.h"

//
//
void draw_hexagon(struct Military_base ** military_bases, int i, int j, SDL_Renderer * sdlRenderer,SDL_Texture * flags_texture[5], int frame_counter, TTF_Font * font4){
    if (military_bases[i][j].activated == false)
        return;
    const Sint16 x[6] = {military_bases[i][j].x + 10,
                         military_bases[i][j].x + 20,
                         military_bases[i][j].x + 10,
                         military_bases[i][j].x - 10,
                         military_bases[i][j].x - 20,
                         military_bases[i][j].x - 10};
    const Sint16 y[6] = {military_bases[i][j].y - 17,
                         military_bases[i][j].y ,
                         military_bases[i][j].y + 17,
                         military_bases[i][j].y + 17,
                         military_bases[i][j].y ,
                         military_bases[i][j].y - 17};
    filledPolygonColor(sdlRenderer,x,y,6,military_bases[i][j].color);
    SDL_Rect flag_position = {military_bases[i][j].x-12,military_bases[i][j].y-12,24,24};
    if(i < 5){
        SDL_RenderCopy(sdlRenderer, flags_texture[i], NULL, &flag_position);
    }
    if(i < 5 && military_bases[i][j].being_attacked == false && military_bases[i][j].limitation_of_soldiers > military_bases[i][j].number_of_soldiers && frame_counter % military_bases[i][j].soldier_producing_speed == 0){
        military_bases[i][j].number_of_soldiers++;
    }
    char number_soldiers[5];
    sprintf(number_soldiers,"%d",military_bases[i][j].number_of_soldiers);
    SDL_Surface * number_surface = TTF_RenderText_Solid(font4, number_soldiers, black);
    if( i == 3 )
        number_surface = TTF_RenderText_Solid(font4,number_soldiers,white);
    if( i == 1 )
        number_surface = TTF_RenderText_Solid(font4,number_soldiers,green);
    SDL_Texture * number_texture = SDL_CreateTextureFromSurface(sdlRenderer, number_surface);
    SDL_RenderCopy(sdlRenderer,number_texture,NULL,&flag_position);
    SDL_DestroyTexture(number_texture);
    SDL_FreeSurface(number_surface);
}
//
//
int if_in_hexagon(struct Military_base ** military_bases, int i, int j, int x, int y){
    if((military_bases[i][j].x - x) * (military_bases[i][j].x - x) + (military_bases[i][j].y - y) * (military_bases[i][j].y - y) < 256)
        return 1;
    return 0;
}
//
struct move next_move_of_soldier(int x1, int y1, int x2, int y2){
    struct move output;
    int x_sign = 1;
    int y_sign = 1;
    int x_diff = x2 - x1;
    int y_diff = y2 - y1;
    if(x_diff < 0){
        x_sign = -1;
        x_diff *=-1;
    }
    if(y_diff < 0){
        y_sign = -1;
        y_diff *=-1;
    }
    if(x_diff == 0){
        if(y_diff == 0){
            output.x = 0;
            output.y = 0;
            return output;
        } else{
            output.x = 0;
            output.y = y_sign*3;
            return output;
        }
    }
    if(y_diff == 0){
        output.y = 0;
        output.x = x_sign*3;
        return output;
    }
    if(x_diff > y_diff){
        double slope = ((y_diff*1.0)/x_diff)*3;
        int s = (int)(slope);
        if(s == 0)
            s = 1;
        output.x = x_sign*3;
        output.y = y_sign*s;
        return output;
    }
    else{
        double slope = ((x_diff*1.0)/y_diff)*3;
        int s = (int)(slope);
        if(s == 0)
            s = 1;
        output.y = y_sign*3;
        output.x = x_sign*s;
        return output;
    }
}
//this function returns the index of military_base[new_id] which was changed and returns -1 if it couldn't change anything
int change_base_id(struct Military_base ** military_bases, int formal_id, int place, int new_id, int number_of_military_bases[]){
    military_bases[formal_id][place].activated = false;
    for (int i = 0; i < number_of_military_bases[new_id]; ++i) {
        if (military_bases[new_id][i].activated == false){
            military_bases[new_id][i].activated = true;
            military_bases[new_id][i].x = military_bases[formal_id][place].x;
            military_bases[new_id][i].y = military_bases[formal_id][place].y;
            military_bases[new_id][i].number_of_soldiers = military_bases[formal_id][place].number_of_soldiers;
            military_bases[new_id][i].being_attacked = false;
            military_bases[new_id][i].color = military_base_colors[new_id];
            military_bases[new_id][i].limitation_of_soldiers = military_bases[new_id][0].limitation_of_soldiers;
            military_bases[new_id][i].soldier_producing_speed = military_bases[new_id][0].soldier_producing_speed;
            return i;
        }
    }
    return -1;
}
//
void score_board(int number_of_military_base[8],SDL_Renderer * sdlRenderer,SDL_Texture * flags_texture[5], TTF_Font * font4, struct Military_base** military_base, int id_potion[5], SDL_Texture * potions_texture[4], struct potion potions[5]){
    int number[5] = {0};
    int id[5] = {0,1,2,3,4};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            if (military_base[i][j].activated == true)
                number[i]++;
        }
    }
    for (int i = 0; i < 5; ++i) {
        int max = number[i];
        for (int j = i; j < 5; ++j) {
            if (max < number[j]) {
                max = number[j];
                number[j] = number[i];
                number[i] = max;
                int hold = id[j];
                id[j] = id[i];
                id[i] = hold;
            }
        }
    }
    SDL_Surface * point_surface;
    SDL_Texture * point_texture;
    for (int i = 0; i < 5; i++){
        if (number[i] == 0)
            continue;
        SDL_Rect position = {1330,100*(i+1),60,60};
        SDL_RenderCopy(sdlRenderer, flags_texture[id[i]], NULL, &position);

        position.x = 1260;
        char point[4];
        sprintf(point,"%d",number[i]);
        point_surface = TTF_RenderText_Solid(font4, point, white);
        point_texture = SDL_CreateTextureFromSurface(sdlRenderer, point_surface);
        SDL_RenderCopy(sdlRenderer,point_texture,NULL,&position);
        if (id_potion[id[i]] != -1){
            position.x = 1220;
            position.y +=15;
            position.w = 30;
            position.h = 30;
            SDL_RenderCopy(sdlRenderer,potions_texture[id_potion[id[i]]],NULL,&position);
            memset(point,'\0',4);
            sprintf(point,"%d",potions[id_potion[id[i]]].time);
            point_surface = TTF_RenderText_Solid(font4, point, red);
            point_texture = SDL_CreateTextureFromSurface(sdlRenderer, point_surface);
            position.x = 1200;
            position.w = 20;
            position.h = 20;
            SDL_RenderCopy(sdlRenderer,point_texture,NULL,&position);
        }
    }
    SDL_DestroyTexture(point_texture);
    SDL_FreeSurface(point_surface);
}
//
void set_march(struct march * marches, struct Military_base ** military_bases, int i1, int j1, int i2, int j2,int index_of_march,int number_of_marches){


    //printf("marches was being realloced\n");
    marches[index_of_march].finished = false;
    marches[index_of_march].number_of_soldiers = military_bases[i1][j1].number_of_soldiers;
    military_bases[i1][j1].number_of_soldiers = 0;
    marches[index_of_march].destination_x = military_bases[i2][j2].x;
    marches[index_of_march].destination_y = military_bases[i2][j2].y;
    marches[index_of_march].id = i1;
    marches[index_of_march].destination_place[0] = i2;
    marches[index_of_march].destination_place[1] = j2;
    marches[index_of_march].number_of_soldiers_to_move = 1;
    //printf("number of marches is %d\n",number_of_marches+1);
    if (index_of_march != number_of_marches-1) {
        free(marches[index_of_march].soldiers);
    }
    marches[index_of_march].soldiers = (struct soldier*)(malloc(sizeof(struct soldier) * marches[index_of_march].number_of_soldiers));
    marches[index_of_march].number_of_killed_soldiers = 0;
    marches[index_of_march].number_of_soldiers_in_destination = 0;
    for (int k = 0; k < marches[index_of_march].number_of_soldiers; ++k) {
        marches[index_of_march].soldiers[k].x = military_bases[i1][j1].x;
        marches[index_of_march].soldiers[k].y = military_bases[i1][j1].y;
        marches[index_of_march].soldiers[k].in_destination = false;
        marches[index_of_march].soldiers[k].killed = false;
    }
    //printf("number of marches is %d\n",number_of_marches+1);
}
//
int base_strength(struct Military_base ** military_bases,int i1, int j1, int i2, int j2){
    int output = military_bases[i2][j2].number_of_soldiers;
    if (i2 > 4){
        output +=(abs(military_bases[i2][j2].x - military_bases[i1][j1].x) + abs(military_bases[i2][j2].y - military_bases[i1][j1].y))/20 + 10;
        return output;
    }
    output +=(abs(military_bases[i2][j2].x - military_bases[i1][j1].x) + abs(military_bases[i2][j2].y - military_bases[i1][j1].y))/10;
    return output;
}
//this function returns the number of marches that was arranged
struct march_from_to artificial_intelligence_singular( struct Military_base ** military_bases, struct march * marches,int id, int player_id,const int number_of_military_base[8]){
    struct march_from_to output = {-1,-1,-1,-1};
    //printf("enter artificial\n");
    for (int i = 0; i < number_of_military_base[id]; ++i) {
        if (military_bases[id][i].activated == false)
            continue;
        for (int j = 0; j < number_of_military_base[player_id]; ++j) {
            if (military_bases[player_id][j].activated == false)
                continue;
            //printf("not sure if a march should be set\n");
            if (base_strength(military_bases,id,i,player_id,j) < military_bases[id][i].number_of_soldiers){
                //printf("wants to set a march from %d and %d to %d and %d\n",id,i,player_id,j);
                output.i1 = id;
                output.j1 = i;
                output.i2 = player_id;
                output.j2 = j;
                return output;
            }
        }
        for (int j = 0; j < 8; ++j) {
            if (j == player_id || j == id)
                continue;
            for (int k = 0; k < number_of_military_base[j]; ++k) {
                if (military_bases[j][k].activated == false)
                    continue;
                //printf("not sure if a march should be set\n");
                if (base_strength(military_bases,id,i,j,k) < military_bases[id][i].number_of_soldiers){
                    //printf("wants to set a march from %d and %d to %d and %d\n",id,i,j,k);
                    output.i1 = id;
                    output.j1 = i;
                    output.i2 = j;
                    output.j2 = k;
                    return output;
                }
            }
        }
    }
    return output;
}
//
bool is_valid_potion(struct potion potions[],int i, struct Military_base ** military_bases, int number_of_military_bases[]){
    for (int j = 0; j < i; ++j) {
        if (abs(potions[i].x - potions[j].x) + abs(potions[i].y - potions[j].y) < 40){
            return false;
        }
    }
    for (int j = 0; j < 8; ++j) {
        for (int k = 0; k < number_of_military_bases[j]; ++k) {
            if (abs(potions[i].x - military_bases[j][k].x) + abs(potions[i].y - military_bases[j][k].y) < 40)
                return false;
        }
    }
    return true;
}
//if quit button is pushed this function returns -1 and 1 if player wins and 0 if loses
int game_page(TTF_Font * font4, SDL_Window *sdlWindow,
               SDL_Renderer *sdlRenderer,
               SDL_Texture * state_texture, SDL_Texture * BP_texture
        ,SDL_Rect state_position, SDL_Rect BP_position, struct Character * dictators, int number_of_military_base[8],int player_id, struct Military_base ** military_bases){

    //initialization of flags
    SDL_Surface * military_base_flag[5];
    military_base_flag[0] = IMG_Load("napeleon_flag.jpeg");
    military_base_flag[1] = IMG_Load("caesar_flag.png");
    military_base_flag[2] = IMG_Load("jumong_flag.jpeg");
    military_base_flag[3] = IMG_Load("hitler_flag.jpeg");
    military_base_flag[4] = IMG_Load("stalin_flag.jpeg");
    SDL_Texture * flags_texture[5];
    for(int i = 0; i < 5; i++){
        flags_texture[i] = SDL_CreateTextureFromSurface(sdlRenderer,military_base_flag[i]);
    }
    //initialization
    SDL_Surface * map = IMG_Load("map.png");
    SDL_Texture * map_texture = SDL_CreateTextureFromSurface(sdlRenderer, map);
    SDL_Surface * discover = TTF_RenderText_Solid(font4,"not discovered yet:D", red);
    SDL_Texture * discover_texture = SDL_CreateTextureFromSurface(sdlRenderer, discover);
    //
    SDL_Rect map_position = {0,100,1200,700};
    SDL_Rect discover_position = {100,350,180,30};
    //====================================================================
    //making the marching array
    struct march * marches = (struct march*)(malloc(sizeof(struct march)));
    int number_of_marches = 0;
    //======================================================================
    int number_of_all_bases = 0;
    for (int i = 0; i < 8; ++i) {
        number_of_all_bases +=number_of_military_base[i];
    }
    //=====================================================================
    //potion 0 doubles the speed of soldiers
    //potion 1 freezes all the enemies soldiers
    //potion 2 removes the limit of producing soldiers in military bases
    //potion 3 changes the id of soldiers who attacks it to its own
    //potion 4 doubles the soldier producing speed
    //initialization of potions
    struct potion potions[5];
    for (int i = 0; i < 5; ++i) {
        potions[i].id = -1;
        potions[i].activated = false;
        potions[i].being_used = false;
        potions[i].time = 50;
        while (1){
            int i1 = rand()%8;
            if (number_of_military_base[i1] == 0)
                continue;
            int j1 = rand()%number_of_military_base[i1];
            int i2 = rand()%8;
            if (number_of_military_base[i2] == 0)
                continue;
            int j2 = rand()%number_of_military_base[i2];
            struct move slope = next_move_of_soldier(military_bases[i1][j1].x, military_bases[i1][j1].y, military_bases[i2][j2].x, military_bases[i2][j2].y);
            int temp =(rand() % abs(military_bases[i1][j1].x - military_bases[i2][j2].x))/3;
            slope.x *=temp;
            slope.y *=temp;
            potions[i].x = military_bases[i1][j1].x + slope.x;
            potions[i].y = military_bases[i1][j1].y + slope.y;
            if (is_valid_potion(potions,i,military_bases,number_of_military_base) == false){
                continue;
            }
            break;
        }
    }
    SDL_Surface * potions_surface[5];
    SDL_Texture * potions_texture[5];
    potions_surface[0] = IMG_Load("potion0.jpeg");
    potions_surface[1] = IMG_Load("potion1.jpeg");
    potions_surface[2] = IMG_Load("potion2.jpeg");
    potions_surface[3] = IMG_Load("potion3.jpeg");
    potions_surface[4] = IMG_Load("potion4.jpeg");
    for (int i = 0; i < 5; ++i) {
        potions_texture[i] = SDL_CreateTextureFromSurface(sdlRenderer,potions_surface[i]);
    }
    int id_potion[5] = {-1,-1,-1,-1,-1};
    //=====================================================================
    //======================================================================
    for (int i = 0; i < 8; ++i) {
        printf("%d ",number_of_military_base[i]);
    }
    printf("\n");
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < number_of_military_base[i]; ++j) {
            printf("%d and %d---",military_bases[i][j].x,military_bases[i][j].y);
        }
        printf("\n");
    }
    int output = -1;
    SDL_Event event;
    bool quit = false;
    int frame_counter = 0;
    int origin_base = -1;
    int number_of_activated_potions = 0;
    while (!quit){
        //music
        if (Mix_PlayingMusic() == 0){
            //music
            if (player_id == 0){
                Mix_PlayMusic(napeleon_game_play_list[rand()%2],0);
            }
            if (player_id == 1){
                Mix_PlayMusic(caesar_game_play_list[rand()%4],0);
            }
            if (player_id == 2){
                Mix_PlayMusic(jumong_game_play_list[rand()%5],0);
            }
            if (player_id == 3){
                Mix_PlayMusic(hitler_game_play_list[rand()%2],0);
            }
            if (player_id == 4){
                Mix_PlayMusic(stalin_game_play_list[rand()%3],0);
            }
        }
        //state BP header
        SDL_SetRenderDrawColor(sdlRenderer, 0x1a, 0x10, 0x10, 0xf0);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, state_texture, NULL, &state_position);
        SDL_RenderCopy(sdlRenderer, BP_texture, NULL, &BP_position);
        //
        SDL_RenderCopy(sdlRenderer, map_texture, NULL, &map_position);
        SDL_RenderCopy(sdlRenderer, discover_texture, NULL, &discover_position);
        //drawing of potions
        for (int i = 0; i < 5; ++i) {
            if (potions[i].activated == false)
                continue;
            if (potions[i].being_used == true){
                if (potions[i].time == 0){
                    if (i == 2){
                        for (int l = 0; l < number_of_military_base[potions[i].id]; ++l) {
                            military_bases[potions[i].id][l].limitation_of_soldiers = 50;
                        }
                    }
                    if (i == 4){
                        for (int l = 0; l < number_of_military_base[potions[i].id]; ++l) {
                            military_bases[potions[i].id][l].soldier_producing_speed = 50;
                        }
                    }
                    id_potion[potions[i].id] = -1;
                    potions[i].id = -1;
                    potions[i].being_used = false;
                    potions[i].activated = false;
                }
                if (frame_counter%60 == 0){
                    potions[i].time--;
                }
                continue;
            }
            SDL_Rect potion_position = {potions[i].x - 12, potions[i].y - 12, 24, 24};
            SDL_RenderCopy(sdlRenderer, potions_texture[i], NULL, &potion_position);
            for (int j = 0; j < number_of_marches; ++j) {
                if (marches[j].finished == true || id_potion[marches[j].id] != -1)
                    continue;
                for (int k = 0; k < marches[j].number_of_soldiers; ++k) {
                    if (marches[j].soldiers[k].killed == true || marches[j].soldiers[k].in_destination == true)
                        continue;
                    if (abs(marches[j].soldiers[k].x - potions[i].x) + abs(marches[j].soldiers[k].y - potions[i].y) < 25){
                        potions[i].being_used = true;
                        potions[i].id = marches[j].id;
                        id_potion[marches[j].id] = i;
                        if (i == 2){
                            for (int l = 0; l < number_of_military_base[potions[i].id]; ++l) {
                                military_bases[potions[i].id][l].limitation_of_soldiers = 1000;
                            }
                        }
                        if (i == 4){
                            for (int l = 0; l < number_of_military_base[potions[i].id]; ++l) {
                                military_bases[potions[i].id][l].soldier_producing_speed = 25;
                            }
                        }
                    }
                }
            }

        }
        if (number_of_activated_potions < 5 && rand() % 1000 == 0){
            potions[number_of_activated_potions].activated = true;
            number_of_activated_potions++;
        }
        //
        //drawing of soldiers
        //printf("number of soldiers in des of the last marche is %d\n",marches[number_of_marches-1].number_of_soldiers_in_destination);
        for (int i = 0; i < number_of_marches; i++) {
            if (marches[i].finished == true)
                continue;
            for (int j = 0; j < marches[i].number_of_soldiers_to_move; j++) {
                if(marches[i].soldiers[j].in_destination == true || marches[i].soldiers[j].killed == true){
                    continue;
                }
                if(abs(marches[i].soldiers[j].x - marches[i].destination_x) + abs(marches[i].soldiers[j].y - marches[i].destination_y) < 10) {
                    marches[i].soldiers[j].in_destination = true;
                    //printf("soldier number %d of march %d had reached base %d and %d\n",j,i,marches[i].destination_place[0],marches[i].destination_place[1]);
                    marches[i].number_of_soldiers_in_destination++;
                    if(marches[i].id != marches[i].destination_place[0]){
                        if (military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].number_of_soldiers <= 0){
                            int changed_index = change_base_id(military_bases,marches[i].destination_place[0],marches[i].destination_place[1], marches[i].id, number_of_military_base);
                            if (changed_index == -1){
                                number_of_military_base[marches[i].id]++;
                                military_bases[marches[i].id] = (struct Military_base*)(realloc(military_bases[marches[i].id],
                                                                                                sizeof(struct Military_base) * number_of_military_base[marches[i].id]));
                                military_bases[marches[i].id][number_of_military_base[marches[i].id]-1].activated = false;
                                changed_index = change_base_id(military_bases,marches[i].destination_place[0],marches[i].destination_place[1], marches[i].id,number_of_military_base);
                            }
                            //printf("the id of base %d and %d was changed to %d and %d\n",marches[i].destination_place[0],marches[i].destination_place[1],marches[i].id,number_of_military_base[marches[i].id]-1);
                            int hold1 = marches[i].destination_place[0];
                            int hold2 = marches[i].destination_place[1];
                            if(hold1 == player_id && hold2 == origin_base){
                                origin_base = -1;
                            }
                            for (int k = 0; k < number_of_marches; ++k) {
                                if(marches[k].destination_place[0] == hold1 && marches[k].destination_place[1] == hold2){
                                    marches[k].destination_place[0] = marches[i].id;
                                    marches[k].destination_place[1] = changed_index;
                                }
                            }
                            military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].number_of_soldiers++;
                            military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].being_attacked = false;
                        } else {
                            //printf("number of soldiers of base %d and %d was decreased\n",marches[i].destination_place[0],marches[i].destination_place[1]);
                            if (id_potion[marches[i].destination_place[0]] == 3){
                                military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].number_of_soldiers++;
                            } else{
                                military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].number_of_soldiers--;
                            }
                            military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].being_attacked = true;
                        }
                    } else{
                        //printf("number of soldiers of base %d and %d was increased\n",marches[i].destination_place[0],marches[i].destination_place[1]);
                        military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].number_of_soldiers++;
                        military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].being_attacked = true;
                    }

                }
                struct move next_move = next_move_of_soldier(marches[i].soldiers[j].x,marches[i].soldiers[j].y, marches[i].destination_x,
                                                             marches[i].destination_y);
                //potion
                if (id_potion[marches[i].id] == 0){
                    next_move.x *=2;
                    next_move.y *=2;
                }
                if (potions[1].id != -1 && potions[1].id != marches[i].id){
                    next_move.x = 0;
                    next_move.y = 0;
                }
                //
                marches[i].soldiers[j].x += next_move.x;
                marches[i].soldiers[j].y += next_move.y;
                SDL_Rect soldier_position = {marches[i].soldiers[j].x-3,marches[i].soldiers[j].y,6,6};
                SDL_RenderCopy(sdlRenderer, flags_texture[marches[i].id], NULL, &soldier_position);
            }
            if ((potions[1].id == -1 || potions[1].id == marches[i].id) && marches[i].number_of_soldiers > marches[i].number_of_soldiers_to_move && frame_counter % 20 == 0) {
                marches[i].number_of_soldiers_to_move++;
            }
        }
        //checking for finished marches
        for (int i = 0; i < number_of_marches; ++i) {
            if (marches[i].finished == true || marches[i].number_of_soldiers_in_destination == marches[i].number_of_soldiers - marches[i].number_of_killed_soldiers) {
                military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].being_attacked = false;
                marches[i].finished = true;

            }
        }
        //soldiers killing
        for (int i = 0; i < number_of_marches; ++i) {
            if (marches[i].finished == true)
                continue;
            for (int j = i+1; j < number_of_marches; ++j) {
                if (marches[j].finished == true || marches[i].id == marches[j].id)
                    continue;
                for (int k = 0; k < marches[i].number_of_soldiers; ++k) {
                    if (marches[i].soldiers[k].in_destination == true || marches[i].soldiers[k].killed == true)
                        continue;
                    for (int l = 0; l < marches[j].number_of_soldiers; ++l) {
                        if (marches[j].soldiers[l].in_destination == true || marches[j].soldiers[l].killed == true)
                            continue;
                        if (abs(marches[i].soldiers[k].x - marches[j].soldiers[l].x) + abs(marches[i].soldiers[k].y - marches[j].soldiers[l].y) < 12){
                            marches[i].soldiers[k].killed = true;
                            marches[j].soldiers[l].killed = true;
                            marches[i].number_of_killed_soldiers++;
                            marches[j].number_of_killed_soldiers++;
                            break;
                        }
                    }
                }
            }
        }
        //drawing of military bases
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < number_of_military_base[i]; j++){
                draw_hexagon(military_bases,i,j,sdlRenderer,flags_texture,frame_counter,font4);
            }
        }
//        for(int i = 0; i < 8; i++){
//            boxColor(sdlRenderer,regions[i].x1,regions[i].y1,regions[i].x2,regions[i].y2,military_base_colors[i]);
//        }

//        printf("number of soldiers in bases are\n");
//        for (int i = 0; i < 5; ++i) {
//            for (int j = 0; j < number_of_military_base[i]; ++j) {
//                printf("%d ",military_bases[i][j].number_of_soldiers);
//            }
//            printf("\n");
//        }
//        printf("===========================================\n");
        //score board
        score_board(number_of_military_base,sdlRenderer,flags_texture,font4,military_bases,id_potion,potions_texture,potions);
        //checking for end of game
        int number_of_my_bases = 0;
        for (int i = 0; i < number_of_military_base[player_id]; ++i) {
            if (military_bases[player_id][i].activated == true)
                number_of_my_bases++;
        }
        if (number_of_my_bases == number_of_all_bases){
            quit = true;
            output = 1;
        }
        if (number_of_my_bases == 0){
            quit = true;
            output = 0;
        }
        //the choosing other players marches
        for (int i = 0; i < 5; ++i) {
            if (i == player_id)
                continue;
            struct march_from_to singular_march = artificial_intelligence_singular(military_bases,marches,i,player_id,number_of_military_base);
            if (singular_march.i1 != -1){
//                marches = (struct march*)(realloc(marches, sizeof(struct march) * (number_of_marches+1)));
//                set_march(marches,military_bases,singular_march.i1,singular_march.j1,singular_march.i2,singular_march.j2,number_of_marches);
//                number_of_marches++;
                bool flag = false;
                for (int j = 0; j < number_of_marches; ++j) {
                    if (marches[j].finished == true){
                        //military_bases[marches[i].destination_place[0]][marches[i].destination_place[1]].being_attacked = false;
                        set_march(marches,military_bases,singular_march.i1,singular_march.j1,singular_march.i2,singular_march.j2,j,number_of_marches);
                        flag = true;
                        break;
                    }
                }
                if (!flag){
                    number_of_marches++;
                    marches = (struct march*)(realloc(marches, sizeof(struct march) * number_of_marches));
                    set_march(marches,military_bases,singular_march.i1,singular_march.j1,singular_march.i2,singular_march.j2,number_of_marches-1,number_of_marches);
                }
            }
        }
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
                    for(int i = 0; i < 8; i++){
                        if(origin_base == -1 && i != player_id)
                            continue;
                        for(int j = 0; j < number_of_military_base[i]; j++){
                            if (military_bases[i][j].activated == false)
                                continue;
                            if(if_in_hexagon(military_bases,i,j,event.button.x,event.button.y)) {
                                if(origin_base == -1){
                                    origin_base = j;
                                    military_bases[i][j].color = military_base_colors[8];
                                } else{
                                    if (origin_base == j && i == player_id){
                                        origin_base = -1;
                                        military_bases[i][j].color = military_base_colors[player_id];
                                        continue;
                                    }
                                    military_bases[player_id][origin_base].color = military_base_colors[player_id];
                                    bool flag = false;
                                    printf("march was set from %d and %d to %d and %d\n",player_id,origin_base,i, j);
                                    for (int k = 0; k < number_of_marches; ++k) {
                                        if (marches[k].finished == true){
                                            //military_bases[marches[k].destination_place[0]][marches[k].destination_place[1]].being_attacked = false;
                                            set_march(marches,military_bases,player_id,origin_base,i,j,k,number_of_marches);
                                            flag = true;
                                            break;
                                        }
                                    }
                                    if (!flag){
                                        number_of_marches++;
                                        marches = (struct march*)(realloc(marches, sizeof(struct march) * number_of_marches));
                                        set_march(marches,military_bases,player_id,origin_base,i,j,number_of_marches-1,number_of_marches);
                                    }
                                    //printf("march was set from %d and %d to %d and %d\n",player_id,origin_base,i,j);
                                    origin_base = -1;
                                    break;

                                }
                            }
                        }
                    }
            }
        }
        //
        frame_counter++;
        if (frame_counter > 1000000)
            frame_counter %=1000000;

    }
    //======================================
    //end and destroy
    SDL_DestroyTexture(map_texture);
    SDL_FreeSurface(map);
    SDL_DestroyTexture(discover_texture);
    SDL_FreeSurface(discover);
    for (int i = 0; i < 5; ++i) {
        SDL_DestroyTexture(potions_texture[i]);
        SDL_FreeSurface(potions_surface[i]);
    }
    for(int i = 0; i < 5; i++){
        SDL_DestroyTexture(flags_texture[i]);
        SDL_FreeSurface(military_base_flag[i]);
    }
    for(int i = 0; i < 8; i++){
        free(military_bases[i]);
    }
    free(military_bases);
    for (int i = 0; i < number_of_marches; ++i) {
        free(marches[i].soldiers);
    }
    free(marches);
    return output;
}
