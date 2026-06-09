#include "../include/gui.h"
#include <allegro5/allegro_primitives.h>

#define TILE_SIZE 20

void draw_game_state(SnakeGame* game, int high_score, bool game_started, ALLEGRO_FONT* font) {
    al_clear_to_color(al_map_rgb(34, 139, 34));

    if (!game_started && !game->game_over) {
        al_draw_text(font, al_map_rgb(255, 255, 255), 400, 250, ALLEGRO_ALIGN_CENTER, "SNAKE 5.0");
        al_draw_text(font, al_map_rgb(200, 200, 200), 400, 280, ALLEGRO_ALIGN_CENTER, "Wcisnij S, aby rozpoczac gre");
    }
    else if (game->game_over) {
        al_draw_text(font, al_map_rgb(255, 0, 0), 400, 250, ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTER, "Twoj wynik: %d", game->score);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Najlepszy wynik dotychczas: %d", high_score);
        al_draw_text(font, al_map_rgb(200, 200, 200), 400, 320, ALLEGRO_ALIGN_CENTER, "Wcisnij R - Restart");
        al_draw_text(font, al_map_rgb(200, 200, 200), 400, 340, ALLEGRO_ALIGN_CENTER, "Wcisnij ESC - Wyjscie");
    }
    else {
        al_draw_filled_rectangle(game->apple_x * TILE_SIZE, game->apple_y * TILE_SIZE,
            (game->apple_x + 1) * TILE_SIZE, (game->apple_y + 1) * TILE_SIZE,
            al_map_rgb(255, 0, 0));

        SnakeSegment* current = game->head;
        while (current != NULL) {
            al_draw_filled_rectangle(current->x * TILE_SIZE, current->y * TILE_SIZE,
                (current->x + 1) * TILE_SIZE, (current->y + 1) * TILE_SIZE,
                al_map_rgb(255, 105, 180));

            if (current == game->head) {
                int hx = current->x * TILE_SIZE;
                int hy = current->y * TILE_SIZE;
                if (game->dir == DIR_UP) {
                    al_draw_filled_rectangle(hx + 4, hy + 4, hx + 8, hy + 8, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(hx + 12, hy + 4, hx + 16, hy + 8, al_map_rgb(0, 0, 0));
                }
                else if (game->dir == DIR_DOWN) {
                    al_draw_filled_rectangle(hx + 4, hy + 12, hx + 8, hy + 16, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(hx + 12, hy + 12, hx + 16, hy + 16, al_map_rgb(0, 0, 0));
                }
                else if (game->dir == DIR_LEFT) {
                    al_draw_filled_rectangle(hx + 4, hy + 4, hx + 8, hy + 8, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(hx + 4, hy + 12, hx + 8, hy + 16, al_map_rgb(0, 0, 0));
                }
                else if (game->dir == DIR_RIGHT) {
                    al_draw_filled_rectangle(hx + 12, hy + 4, hx + 16, hy + 8, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(hx + 12, hy + 12, hx + 16, hy + 16, al_map_rgb(0, 0, 0));
                }
            }
            current = current->next;
        }
    }

    al_draw_rectangle(5, 5, 795, 595, al_map_rgb(101, 67, 33), 10);
    al_flip_display();
}