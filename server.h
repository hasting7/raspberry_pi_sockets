#ifndef SERVER_H
#define SERVER_H

#define RED 15 
#define GREEN 16
#define BLUE 1

void setupSegPins();
void displayValue(int);
void *thread_func(void *);
void *button_thread_func(void *);
void reset_button();
void white();
void setup();

#endif