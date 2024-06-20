#include "drone.h"

drone_t initDrone(int x, int y, int cartsize){
    drone_t drone;
    drone.x = x;
    drone.y = y;
    drone.maxCartSize = cartsize;
    drone.currentCartSize = 0;
    drone.direction = STOP;
    drone.cart = (cart_t*) malloc(sizeof(cart_t) * (cartsize + 1));
    return drone;
}

void initPumpkin( pumpkin_t (*pumpkin)[WIDTH]){
    for(int i = 0; i < HEIGHT-STORAGEHIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            pumpkin[i][j].x = j;
            pumpkin[i][j].y = i; 
            pumpkin[i][j].isRipe = 0;
        }
    }
}