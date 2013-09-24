#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int DIM = 8;
int snake[64][4];
int pellet[2] = {-1, -1};
bool snakeLive = true;

/*int* clone(int *t, int len) {
	int out[len];
	for (int i = 0; i < len; i++) {
		out[i] = t[i];
	} 
	return out;
}*/

int moveFwd(int a) {
	return (a + 1) % DIM;
}

int moveBack(int a) {
	return (a - 1 + DIM) % DIM;
}

void placePellet() {
    bool cont = true;
    int x, y;
    //need to check snake length < DIM^2 to avoid infinite loop
    //though that won't really happen in a real game...
    while (cont) {
          cont = false;
          int a = rand() % (DIM * DIM);
          x = a % DIM;
          y = a / DIM;
          
          for (int i = 0; i < DIM * DIM; i++) {
                if (snake[i][0] == x && snake[i][1] == y) {
                    cont = true;
				    break;
		    	}
		  }
    }
    printf("pellet x=%d y=$d", x, y);
    pellet[0] = x;
    pellet[1] = y;
}


//dir: 1 - up, 2 - right, 3 - down, 4 - left
void updateSnake(int dir) {
	int headPos[4];
	memcpy(&headPos, &snake[0], sizeof(headPos));
	
	//copy previous xy position of head
	headPos[2] = headPos[0];
	headPos[3] = headPos[1];

	//calculate new head position
	switch(dir) {
		case 1: //up
		headPos[1] = moveBack(headPos[1]);
		break;
		case 2: //right
		headPos[0] = moveFwd(headPos[0]);
		break;
		case 3: //down
		headPos[1] = moveFwd(headPos[1]);
		break;
		case 4: //left
		headPos[0] = moveBack(headPos[0]);
		break;
		default:
		return; //don't update snake if the direction is not understood
	}

	//check if snake has hit the pellet
	if (headPos[0] == pellet[0] && headPos[1] == pellet[1]) {
		//snake has hit a pellet, make pellet new head of snake
		int newSnake[64][4];
		for (int i = 0; i < 4; i++) {
			newSnake[0][i] = headPos[i];
		}
		
		for (int i = 1; i < 64; i++) {
			for (int e = 0; e < 4; e++) {
				newSnake[i][e] = snake[i-1][e];
			}
		}
		memcpy(&snake, &newSnake, sizeof(newSnake));
		
		placePellet();

	} else {
	    snake[0][0] = headPos[0];
	    snake[0][1] = headPos[1];
	    snake[0][2] = headPos[2];
	    snake[0][3] = headPos[3];
    
	    for (int i = 1; i < 64; i++) {
	    	if (snake[i][0] != -1) { //don't work on nonexistent snake segments
	    		snake[i][2] = snake[i][0];
	    		snake[i][3] = snake[i][1];
	    	
	    		snake[i][0] = snake[i-1][2];
	    		snake[i][1] = snake[i-1][3];
	    	}
    	}
	}
	 
}

int getKeyboardDir() {
    char c = getchar();
//    printf("input: %c\n", c);
    switch(c) {
        case 'w':
        return 1;
        case 'a':
        return 4;
        case 's':
        return 3;
        case 'd':
        return 2;
    }
	return -1;
}

void drawScreen() {
    int x, y;
    char screenString[(DIM + 1) * DIM];
	for (y = 0; y < DIM; y++) {
		for (x = 0; x < DIM; x++) {
			char pixel = '#';
			if (pellet[0] == x && pellet[1] == y) {
					pixel = 'O';
			}
			for (int i = 0; i < DIM * DIM; i++) {
				if (snake[i][0] == x && snake[i][1] == y) {
					pixel = 'O';
					break;
				}
			}
			//screenString[y*x] = pixel;
			printf("%c", pixel);
		}
		//screenString[y*(DIM+1)] = '\n';
		printf("\n");
	}
	//printf(screenString);
}

int main() {
	for (int i = 0; i < DIM*DIM; i++) {
		for (int e = 0; e < 4; e++) {
			snake[i][e] = -1;
		}
	}
	pellet[0] = 3;
	pellet[1] = 3;
	
	snake[0][0] = 3;
	snake[0][1] = 0;
	snake[0][2] = 3;
	snake[0][3] = 0;

	snake[1][0] = 2;
	snake[1][1] = 0;
	snake[1][2] = 2;
	snake[1][3] = 0;
	
	snake[2][0] = 1;
	snake[2][1] = 0;
	snake[2][2] = 1;
	snake[2][3] = 0;

	snake[3][0] = 0;
	snake[3][1] = 0;
	snake[3][2] = 0;
	snake[3][3] = 0;

	for (int i = 0; i < 2; i++) {
		for (int e = 0; e < 4; e++) {
			printf("%d ", snake[i][e]); 	
		}
		printf("\n");
	}
/*
	for (int i = 0; i < 10; i++) {
		for (int e = 0; e < 4; e++) {
			printf("%d", snake[i][e]); 	
		}
		printf("\n");
	}
*/
   drawScreen();
	while (true) {
		//sleep(1);
		int dir = getKeyboardDir();
		updateSnake(dir);
        drawScreen();		
	}
	
}

