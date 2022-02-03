#include "Room.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
Player player;

void showMaze(vector <Room> mtx, int SIZE) {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			mtx[SIZE * y + x].repr(player.GetPosX(), player.GetPosY());
		}
		std::cout << '\n';
	}
	std::cout << endl;
}


int main()
{
	int SIZE;
	std::cout << "Size of the maze: ";
	cin >> SIZE;
	std::cout << endl;
	vector <Room> maze;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			maze.push_back(Room(j, i));
		}
	}
	showMaze(maze, SIZE);
	return 0;
}