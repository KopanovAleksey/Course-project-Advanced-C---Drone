#include "drone.h"

int gameOver(drone_t drone){
    if(drone.x == 0 || drone.y == 0 || drone.y == HEIGHT || drone.x == WIDTH)
        return 1;
    return 0;
}

int main(int argc, char const *argv[])
{
    // drone_t drone = initDrone(WIDTH/2, HEIGHT - STORAGEHIGHT + 1);
    drone_t drone[DRONECOUNT];
    char field[HEIGHT][WIDTH];
    for(int i = 0; i < DRONECOUNT; i++){
        drone[i] = initDrone(i * WIDTH/DRONECOUNT, HEIGHT - STORAGEHIGHT + 1);
    }
    pumpkin_t pumpkin[HEIGHT - STORAGEHIGHT][WIDTH];
    initPumpkin(pumpkin);
    char key;
    int pumpkinSpawnRate = 2;
    int score = 0;
    while (/*!gameOver(drone) &&*/ key != KEY_STOP && score < (HEIGHT - STORAGEHIGHT)*WIDTH)
    {
        system("cls");
        printf("SCORE: %d\n", score);

        if(kbhit()){
		 	key = tolower(getch());
		 	// changeDirection(&drone, key);
		}

        if(pumpkinSpawnRate == 2){
            pumpkinSpawnRate = 0;
            growPumpkin(pumpkin);
        } else
            pumpkinSpawnRate++;

        for(int i = 0; i < DRONECOUNT; i++){
            autoChangeDirection(&(drone[i]), pumpkin, field);
            
            if(isStored(drone[i])){
                score += drone[i].currentCartSize;
                drone[i].currentCartSize = 0;
            }
            move(&(drone[i]), pumpkin);
            updateField(field, drone, pumpkin);
        }
        printField(field);
        Sleep(400);
    }
    system("cls");
    printf("Game Over\nSCORE: %d\n", score);
    return 0;
}
