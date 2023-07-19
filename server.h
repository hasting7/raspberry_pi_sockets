#ifndef SERVER_H
#define SERVER_H

#define RED 15 
#define GREEN 16
#define BLUE 1
#define ON 7;
#define OFF 0;


void setupSegPins();
void displayValue(int);
void *thread_func(void *);
void *button_thread_func(void *);
void reset_button();
void setup();
void set_color();

extern int rgb[3];

#endif