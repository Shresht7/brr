#ifndef HELPERS_H
#define HELPERS_H

void sleep(int duration);

int contains(char *input, char *str);

int get_random_number_between(int lower, int upper);

int key_pressed();
int get_pressed_key();
void set_terminal_mode();
void reset_terminal_mode();

#endif HELPERS_H
