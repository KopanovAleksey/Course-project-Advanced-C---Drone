#include "drone.h"

int pumpkinCount = WIDTH * (HEIGHT - STORAGEHIGHT);

void move(drone_t *drone, pumpkin_t (*pumpkin)[WIDTH]){
	if(drone->direction != STOP){
        for (int i = drone->currentCartSize; i > 0; i--){
            drone->cart[i] = drone->cart[i-1];
        }
        drone->cart[0].x = drone->x;
        drone->cart[0].y = drone->y;
    }
    switch (drone->direction){
		case UP:
            drone->y = drone->y - 1;
			break;
		case DOWN:
            drone->y = drone->y + 1;
			break;
		case LEFT:	
            drone->x = drone->x - 1;
			break;
		case RIGHT:	
            drone->x = drone->x + 1;
			break;
	}

    if(isHarvest(*drone, pumpkin)){
        pumpkin[drone->y][drone->x].isRipe = -1;
        drone->currentCartSize++;
        pumpkinCount--;
    }
}

void changeDirection(drone_t *drone, char key){
	if(key == KEY_UP && drone->direction != DOWN)
		drone->direction = UP;
	if(key == KEY_DOWN && drone->direction != UP)
		drone->direction = DOWN;
	if(key == KEY_LEFT && drone->direction != RIGHT)
		drone->direction = LEFT;
	if(key == KEY_RIGHT && drone->direction != LEFT)
		drone->direction = RIGHT;
}

void avoidObstacles(drone_t *drone, char (*field)[WIDTH]){
    if((drone->direction == UP && (field[drone->y - 1][drone->x] == '%' || field[drone->y - 1][drone->x] == '@' || drone->y - 1 < 0))
        || (drone->direction == DOWN && (field[drone->y + 1][drone->x] == '%' || field[drone->y + 1][drone->x] == '@'|| drone->y + 1 >= HEIGHT))){
        if(field[drone->y][drone->x - 1] != '%' && field[drone->y][drone->x - 1] != '@' && drone->x - 1 >= 0){
            drone->direction = LEFT;
            return;
        }
        else if(field[drone->y][drone->x + 1] != '%' && field[drone->y][drone->x + 1] != '@' && drone->x + 1 < WIDTH){
            drone->direction = RIGHT;
            return;
        }
        else{
            drone->direction = STOP;
            return;
        }
    }

    if((drone->direction == LEFT && (field[drone->y][drone->x - 1] == '%' || field[drone->y][drone->x - 1] == '@'|| drone->x - 1 < 0))
        || (drone->direction == RIGHT && (field[drone->y][drone->x + 1] == '%' || field[drone->y][drone->x + 1] == '@'|| drone->x + 1 >= WIDTH))){
        if(field[drone->y - 1][drone->x] != '%' && field[drone->y - 1][drone->x] != '@'&& drone->y - 1 >= 0){
            drone->direction = UP;
            return;
        }
        else if(field[drone->y + 1][drone->x] != '%' && field[drone->y + 1][drone->x] != '@'&& drone->y + 1 < HEIGHT){
            drone->direction = DOWN;
            return;
        }
        else{
            drone->direction = STOP;
            return;
        }
    }

    if(drone->direction == STOP){
        if(field[drone->y - 1][drone->x] != '%' && field[drone->y - 1][drone->x] != '@'&& drone->y - 1 >= 0){
            drone->direction = UP;
            return;
        }
        if(field[drone->y + 1][drone->x] != '%' && field[drone->y + 1][drone->x] != '@'&& drone->y + 1 < HEIGHT){
            drone->direction = DOWN;
            return;
        }
        if(field[drone->y ][drone->x + 1] != '%' && field[drone->y][drone->x + 1] != '@'&& drone->x + 1 < WIDTH){
            drone->direction = RIGHT;
            return;
        }
        if(field[drone->y ][drone->x - 1] != '%' && field[drone->y][drone->x - 1] != '@'&& drone->x - 1 >= 0){
            drone->direction = LEFT;
            return;
        }
    }
}

void autoChangeDirection(drone_t *drone, pumpkin_t (*pumpkin)[WIDTH], char (*field)[WIDTH]){
    if(drone->currentCartSize == drone->maxCartSize || pumpkinCount <= 0){
        if(drone->direction == LEFT || drone->direction == RIGHT){
            drone->direction = DOWN;
            avoidObstacles(drone, field);
            return;
        }
        if(drone->direction == UP){
            drone->direction = LEFT;
            avoidObstacles(drone, field);
            return;
        }
        if (drone->direction == DOWN){
            avoidObstacles(drone, field);
            return;
        }
    }

    int distance = 1000;
    pumpkin_t *closestP = NULL;

    for(int i = 0; i < HEIGHT-STORAGEHIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(pumpkin[i][j].isRipe == 1 && distance > (abs(drone->x - j) + abs(drone->y - i))){
                closestP = &(pumpkin[i])[j];
                distance = (abs(drone->x - j) + abs(drone->y - i));
            }
        }
    }
    if(closestP == NULL){
        avoidObstacles(drone, field);
        return;
    }

    if(drone->direction == STOP){
        avoidObstacles(drone, field);
    }

    if ((drone->direction == LEFT || drone->direction == RIGHT) 
                                        && drone->y == closestP->y){
        avoidObstacles(drone, field);
        return;
        }
    if ((drone->direction == UP || drone->direction == DOWN) 
                                        && drone->x == closestP->x){
        avoidObstacles(drone, field);
        return;
        }
    if ((drone->direction == LEFT || drone->direction == RIGHT) 
                                        && drone->y != closestP->y){
        if (closestP->y < drone->y){
            drone->direction = UP;
            avoidObstacles(drone, field);
            return;
        }
        else {
            drone->direction = DOWN;
            avoidObstacles(drone, field);
            return;
        }
    }
    if ((drone->direction == UP || drone->direction == DOWN) 
                                        && drone->x != closestP->x){
        if (closestP->x < drone->x){
            drone->direction = LEFT;
            avoidObstacles(drone, field);
            return;
        }
        else {
            drone->direction = RIGHT;
            avoidObstacles(drone, field);
            return;
        }                                        
    }
    if((drone->direction == UP || drone->direction == DOWN)&& drone->x > closestP->x){
        drone->direction = LEFT;
        avoidObstacles(drone, field);
    }
    else if((drone->direction == UP || drone->direction == DOWN)&& drone->x < closestP->x){
        drone->direction = RIGHT;
        avoidObstacles(drone, field);
    }
    else if((drone->direction == LEFT || drone->direction == RIGHT) && drone->y > closestP->y){
        drone->direction = UP;
        avoidObstacles(drone, field);
    }
    else if((drone->direction == LEFT || drone->direction == RIGHT)&& drone->y < closestP->y){
        drone->direction = DOWN;
        avoidObstacles(drone, field);
    }
}