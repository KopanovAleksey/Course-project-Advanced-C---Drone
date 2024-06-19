#include "drone.h"

int grownPumpkinCount = 0;

void growPumpkin(pumpkin_t (*pumpkin)[WIDTH]){
    int isFound = 0;
    while (grownPumpkinCount < WIDTH*(HEIGHT-STORAGEHIGHT) && !isFound)
    {
        int startI = rand()%(HEIGHT-STORAGEHIGHT - 1);
        int startJ = rand()%(WIDTH - 1);
        for(int i = startI; i < HEIGHT-STORAGEHIGHT; i++){
            for(int j = startJ; j < WIDTH; j++){
                if(pumpkin[i][j].isRipe == 0){
                    pumpkin[i][j].isRipe = 1;
                    isFound = 1;
                    grownPumpkinCount++;
                    break;
                }
            }
            if(isFound)
                break;
        } 
    }
}

int isHarvest(drone_t drone, pumpkin_t (*pumpkin)[WIDTH]){
    if(drone.y >= HEIGHT - STORAGEHIGHT)
        return 0;
    return (pumpkin[drone.y][drone.x].isRipe == 1) && drone.currentCartSize < drone.maxCartSize;
}

int isStored(drone_t drone){
    return drone.y > HEIGHT - STORAGEHIGHT;
}