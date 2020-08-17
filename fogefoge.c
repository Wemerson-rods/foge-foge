#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

Map map;
Position positionHero;
int pill = 0;

// Define o caminho de um fantasma
int wayGhost(int x, int y, int* nextX, int* nextY) 
{
    int option[4][2] = {
						{ x-1, y },
						{ x+1, y },
						{ x, y-1 },
						{ x, y+1 }
						};
    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        int position = rand() % 4;
        
        if(canWalk(&map, GHOST, option[position][0], option[position][1]))
        {
            *nextX = option[position][0];
            *nextY = option[position][1];
            return 1;
        }
    }
    return 0;
}
// Movimenta o fantasma no mapa
void moveGhost()
{
    Map mapAux;
    copyMap(&mapAux, &map);
	
    for(int i = 0; i < map.row; i++)
    {
        for(int j = 0; j < map.column; j++)
        {
            if(mapAux.matrix[i][j] == GHOST)
            {
                int x;
                int y;
                if(wayGhost(i, j, &x, &y))
                {
                    updatePosition(&map, i, j, x, y, GHOST);
                }
            }
        }
    }
    freeMap(&mapAux);
}
// Verifica se a entrada do teclado é uma das direções de movimentação (w, s, a, d)
int isDirection(char direction)
{
    return(direction == UP ||
           direction == DOWN || 
           direction == LEFT || 
           direction == RIGHT);
}
// Movimenta o heroi no mapa
void moveHero(char direction)
{
    if(isDirection(direction))
    {
        int nextX = positionHero.x;
        int nextY = positionHero.y;
        
        switch(direction)
        {
            case UP:
                nextX--;
                break;
            case DOWN:
                nextX++;
                break;
            case LEFT:
                nextY--;
                break;
            default:
                nextY++;
                break;
        }
        
        if(canWalk(&map, GHOST, nextX, nextY))
        {
            if(isCharacter(&map, PILL, nextX, nextY))
            {
                pill = 1;
            }
            updatePosition(&map, 
                            positionHero.x, positionHero.y, 
                            nextX, nextY, 
                            HERO);
            positionHero.x = nextX;
            positionHero.y = nextY;
        }
    }
}
// Realiza a explosão da pílula
void explod()
{
    if(pill)
    {
        explodPill(positionHero.x, positionHero.y, 0, 1, 2);
        explodPill(positionHero.x, positionHero.y, 0, -1, 2);
        explodPill(positionHero.x, positionHero.y, 1, 0, 2);
        explodPill(positionHero.x, positionHero.y, -1, 0, 2);
    
        pill = 0;
    }
}
// Realiza a explosão da pílula em uma teterminada direção
void explodPill(int x, int y, int nextX, int nextY, int quant)
{
    if(quant == 0)
    {
        return;
    }
    int newX = x + nextX;
    int newY = y + nextY;
    if(!isValid(&map, newX, newY) || 
        isWall(&map, newX, newY))
    {
        return;
    }
    
    map.matrix[newX][newY] = EMPTY;
    explodPill(newX, newY, nextX, nextY, quant -1);

}
// Verifica se é fim de jogo, fim de jogo ocorre quando o heroi e pego pelos fantasmas
int isEnd()
{  
    return !(isCharacter(&map, positionHero.x, positionHero.y, HERO));
}

int main()
{
    readMap(&map);
    findPosition(&map, &positionHero, HERO);
    printMap(&map);
	
    do
    {
        char input;
        scanf(" %c", &input);
        
        moveHero(input);
        if(input == BOMB)
        {
            explod();
        }
        moveGhost();
		printMap(&map);
    
    }while(!isEnd());
    
    freeMap(&map);
    
    return 0;
}
