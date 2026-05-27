#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "snake_logic.h"

#define TILE_SIZE 20

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 10.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    SnakeGame game;
    init_game(&game);

    bool running = true;
    bool redraw = true;
    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            move_snake(&game);

            double moves_per_second = 8.0 + (game.score / 10.0) * 0.5;
            al_set_timer_speed(timer, 1.0 / moves_per_second);

            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:    if (game.dir != DIR_DOWN) game.dir = DIR_UP; break;
            case ALLEGRO_KEY_DOWN:  if (game.dir != DIR_UP) game.dir = DIR_DOWN; break;
            case ALLEGRO_KEY_LEFT:  if (game.dir != DIR_RIGHT) game.dir = DIR_LEFT; break;
            case ALLEGRO_KEY_RIGHT: if (game.dir != DIR_LEFT) game.dir = DIR_RIGHT; break;
            }
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_filled_rectangle(game.apple_x * TILE_SIZE, game.apple_y * TILE_SIZE,
                (game.apple_x + 1) * TILE_SIZE, (game.apple_y + 1) * TILE_SIZE,
                al_map_rgb(255, 0, 0));

            SnakeSegment* current = game.head;
            while (current != NULL) {
                al_draw_filled_rectangle(current->x * TILE_SIZE, current->y * TILE_SIZE,
                    (current->x + 1) * TILE_SIZE, (current->y + 1) * TILE_SIZE,
                    al_map_rgb(0, 255, 0));
                current = current->next;
            }

            al_flip_display();
            redraw = false;
        }
    }

    free_game(&game);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}