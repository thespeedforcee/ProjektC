#ifndef GUI_H
#define GUI_H

#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include "snake_logic.h"

void draw_game_state(SnakeGame* game, int high_score, bool game_started, ALLEGRO_FONT* font);

#endif