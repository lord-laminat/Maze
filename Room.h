#pragma once
#include <random>
#include <iostream>
#include "Player.h"
#include <string>
class Room{
private:
	int PosX = 0;
	int PosY = 0;
	bool visible = false;
	bool external = false;
	int walls[4]{0, 0, 0, 0};
	const std::string sigil = " ";

	void shuffle(int* arr)
	{
		srand(time(NULL));
		for (int i = 4 - 1; i >= 1; i--)
		{
			int j = rand() % (i + 1);

			int tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
		}
	}

public:
	// constructors
	Room() {}
	Room(const Room& room) :
		PosX(room.PosX), PosY(room.PosY), external(room.external), sigil(room.sigil) {}
	
	Room(int x, int y, int SIZE) {
		PosX = x;
		PosY = y;
		if (PosY == 0 or PosY == SIZE - 1 or PosX == 0 or PosX == SIZE - 1) {
			external = true;
		}
		else {
			for (int i = 0; i < std::rand() % 2 + 1; i++) {
				walls[i] = 1;
			}
			shuffle(walls);
		}
	}

	void SetVisible(bool vis) { visible = vis; }
	void SetWall(int wallId, int New) { walls[wallId] = New; }
	void SetX(int x) { PosX = x; }
	void SetY(int y) { PosY = y; }
	bool isExternal() { return external; }
	bool isWall(int num) {
		if (walls[num] != 0 or external) {
			return true;
		}
		else {
			return false;
		}
	}
	int GetX() { return PosX; }
	int GetY() { return PosY; }

	// room's representation
	void repr(int PlayerPosX, int PlayerPosY) {
		if (!external) {
			if (PlayerPosX == PosX and PlayerPosY == PosY) {
				std::cout << "\x1b[32m{\x1b[0m" + sigil + "\x1b[32m}\x1b[0m";
			}
			else if (visible) {
				std::cout << '[' + sigil + ']';
			}
			else {
				std::cout << "   ";
			}
		}
		else {
			std::cout << " # ";
		}
	}
};