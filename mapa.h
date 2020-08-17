#ifndef _MAPA_H_
#define _MAPA_H_

#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct Map
{
    char** matrix;
    int row = 0;
    int column = 0;
};

struct Position
{
    int x;
    int y;
};

int isValid(Map* m, int x, int y);
int isEmpty(Map* m, int x, int y);
int isWall(Map* m, int x, int y);
int isCharacter(Map* m, char character, int x, int y);
int canWalk(Map* m, char c, int x, int y);
void copyMap(Map* newMap, Map* map);
void updatePosition(Map* m, int x, int y, int nextX, int nextY, char c);
void findPosition(Map* m, Position* p, char c);
int isCharacter(Map* m, int x, int y, char c);
void readMap(Map* m);
void allocateMap(Map* m);
void freeMap(Map* m);

#endif