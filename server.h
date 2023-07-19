#ifndef SERVER_H
#define SERVER_H

#define RED_PIN 1
#define GREEN_PIN 16
#define BLUE_PIN 15
#define ON 7
#define OFF 0
#define RED 4
#define GREEN 2
#define BLUE 1
#define PURPLE 5
#define YELLOW 6
#define CYAN 3

int color_cycle[7] = {RED, ON, YELLOW, GREEN, CYAN, BLUE, PURPLE};

void setupSegPins();
void displayValue(int);
void *thread_func(void *);
void *button_thread_func(void *);
void reset_button();
void setup();
void set_color();
void cycle_step();

extern int rgb[3];

#endif