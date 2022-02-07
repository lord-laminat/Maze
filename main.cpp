#include "Room.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
Player player;
int SIZE;
vector <Room> maze;

// showing maze in console
void showMaze() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			maze[SIZE * y + x].repr(player.GetPosX(), player.GetPosY());
		}
		cout << '\n';
	}
	cout << endl;
}

// player's movement function 
void playerMove(char wayChar) {
	int chosenRoomId, way;
	switch (wayChar) {
	case 'u':
		chosenRoomId = SIZE * (player.GetPosY() - 1) + player.GetPosX();
		way = 0;
		break;
	case 'r':
		chosenRoomId = SIZE * player.GetPosY() + player.GetPosX() + 1;
		way = 1;
		break;
	case 'd':
		chosenRoomId = SIZE * (player.GetPosY() + 1) + player.GetPosX();
		way = 2;
		break;
	case 'l':
		chosenRoomId = SIZE * player.GetPosY() + player.GetPosX() - 1;
		way = 3;
		break;
	default:
		cout << "\nYou are just sitting..." << endl;
		return void();
	}
	int yourRoomId = SIZE * player.GetPosY() + player.GetPosX();

	if (maze[yourRoomId].isWall(way) or maze[chosenRoomId].isWall((way + 2) % 4)) {
		char ans;
		cout << "\nThere is wall in front of you. Do you want to blow it? [Y/N]\n > ";
		cin >> ans;
		if (ans == 'y' and player.GetBombs() > 0) {
			player.SetBombs(player.GetBombs() - 1);
			if (maze[chosenRoomId].isExternal()) {
				cout << "\nThis wall is too powerful! You can't blow it." << endl;
				maze[chosenRoomId].SetVisible(true);
			}
			else {
				cout << "\nYou've successfully blown up this wall!" << endl;
				maze[yourRoomId].SetWall(way, 0);
				maze[chosenRoomId].SetWall((way + 2) % 4, 0);
				maze[chosenRoomId].SetVisible(true);
				player.SetPosX(maze[chosenRoomId].GetX());
				player.SetPosY(maze[chosenRoomId].GetY());
			}
		}
		else if (ans == 'y' /* player.GetBombs() <= 0 */) {
			cout << "\n\nYou haven't got enought bombs :(\nYou are just crying..." << endl;
		}
		else /*  if (ans != 'y')  */ {
			cout << "\nYou are just sitting..." << endl;
		}
	}
	else {
		maze[chosenRoomId].SetVisible(true);
		player.SetPosX(maze[chosenRoomId].GetX());
		player.SetPosY(maze[chosenRoomId].GetY());
	}
}

void makeRiver(int cellId, int enter, int lenght, char sig){
	vector <int> ways;
	if (maze[cellId - SIZE].GetType() == ' ') {
		ways.push_back(0);
	}
	if (maze[cellId + 1].GetType() == ' ') {
		ways.push_back(1);
	}
	if (maze[cellId + SIZE].GetType() == ' ') {
		ways.push_back(2);
	}
	if (maze[cellId - 1].GetType() == ' ') {
		ways.push_back(3);
	}

	if (lenght <= 0 or ways.size() == 0) {
		return void();
	}
	maze[cellId].SetType(sig);
	maze[cellId].SetWay((enter + 2) % 4);
	maze[cellId].SetWall(enter, 0);
	maze[cellId].SetWall((enter + 2) % 4, 0);
	int way = ways[rand() % ways.size()];
	if (way % 2 == 0) {
		makeRiver(cellId + (SIZE * (way - 1)), way, lenght - 1, '~');
	}
	else {
		makeRiver(cellId + 2 - way, way, lenght - 1, '~');
	}
}

char down(char ch) {
	if (ch < 91 and ch > 64) {
		ch += 32;
	}
	return ch;
}

void statsShowWindow(Player player) {
	string s = "----------";
	cout << " #" << s << '#' << endl;
	cout << " |" << " Bombs: " << player.GetBombs() << " |" << endl;
	cout << " #" << s << '#' << endl;
}

int main() {
	// size of the maze defining
	cout << "Size of the maze: ";
	cin >> SIZE;
	if (SIZE < 5) { SIZE = 5; }
	SIZE += 2;
	cout << endl;

	// maze forming
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			maze.push_back(Room(j, i, SIZE));
		}
	}

	// maze filling
	// 'A' - arsenal, '*' - estuary
	maze[SIZE * (rand() % (SIZE - 2) + 1) + (rand() % (SIZE - 2) + 1)].SetType('A');
	int estuaryId = SIZE * (rand() % (SIZE - 2) + 1) + (rand() % (SIZE - 2) + 1);
	makeRiver(estuaryId, rand() % 4, SIZE - 1, '*');

	// start room chosing
	player.SetPosX(rand() % (SIZE - 2) + 1);
	player.SetPosY(rand() % (SIZE - 2) + 1);
	maze[SIZE * player.GetPosY() + player.GetPosX()].SetVisible(true);

	// game loop starting
	char way;
	while (true) {
		showMaze();
		statsShowWindow(player);
		cout << "\nYou are standing in the empty room. [U/R/D/L]\n > ";
		cin >> way;
		cout << endl;
		playerMove(down(way));
		maze[SIZE * player.GetPosY() + player.GetPosX()].run(&player);
	}
	return 0;
}