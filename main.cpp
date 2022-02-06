#include "Room.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
Player player;
vector <Room> maze;

// showing maze in console
void showMaze(int SIZE) {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			maze[SIZE * y + x].repr(player.GetPosX(), player.GetPosY());
		}
		cout << '\n';
	}
	cout << endl;
}

// player's movement function 
void playerMove(char wayChar, int SIZE) {
	int chosenRoomId, way;
	switch (wayChar) {
	case 'u':
		chosenRoomId = SIZE * (player.GetPosY() - 1) + player.GetPosX();
		way = 0;
		break;
	case 'r':
		chosenRoomId = SIZE * player.GetPosY() + player.GetPosX() + 1;
		way = 2;
		break;
	case 'd':
		chosenRoomId = SIZE * (player.GetPosY() + 1) + player.GetPosX();
		way = 1;
		break;
	case 'l':
		chosenRoomId = SIZE * player.GetPosY() + player.GetPosX() - 1;
		way = 3;
		break;
	default:
		cout << "\nYou are just sitting..." << endl;
		return void();
	}
	Room yourRoom(player.GetPosX(), player.GetPosY(), SIZE);

	if (yourRoom.isWall(way) or maze[chosenRoomId].isWall((way + 2) % 4)) {
		char ans;
		cout << "\nThere is wall in front of you. Do you want to blow it? [Y/N]\n > ";
		cin >> ans;
		if (ans == 'y' and player.GetBombs() > 0) {
			player.SetBombs(player.GetBombs() - 1);
			if (maze[chosenRoomId].isExternal()) {
				cout << "\nThis wall is too powerful! You can't blow it." << endl;
			}
			else {
				cout << "\nYou've successfully blown up this wall!" << endl;
				yourRoom.SetWall(way, 0);
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
	int SIZE;
	cout << "Size of the maze: ";
	cin >> SIZE;
	SIZE += 2;
	cout << endl;

	// maze forming
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			maze.push_back(Room(j, i, SIZE));
		}
	}

	// start room chosing
	player.SetPosX(rand() % (SIZE - 2) + 1);
	player.SetPosY(rand() % (SIZE - 2) + 1);
	maze[SIZE * player.GetPosY() + player.GetPosX()].SetVisible(true);

	// game loop starting
	char way;
	while (true) {
		showMaze(SIZE);
		statsShowWindow(player);
		cout << "\nYou are standing in the empty room. [U/R/D/L]\n > ";
		cin >> way;
		cout << endl;
		playerMove(down(way), SIZE);
	}
	return 0;
}