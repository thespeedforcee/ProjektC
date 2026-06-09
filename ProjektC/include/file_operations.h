#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void save_to_log(const char* message);
int load_high_score(void);
void save_high_score(int score);
double load_config_speed(void);
void save_game_history(int score);

#endif