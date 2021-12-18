#pragma once

#include <common.h>

typedef struct {
    bool start;
    bool select;
    bool a;
    bool b;
    bool up;
    bool down;
    bool left;
    bool right;
} gamepad_state;

void gamepad_init();
bool gamepad_button_sel();
bool gamepad_dir_sel();
void gamepad_set_sel(u8 value);

gamepad_state *gamepad_get_state();
u8 gamepad_get_output();
