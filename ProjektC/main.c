#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "snake_logic.h"
#include <allegro5/allegro_font.h>
#include <time.h>

#define TILE_SIZE 20

void save_to_log(const char* message) {
    FILE* log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "[LOG]: %s\n", message);
        fclose(log_file);
    }
}

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

    int high_score = 0;
    FILE* file = fopen("highscore.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &high_score) == 1) {
        }
        fclose(file);
    }

    double start_speed = 6.0;
    FILE* config_file = fopen("config.txt", "r");
    if (config_file != NULL) {
        if (fscanf(config_file, "%lf", &start_speed) == 1) {
        }
        fclose(config_file);
    }

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
                        FILE* file_out = fopen("highscore.txt", "w");
                        if (file_out != NULL) {
                            fprintf(file_out, "%d", high_score);
                            fclose(file_out);
                        }
                    }
                    save_to_log("Koniec gry - waz uderzyl w przeszkode lub samego siebie.");

                    FILE* history = fopen("historia.txt", "a");
                    if (history != NULL) {
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        fprintf(history, "[%04d-%02d-%02d %02d:%02d:%02d] Zakonczono gre. Wynik: %d pkt\n",
                            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                            tm.tm_hour, tm.tm_min, tm.tm_sec,
                            game.score);
                        fclose(history);
                    }
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
                        FILE* file_out = fopen("highscore.txt", "w");
                        if (file_out != NULL) {
                            fprintf(file_out, "%d", high_score);
                            fclose(file_out);
                        }
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
            al_clear_to_color(al_map_rgb(34, 139, 34));

            if (!game_started && !game.game_over) {
                al_draw_text(font, al_map_rgb(255, 255, 255), 400, 250, ALLEGRO_ALIGN_CENTER, "SNAKE 5.0");
                al_draw_text(font, al_map_rgb(200, 200, 200), 400, 280, ALLEGRO_ALIGN_CENTER, "Wcisnij S, aby rozpoczac gre");
            }
            else if (game.game_over) {
                al_draw_text(font, al_map_rgb(255, 0, 0), 400, 250, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTER, "Twoj wynik: %d", game.score);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Najlepszy wynik dotychczas: %d", high_score);
                al_draw_text(font, al_map_rgb(200, 200, 200), 400, 320, ALLEGRO_ALIGN_CENTER, "Wcisnij R - Restart");
                al_draw_text(font, al_map_rgb(200, 200, 200), 400, 340, ALLEGRO_ALIGN_CENTER, "Wcisnij ESC - Wyjscie");
            }
            else {
                al_draw_filled_rectangle(game.apple_x * TILE_SIZE, game.apple_y * TILE_SIZE,
                    (game.apple_x + 1) * TILE_SIZE, (game.apple_y + 1) * TILE_SIZE,
                    al_map_rgb(255, 0, 0));

                SnakeSegment* current = game.head;
                while (current != NULL) {
                    al_draw_filled_rectangle(current->x * TILE_SIZE, current->y * TILE_SIZE,
                        (current->x + 1) * TILE_SIZE, (current->y + 1) * TILE_SIZE,
                        al_map_rgb(255, 105, 180));

                    if (current == game.head) {
                        int hx = current->x * TILE_SIZE;
                        int hy = current->y * TILE_SIZE;
                        if (game.dir == DIR_UP) {
                            al_draw_filled_rectangle(hx + 4, hy + 4, hx + 8, hy + 8, al_map_rgb(0, 0, 0));
                            al_draw_filled_rectangle(hx + 12, hy + 4, hx + 16, hy + 8, al_map_rgb(0, 0, 0));
                        }
                        else if (game.dir == DIR_DOWN) {
                            al_draw_filled_rectangle(hx + 4, hy + 12, hx + 8, hy + 16, al_map_rgb(0, 0, 0));
                            al_draw_filled_rectangle(hx + 12, hy + 12, hx + 16, hy + 16, al_map_rgb(0, 0, 0));
                        }
                        else if (game.dir == DIR_LEFT) {
                            al_draw_filled_rectangle(hx + 4, hy + 4, hx + 8, hy + 8, al_map_rgb(0, 0, 0));
                            al_draw_filled_rectangle(hx + 4, hy + 12, hx + 8, hy + 16, al_map_rgb(0, 0, 0));
                        }
                        else if (game.dir == DIR_RIGHT) {
                            al_draw_filled_rectangle(hx + 12, hy + 4, hx + 16, hy + 8, al_map_rgb(0, 0, 0));
                            al_draw_filled_rectangle(hx + 12, hy + 12, hx + 16, hy + 16, al_map_rgb(0, 0, 0));
                        }
                    }
                    current = current->next;
                }
            }

            al_draw_rectangle(5, 5, 795, 595, al_map_rgb(101, 67, 33), 10);

            al_flip_display();
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