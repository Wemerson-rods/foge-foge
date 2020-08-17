#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "mapa.h"


char drawGhost[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char drawHero[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char drawPill[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char drawWall[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char drawEmpty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void printMap(Map* m)
{
    for(int i = 0; i < m->row; i++)
    {
        for(int part = 0; part < 4; part++)
        {
            for(int j = 0; j < m->column; j++)
            {
                switch(m->matrix[i][j])
                {
                    case HERO:
                        printf("%s", drawHero[part]);
                        break;
                    case GHOST:
                        printf("%s", drawGhost[part]);
                        break;
                    case EMPTY:
                        printf("%s", drawEmpty[part]);
                        break;
                    case PILL:
                        printf("%s", drawPill[part]);
                        break;
                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        printf("%s", drawWall[part]);
                        break;
                }
            }
            printf("\n");
        } 
    }
}
