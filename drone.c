#include "drone.h"

int main(int argc, char const *argv[])
{
    int GAMEMODE;
    printf("Hello! This is Drone agricultural drone simulator !\n");
	printf("Rules:\n1)'w','a','s','d' - for move;\n2)'f' - for exit.\n");
	printf("Select game option:\n1)Solo harvest\n2)Automatic harvest\n");
	printf("Gamemode: ");
	char c;
	while(c != '1' && c != '2'&& c != 'f')
		scanf("%c", &c);
        
	switch (c)
	{
	case '1':
		GAMEMODE = 1;
        break;
	case '2':
		GAMEMODE = 2;
        break;
    case 'f':
		return 0;
	}

    system("cls");

    
    drone_t player = initDrone(WIDTH/2, HEIGHT - STORAGEHIGHT + 1, 100);
    drone_t drone[DRONECOUNT];
    for(int i = 0; i < DRONECOUNT; i++){
        drone[i] = initDrone(i * WIDTH/DRONECOUNT + 1, HEIGHT - STORAGEHIGHT + 1, CARTSIZE);
    }
    
    char field[HEIGHT][WIDTH];

    pumpkin_t pumpkin[HEIGHT - STORAGEHIGHT][WIDTH];
    initPumpkin(pumpkin);

    char key;
    int pumpkinSpawnRate = 2;
    int score = 0;
    while (!gameOver(player) && key != KEY_STOP && score < (HEIGHT - STORAGEHIGHT)*WIDTH){
        system("cls");
        printf("SCORE: %d\n", score);

        if(pumpkinSpawnRate == 2){
            pumpkinSpawnRate = 0;
            growPumpkin(pumpkin);
        } else
            pumpkinSpawnRate++;

        if(GAMEMODE == 1){
            if(kbhit()){
                key = tolower(getch());
                changeDirection(&player, key);
		    }
            if(isStored(player)){
                score += player.currentCartSize;
                player.currentCartSize = 0;
            }
            move(&player, pumpkin);
            updateFieldSolo(field, player, pumpkin);
        }
        if(GAMEMODE == 2){
            for(int i = 0; i < DRONECOUNT; i++){
                if(kbhit())
		 	        key = tolower(getch());
                autoChangeDirection(&(drone[i]), pumpkin, field);
                if(isStored(drone[i])){
                    score += drone[i].currentCartSize;
                    drone[i].currentCartSize = 0;
                }
                move(&(drone[i]), pumpkin);
                updateFieldAI(field, drone, pumpkin);
            }   
        }
        printField(field);
        Sleep(400);
    
    }
    system("cls");
    printf("Game Over\nSCORE: %d\n", score);
    return 0;
}
