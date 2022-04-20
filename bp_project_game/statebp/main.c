#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"
//
void swap_users(struct user users[], int i, int j){
    int hold = users[i].coin;
    users[i].coin = users[j].coin;
    users[j].coin = hold;
    char hold_string[100];
    memset(hold_string,'\0',100);
    strcat(hold_string,users[i].username);
    memset(users[i].username,'\0',100);
    strcat(users[i].username,users[j].username);
    memset(users[j].username,'\0',100);
    strcat(users[j].username,hold_string);
}
//
int change_user_place(int number_of_users, int index_of_user, struct user users[],int game_status){
    if (game_status == 1){
        users[index_of_user].coin +=150;
        if (index_of_user == 0)
            return index_of_user;
        while (users[index_of_user].coin > users[index_of_user-1].coin){
            swap_users(users,index_of_user,index_of_user-1);
            index_of_user--;
            if (index_of_user == 0)
                return index_of_user;
        }
        return index_of_user;
    } else{
        users[index_of_user].coin -=150;
        if (users[index_of_user].coin < 0){
            users[index_of_user].coin = 0;
        }
        if (index_of_user == number_of_users-1)
            return index_of_user;
        while (users[index_of_user].coin < users[index_of_user+1].coin){
            swap_users(users,index_of_user,index_of_user+1);
            index_of_user++;
            if (index_of_user == number_of_users-1)
                return index_of_user;
        }
        return index_of_user;
    }


}
void write_in_file(struct user users[], int number_of_users){
    FILE * fptr = fopen("usernames.txt","w");
    for (int i = 0; i < number_of_users; ++i) {
        fprintf(fptr,"%s %d\n",users[i].username, users[i].coin);
    }
    fclose(fptr);
}
//
int main() {
    //init
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    //srand
    srand(time(NULL));
    //initialization of window and renderer
    SDL_Window *sdlWindow = SDL_CreateWindow("state.BP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    TTF_Font * font1 = TTF_OpenFont("28 Days Later.ttf", 20);
    TTF_Font * font2 = TTF_OpenFont("KindnessLoveDemoRegular.ttf", 20);
    TTF_Font * font4 = TTF_OpenFont("Cadman-6Yv7o.ttf",20);
    TTF_Font * font3 = TTF_OpenFont("CollegiateFLF.ttf",20);
    SDL_Surface * state_surface = TTF_RenderText_Solid(font1,"state", white);
    SDL_Surface * BP_surface = TTF_RenderText_Solid(font1,"BP",red);
    SDL_Texture * state_texture = SDL_CreateTextureFromSurface(sdlRenderer, state_surface);
    SDL_Texture * BP_texture = SDL_CreateTextureFromSurface(sdlRenderer, BP_surface);
    SDL_Rect state_position = {620,0,130,30};
    SDL_Rect BP_position = {760,0,40,30};
    //
    struct Character * dictators = (struct Character*)(malloc(sizeof(struct Character) * 5));
    //initialization of characters pictures and names
    dictators[0].image = IMG_Load("napeleon.jpeg");
    dictators[0].image_texture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[0].image);
    dictators[1].image = IMG_Load("julius_caesar.jpg");
    dictators[1].image_texture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[1].image);
    dictators[2].image = IMG_Load("jumong.jpeg");
    dictators[2].image_texture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[2].image);
    dictators[3].image = IMG_Load("hitler.jpg");
    dictators[3].image_texture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[3].image);
    dictators[4].image = IMG_Load("stalin.jpeg");
    dictators[4].image_texture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[4].image);

    dictators[0].name = TTF_RenderText_Solid(font3,"napeleon", red);
    dictators[0].name_tuxture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[0].name);
    dictators[1].name = TTF_RenderText_Solid(font3,"julius caesar", red);
    dictators[1].name_tuxture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[1].name);
    dictators[2].name = TTF_RenderText_Solid(font3,"jumong", red);
    dictators[2].name_tuxture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[2].name);
    dictators[3].name = TTF_RenderText_Solid(font3,"hitler", red);
    dictators[3].name_tuxture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[3].name);
    dictators[4].name = TTF_RenderText_Solid(font3,"stalin", red);
    dictators[4].name_tuxture = SDL_CreateTextureFromSurface(sdlRenderer, dictators[4].name);
    //=============================================================
    //initialization of sound
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
    //==========================================================
    main_play_list[0] = Mix_LoadMUS("04 - The Queen's Justice.mp3");
    main_play_list[1] = Mix_LoadMUS("02 Ramin Djawadi - A Lannister Always Pays His Debts.mp3");
    main_play_list[2] = Mix_LoadMUS("01. Main Titles.mp3");
    //===========================================================
    jumong_defeat_play_list[0] = Mix_LoadMUS("18 Longing.mp3");
    jumong_defeat_play_list[1] = Mix_LoadMUS("02 Sad Fate.mp3");
    //===========================================================
    jumong_win_play_list[0] = Mix_LoadMUS("01 Jumong Main Theme Main Theme.mp3");
    jumong_win_play_list[1] = Mix_LoadMUS("21 Jumong Ending Theme Ending Theme.mp3");
    //==========================================================
    other_defeat_play_list[0] = Mix_LoadMUS("19 Ramin Djawadi - For the Realm.mp3");
    other_defeat_play_list[1] = Mix_LoadMUS("03 Ramin Djawadi - Goodbye Brother.mp3");
    //==========================================================
    other_win_play_list[0] = Mix_LoadMUS("Dj Snake & Lil Jon - Turn Down For What 128.mp3");
    //==========================================================
    jumong_game_play_list[0] = Mix_LoadMUS("03 Steel Army s Attack.mp3");
    jumong_game_play_list[1] = Mix_LoadMUS("06 The Sword Of Destiny.mp3");
    jumong_game_play_list[2] = Mix_LoadMUS("07 Bloody Battlefield.mp3");
    jumong_game_play_list[3] = Mix_LoadMUS("16 Legendary Time.mp3");
    jumong_game_play_list[4] = Mix_LoadMUS("20 Pursuit.mp3");
    //==========================================================
    napeleon_game_play_list[0] = Mix_LoadMUS("20 - Ironborn.mp3");
    napeleon_game_play_list[1] = Mix_LoadMUS("10 - Spoils of War, Pt. 2.mp3");
    //==========================================================
    caesar_game_play_list[0] = Mix_LoadMUS("16 Ramin Djawadi - To Vaes Dothrak.mp3");
    caesar_game_play_list[1] = Mix_LoadMUS("18 Ramin Djawadi - Mother of Dragons.mp3");
    caesar_game_play_list[2] = Mix_LoadMUS("02. Blood of My Blood.mp3");
    caesar_game_play_list[3] = Mix_LoadMUS("02 Blood of the Dragon.mp3");
    //==========================================================
    hitler_game_play_list[0] = Mix_LoadMUS("11 Two Swords.mp3");
    hitler_game_play_list[1] = Mix_LoadMUS("18. Hear Me Roar.mp3");
    //==========================================================
    stalin_game_play_list[0] = Mix_LoadMUS("11 Ramin Djawadi - Don't Die with a Clean Sword.mp3");
    stalin_game_play_list[1] = Mix_LoadMUS("16 Ramin Djawadi - Stand and Fight.mp3");
    stalin_game_play_list[2] = Mix_LoadMUS("16. Trust Each Other.mp3");
    //==========================================================
    //==========================================================
    //==========================================================
    //==========================================================
    //===========

    int first_page_output = first_page(font1,font2,font3,sdlWindow,sdlRenderer);
    if(first_page_output == -1)
        return 0;
    //=======================
    Mix_PlayMusic(main_play_list[rand()%3],0);
    //======================
    char username[100];
    memset(username,'\0',100);
    struct user users[100];
    int number_of_users = 0;
    //this function returns the index of username in the array users[] and -1 if quit button was pushed
    int index_of_user = logging_page(font3,font4,sdlRenderer,state_texture,BP_texture,state_position,BP_position,username,users,&number_of_users);
    if(index_of_user == -1)
        return 0;
    write_in_file(users, number_of_users);
    //
    while (1){
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(main_play_list[rand()%3],0);
        }
        //id 0 stands for napeleon 1 for caesar 2 for jumong 3 for hitler 4 for stalin and -1 means the quit vutton was pushed and -2 means there is a requst for viewing leadeship
        int id = choose_character_page(font3,font4,sdlRenderer,state_texture, BP_texture,state_position,BP_position,dictators,username,users[index_of_user].coin);
        if(id == -1)
            break;
        //
        if (id == -2){
            //this function returns -1 if quit button was pushed and 0 if back option was chosen
            int lead = leadership_page(font3,font4,sdlRenderer,state_texture,BP_texture,state_position,BP_position,users,number_of_users);
            if (lead == -1)
                break;
            continue;
        }
        //
        struct Military_base ** military_bases = (struct Military_base**)(malloc(sizeof(struct Military_base*)*8));
        int number_of_military_base[8] = {0};
//        for(int i = 0 ; i < 8; i++){
//            military_bases[i] = (struct Military_base*)(malloc(sizeof(struct Military_base) * number_of_military_base[i]));
//        }
        //generating the bases
        //returns -1 if exit button was pushed
        int generate = generating_board_page(font3,sdlWindow,sdlRenderer,state_texture,BP_texture,state_position,BP_position,number_of_military_base,id,military_bases);
        if (generate == -1)
            break;
        //the 5th and 6th and 7th index of number_of_military_base stand for middle asia and africa and australia
        //
        int game_status = game_page(font4,sdlWindow,sdlRenderer,state_texture, BP_texture,state_position,BP_position,dictators,number_of_military_base,id,military_bases);
        if(game_status == -1)
            break;
        //
        index_of_user = change_user_place(number_of_users,index_of_user,users,game_status);
        write_in_file(users,number_of_users);
        //
        int a = message_page(font3,font4,sdlRenderer,game_status,id);
        if(a == -1)
            break;
    }

    //===========
    SDL_DestroyTexture(BP_texture);
    SDL_DestroyTexture(state_texture);
    SDL_FreeSurface(BP_surface);
    SDL_FreeSurface(state_surface);
    //
    SDL_DestroyTexture(dictators[0].image_texture);
    SDL_DestroyTexture(dictators[1].image_texture);
    SDL_DestroyTexture(dictators[2].image_texture);
    SDL_DestroyTexture(dictators[3].image_texture);
    SDL_DestroyTexture(dictators[4].image_texture);
    SDL_FreeSurface(dictators[0].image);
    SDL_FreeSurface(dictators[1].image);
    SDL_FreeSurface(dictators[2].image);
    SDL_FreeSurface(dictators[3].image);
    SDL_FreeSurface(dictators[4].image);

    SDL_DestroyTexture(dictators[0].name_tuxture);
    SDL_DestroyTexture(dictators[1].name_tuxture);
    SDL_DestroyTexture(dictators[2].name_tuxture);
    SDL_DestroyTexture(dictators[3].name_tuxture);
    SDL_DestroyTexture(dictators[4].name_tuxture);
    SDL_FreeSurface(dictators[0].name);
    SDL_FreeSurface(dictators[1].name);
    SDL_FreeSurface(dictators[2].name);
    SDL_FreeSurface(dictators[3].name);
    SDL_FreeSurface(dictators[4].name);
    //
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);
    free(dictators);
    for (int i = 0; i < 3; ++i) {
        Mix_FreeMusic(main_play_list[i]);
    }
    for (int i = 0; i < 2; ++i) {
        Mix_FreeMusic(jumong_defeat_play_list[i]);
    }
    for (int i = 0; i < 2; ++i) {
        Mix_FreeMusic(jumong_win_play_list[i]);
    }
    for (int i = 0; i < 2; ++i) {
        Mix_FreeMusic(other_defeat_play_list[i]);
    }
    Mix_FreeMusic(other_win_play_list[0]);
    for (int i = 0; i < 5; ++i) {
        Mix_FreeMusic(jumong_game_play_list[i]);
    }
    for (int i = 0; i < 2; ++i) {
        Mix_FreeMusic(napeleon_game_play_list[i]);
    }
    for (int i = 0; i < 4; ++i) {
        Mix_FreeMusic(caesar_game_play_list[i]);
    }
    for (int i = 0; i < 2; ++i) {
        Mix_FreeMusic(hitler_game_play_list[i]);
    }
    for (int i = 0; i < 3; ++i) {
        Mix_FreeMusic(stalin_game_play_list[i]);
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}