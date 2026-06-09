#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "../include/snake_logic.h"
#include "../include/file_operations.h"
#include "../include/gui.h"

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 10.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    SnakeGame game;
    init_game(&game);
    save_to_log("Uruchomiono gre Snake.");

    int high_score = load_high_score();
    double start_speed = load_config_speed();

    bool running = true;
    bool redraw = true;
    bool game_started = false;
    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (game_started && !game.game_over) {
                bool was_alive = !game.game_over;
                move_snake(&game);

                if (was_alive && game.game_over) {
                    if (game.score > high_score) {
                        high_score = game.score;
                        save_high_score(high_score);
                    }
                    save_to_log("Koniec gry - waz uderzyl w przeszkode lub samego siebie.");
                    save_game_history(game.score);
                }

                double moves_per_second = start_speed + (game.score / 10.0) * 0.6;
                al_set_timer_speed(timer, 1.0 / moves_per_second);
            }
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (!game_started) {
                if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                    game_started = true;
                }
            }
            else if (game.game_over) {
                if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                    free_game(&game);
                    init_game(&game);
                    game_started = false;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    if (game.score > high_score) {
                        high_score = game.score;
                        save_high_score(high_score);
                    }
                    save_to_log("Zamknieto aplikacje klawiszem ESC.");
                    running = false;
                }
            }
            else {
                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    if (game.dir != DIR_DOWN) game.dir = DIR_UP; break;
                case ALLEGRO_KEY_DOWN:  if (game.dir != DIR_UP) game.dir = DIR_DOWN; break;
                case ALLEGRO_KEY_LEFT:  if (game.dir != DIR_RIGHT) game.dir = DIR_LEFT; break;
                case ALLEGRO_KEY_RIGHT: if (game.dir != DIR_LEFT) game.dir = DIR_RIGHT; break;
                }
            }
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            draw_game_state(&game, high_score, game_started, font);
            redraw = false;
        }
    }

    free_game(&game);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(font);

    return 0;
}