#include <stdio.h>
#include <stdbool.h>

int DIM = 8;
int snake[64][4];
int pellet[2] = {-1, -1};
bool snakeLive = true;

int clone(int t[], int len) {
	int out[len];
	for (int i = 0; i < len; i++) {
		out[i] = t[i];
	} 
	return *out;
}

int moveFwd(int a) {
	return (a + 1) % DIM;
}

int moveBack(int a) {
	return (a - 1 + DIM) % DIM;
}

int main() {
	for (int i = 0; i < DIM*DIM; i++) {
		for (int e = 0; e < 4; e++) {
			snake[i][e] = -1;
		}
	}

	
}

//dir: 1 - up, 2 - right, 3 - down, 4 - left
void updateSnake(int dir) {
	int* headPos = clone(snake[0], 4);
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
		break;
	}
	headPos[2] = headPos[0];
	headPos[3] = headPos[1];

	if (headPos[0] == pellet[0] && headPos[1] == pellet[1]) {
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

	}
	 
}



