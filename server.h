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


void setupSegPins();
void displayValue(int);
void *thread_func(void *);
void *button_thread_func(void *);
void reset_button();
void setup();
void set_color();

extern int rgb[3];

#endif