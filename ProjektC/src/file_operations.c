#define _CRT_SECURE_NO_WARNINGS
#include "../include/file_operations.h"
#include <stdio.h>
#include <time.h>

void save_to_log(const char* message) {
    FILE* log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "[LOG]: %s\n", message);
        fclose(log_file);
    }
}

int load_high_score(void) {
    int high_score = 0;
    FILE* file = fopen("highscore.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &high_score) == 1) {}
        fclose(file);
    }
    return high_score;
}

void save_high_score(int score) {
    FILE* file_out = fopen("highscore.txt", "w");
    if (file_out != NULL) {
        fprintf(file_out, "%d", score);
        fclose(file_out);
    }
}

double load_config_speed(void) {
    double start_speed = 6.0;
    FILE* config_file = fopen("config.txt", "r");
    if (config_file != NULL) {
        if (fscanf(config_file, "%lf", &start_speed) == 1) {}
        fclose(config_file);
    }
    return start_speed;
}

void save_game_history(int score) {
    FILE* history = fopen("historia.txt", "a");
    if (history != NULL) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(history, "[%04d-%02d-%02d %02d:%02d:%02d] Zakonczono gre. Wynik: %d pkt\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            score);
        fclose(history);
    }
}