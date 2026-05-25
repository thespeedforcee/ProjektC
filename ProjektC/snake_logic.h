#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <stdbool.h>

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct SnakeSegment {
    int x;                       
    int y;                       
    struct SnakeSegment* next;   
} SnakeSegment;

typedef struct {
    SnakeSegment* head;          
    Direction dir;               
    int score;                   
    int apple_x;                
    int apple_y;               
    bool game_over;              
} SnakeGame;

void init_game(SnakeGame* game);
void free_game(SnakeGame* game);

void move_snake(SnakeGame* game);

#endif#pragma once
