#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include "mapa.h"

// Verifica se um (x,y) está dentro dos limites da matriz
int isValid(Map* m, int x, int y)
{
    return ((x < m->row) && (y < m->column));
}
// Verifica se um (x,y) é uma posição vazia
int isEmpty(Map* m, int x, int y)
{
    return (m->matrix[x][y] == EMPTY);
}
// Verifica se um (x,y) é uma parede
int isWall(Map* m, int x, int y)
{
    return ((m->matrix[x][y] == VERTICAL_WALL) ||
            (m->matrix[x][y] == HORIZONTAL_WALL));
}
// Verifica se um (x,y) é um personagem
int isCharacter(Map* m, char character, int x, int y)
{
    return (m->matrix[x][y] == character);
}
// Verifica se um personagem pode se mover para uma nova posição (x,y) 
int canWalk(Map* m, char c, int x, int y)
{
    return (isValid(m, x, y) && 
            !isWall(m, x, y) &&
            !isCharacter(m, c, x, y));
}
// Realiza cópia do mapa
void copyMap(Map* newMap, Map* m)
{
    newMap->row = m->row;
    newMap->column = m->column;
    allocateMap(newMap);
    
    for(int i = 0; i < m->row; i++)
    {
        strcpy(newMap->matrix[i], m->matrix[i]);
    }
}
// Atualiza a posição de um personagem dentro da matriz
void updatePosition(Map* m, int x, int y, int nextX, int nextY, char c)
{
    m->matrix[x][y] = EMPTY;
    m->matrix[nextX][nextY] = c;
}
// Localiza a posição de um personagem dentro da matriz
void findPosition(Map* m, Position* p, char c)
{
    for(int i = 0; i < m->row; i++)
    {
        for(int j = 0; j < m->column; j++)
        {
            if(isCharacter(m, i, j, c))
            {
                p->x = i;
                p->y = j;
                return;
            }
        }
    }
}
// Verifica se á um personagem na posição (x,y)
int isCharacter(Map* m, int x, int y, char c)
{
	if(m->matrix[x][y] == c)
	{
		return 1;
	}
	return 0;
}
// Ler o mapa de um arquivo
void readMap(Map* m)
{
    FILE* file;
    file = fopen("mapa.txt", "r");
    if(file == 0)
    {
        printf("Erro na leitura do mapa\n");
        exit(1);
    }
    
    fscanf(file, "%d %d", &(m->row), &(m->column));
  
    allocateMap(m);
    
    for(int i = 0; i < m->row; i++)
    {
        fscanf(file, "%s", m->matrix[i]);
    }
    fclose(file);
}
// Aloca a matriz para armazerna o mapa
void allocateMap(Map* m)
{
    m->matrix = new char*[m->row];
    for(int i = 0; i < m->row; i++)
    {
        m->matrix[i] = new char[m->column + 1];
    }
}
// Deleta uma matriz 
void freeMap(Map* m)
{
    for(int i = 0; i < m->row; i++)
    {
        delete [] m->matrix[i];
    }
    delete [] m->matrix;
}

