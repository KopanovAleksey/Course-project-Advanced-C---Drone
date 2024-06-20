#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "windows.h"

#define WIDTH 20
#define HEIGHT 15
#define STORAGEHIGHT 4
#define CARTSIZE 3
#define DRONECOUNT 5

#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define DARKGREEN FOREGROUND_GREEN

enum DIRECTION {STOP, LEFT, RIGHT, UP, DOWN};
enum KEYS {KEY_LEFT = 'a', KEY_RIGHT = 'd',
		   KEY_UP = 'w', KEY_DOWN = 's', KEY_STOP = 'f'};


typedef struct drone_t
{
    int x, y;
    int direction;
    struct cart_t *cart;
    size_t currentCartSize;
    size_t maxCartSize;
} drone_t;

typedef struct cart_t {
    int x, y;
} cart_t;

typedef struct pumpkin_t{
    int x, y;
    int isRipe;
} pumpkin_t;

drone_t initDrone(int x, int y, int cartsize);
void initPumpkin( pumpkin_t (*pumpkin)[WIDTH]);
void growPumpkin(pumpkin_t (*pumpkin)[WIDTH]);
int isHarvest(drone_t drone, pumpkin_t (*pumpkin)[WIDTH]);
int isStored(drone_t drone);
void updateFieldSolo(char (*field)[WIDTH], drone_t drone, pumpkin_t (*pumpkin)[WIDTH]);
void updateFieldAI(char (*field)[WIDTH], drone_t drone[DRONECOUNT], pumpkin_t (*pumpkin)[WIDTH]);
void printField(char (*field)[WIDTH]);
void move(drone_t *drone, pumpkin_t (*pumpkin)[WIDTH]);
void changeDirection(drone_t *drone, char key);
void avoidObstacles(drone_t *drone, char (*field)[WIDTH]);
void autoChangeDirection(drone_t *drone, pumpkin_t (*pumpkin)[WIDTH], char (*field)[WIDTH]);
int gameOver(drone_t drone);
