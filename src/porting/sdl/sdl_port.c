//
// Created by endif on 25-6-22.
//

#include "sdl_port.h"
#include <SDL2/SDL.h>
#include "stdbool.h"
#include "lv_drv_conf.h"

SDL_Event event;
bool quit = false;


#include "lvgl.h"
void sdl_event() {
    while (!quit) {
        lv_timer_handler();
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    printf("key:%d\n", event.key.keysym.scancode);
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }

        }

        SDL_Delay(15);
    }
    // 释放 SDL 资源
    SDL_Quit();
}

