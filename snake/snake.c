#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

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


//dir: 1 - up, 2 - right, 3 - down, 4 - left
void updateSnake(int dir) {
	int headPos[4];
	memcpy(&snake[0], &headPos, sizeof(headPos));
	
	//copy previous xy position of head
	headPos[2] = headPos[0];
	headPos[3] = headPos[1];

	//calculate new head position
	switch(dir) {
		case 1:
		headPos[1] = moveFwd(headPos[1]);
		break;
		case 2:
		headPos[0] = moveFwd(headPos[0]);
		break;
		case 3: 
		headPos[1] = moveBack(headPos[1]);
		break;
		case 4:
		headPos[0] = moveBack(headPos[0]);
	}

	//check if snake has hit the pellet
	/*if (headPos[0] == pellet[0] && headPos[1] == pellet[1]) {
		//snake has hit a pellet, make pellet new head of snake
		int newSnake[64][4];
		for (int i = 0; i < 4; i++) {
			newSnake[1][i] = headPos[i];
		}
		
		for (int i = 1; i < 64; i++) {
			for (int e = 0; e < 4; e++) {
				newSnake[i][e] = snake[i-1][e];
			}
		}
		memcpy(&snake, &newSnake, sizeof(newSnake));

	}*/

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

int getKeyboardDir() {
	return 1;
}

void drawScreen() {
	for (int x = 0; x < DIM; x++) {
		for (int y = 0; y < DIM; y++) {
			char pixel = '#';
			for (int i = 0; i < 3; i++) {
				//printf("%d%d\n", snake[i][0], snake[i][1]);
				if (snake[i][0] == x && snake[i][1] == y) {
					pixel = 'O';
					break;
				}
			}
			printf("%c", pixel);
		}
		printf("\n");
	}
}

int main() {
	for (int i = 0; i < DIM*DIM; i++) {
		for (int e = 0; e < 4; e++) {
			snake[i][e] = -1;
		}
	}
	snake[0][0] = 0;
	snake[0][1] = 0;
	snake[0][2] = 0;
	snake[0][3] = 0;

	snake[1][0] = 1;
	snake[1][1] = 0;
	snake[1][2] = 1;
	snake[1][3] = 0;

/*
	for (int i = 0; i < 10; i++) {
		for (int e = 0; e < 4; e++) {
			printf("%d", snake[i][e]); 	
		}
		printf("\n");
	}
*/
	while (true) {
		sleep(1);
		updateSnake(getKeyboardDir());
		drawScreen();
	}
	
}

