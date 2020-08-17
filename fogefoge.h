#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define BOMB 'b'

int wayGhost(int x, int y, int* nextX, int* nextY); 
void moveGhost();
int isDirection(char direction);
void move(char direction);
void explod();
void explodPill(int x, int y, int nextX, int nextY, int quant);
int isEnd();

#endif