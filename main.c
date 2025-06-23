#include <stdio.h>
#include "lvgl.h"

#define _DEFAULT_SOURCE  /* needed for usleep() */
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include "src/porting/sdl/sdl_port.h"
#include "components/lvgl/src/drivers/lv_drivers.h"


static int lvgl_thread(void *data)
{
    LV_UNUSED(data);

    while (1) {
        lv_tick_inc(15);

        SDL_Delay(15);
    }

    return 0;
}

void lv_hal_init() {

    // 初始化 SDL 显示驱动
    lv_display_t * disp = lv_sdl_window_create(480, 320);

    if (!disp) {
        LV_LOG_ERROR("Failed to create SDL window");
        return;
    }

    // 设置窗口标题
    lv_sdl_window_set_title(disp, "LVGL SDL Emulator");

    // 可选：设置窗口图标
    // lv_sdl_window_set_icon(disp, icon_data, icon_width, icon_height);

    // 可选：设置窗口缩放比例
    lv_sdl_window_set_zoom(disp, 1.0f);  // 1:1 缩放

    // 可选：设置窗口是否可调整大小
    lv_sdl_window_set_resizeable(disp, true);
    // SDL_CaptureMouse(SDL_TRUE);
    // lv_port_indev_init();
    lv_indev_t * mouse = lv_sdl_mouse_create();
    // lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    // lv_indev_t * keyboard = lv_sdl_keyboard_create();
    // SDL创建线程
    // SDL_CreateThread(tick_thread, "tick", NULL);


    SDL_CreateThread(lvgl_thread, "lvgl", NULL);
}


static lv_obj_t * label;

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    /*Refresh the text*/
    lv_label_set_text_fmt(label, "%"LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_example_get_started_4(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label above the slider*/
    label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_CENTER, 0, -15);    /*Align top of the slider*/
}

int SDL_main(int argc, char* argv[]) {
    // sdl_port_init();
    lv_init();
    lv_hal_init();

    printf("Hello, World!\n");

    lv_obj_t * page0= lv_obj_create(lv_scr_act());
    lv_obj_center(page0);
    lv_obj_set_size(page0, 480, 320);

    lv_obj_t *labe = lv_label_create(page0);
    lv_label_set_text(labe,"hello world!\n");
    lv_obj_set_align(labe,LV_ALIGN_TOP_MID);


    lv_obj_t *btn = lv_btn_create(page0);
    lv_obj_set_align(btn,LV_ALIGN_BOTTOM_MID);
    lv_obj_t *labe1 = lv_label_create(btn);
    lv_label_set_text(labe1,"1");
    lv_example_get_started_4();

    sdl_event();



    return 0;
}