#include "../include/snake_logic.h"
#include <stdlib.h> 

void init_game(SnakeGame* game) {
    game->dir = DIR_RIGHT;
    game->score = 0;
    game->game_over = false;
    game->apple_x = 15;
    game->apple_y = 10;

    SnakeSegment* new_head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    if (new_head != NULL) {
        new_head->x = 10;
        new_head->y = 10;
        new_head->next = NULL;
    }

    game->head = new_head;
}

void free_game(SnakeGame* game) {
    SnakeSegment* current = game->head;
    while (current != NULL) {
        SnakeSegment* next_segment = current->next;
        free(current);
        current = next_segment;
    }
    game->head = NULL;
}

void move_snake(SnakeGame* game) {
    if (game->game_over || game->head == NULL) return;

    int new_x = game->head->x;
    int new_y = game->head->y;

    switch (game->dir) {
    case DIR_UP:    new_y -= 1; break;
    case DIR_DOWN:  new_y += 1; break;
    case DIR_LEFT:  new_x -= 1; break;
    case DIR_RIGHT: new_x += 1; break;
    }

    if (new_x < 0 || new_x >= 40 || new_y < 0 || new_y >= 30) {
        game->game_over = true;
        return;
    }

    SnakeSegment* check = game->head;
    while (check != NULL) {
        if (check->x == new_x && check->y == new_y) {
            game->game_over = true;
            return;
        }
        check = check->next;
    }

    SnakeSegment* new_head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    new_head->x = new_x;
    new_head->y = new_y;
    new_head->next = game->head;
    game->head = new_head;

    if (new_x == game->apple_x && new_y == game->apple_y) {
        game->score += 10;
        game->apple_x = rand() % 40;
        game->apple_y = rand() % 30;
    }
    else {
        SnakeSegment* current = game->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}