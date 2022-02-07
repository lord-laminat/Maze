#pragma once
#include <random>
#include <iostream>
#include "Player.h"
class Room{
private:
	char type = ' '; // (#) - external, ( ) - empty, (A) - arsenal, (*) - estuary, (~) - river
	int way;
	int PosX = 0;
	int PosY = 0;
	bool visible = false;
	int walls[4]{0, 0, 0, 0};

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
	Room(int x, int y, int SIZE) {
		PosX = x;
		PosY = y;
		if (PosY == 0 or PosY == SIZE - 1 or PosX == 0 or PosX == SIZE - 1) {
			type = '#';
		}
		else {
			for (int i = 0; i < std::rand() % 2 + 1; i++) {
				walls[i] = 1;
			}
			shuffle(walls);
		}
	}
	
	// getters and setters
	void SetVisible(bool vis) { visible = vis; }
	void SetWall(int wallId, int New) { walls[wallId] = New; }
	void SetX(int x) { PosX = x; }
	void SetY(int y) { PosY = y; }
	void SetWay(int n) { way = n; }
	void SetType(char ch) { type = ch; }
	bool isExternal() {
		if (type == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	bool isWall(int n) {
		if (walls[n] != 0 or type == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	int GetX() { return PosX; }
	int GetY() { return PosY; }
	char GetType() { return type; }

	// room's representation
	void repr(int PlayerPosX, int PlayerPosY) {
		std::string s1;
		std::string s2;
		if (PlayerPosX == PosX and PlayerPosY == PosY) {
			s1 = "\x1b[32;21m{\x1b[0m";
			s2 = "\x1b[32;21m}\x1b[0m";
		}
		else {
			s1 = "[";
			s2 = "]";
		}

		if (false/* !visible */) {
			std::cout << "   ";
		}
		else if (type == '#') {
			std::cout << " # ";
		}
		else if (type == 'A') {
			std::cout << s1 << "\x1b[21;33mA\x1b[0m" << s2;
		}
		else if (type == '*') {
			std::cout << s1 << "\x1b[36m*\x1b[0m" << s2;
		}
		else if (type == ' ') {
			std::cout << s1 << ' ' << s2;
		}
		else if (type == '~') {
			std::cout << s1 << "\x1b[21;36m~\x1b[0m" << s2;
		}
	}

	// room's function
	void run(Player *player) {
		switch (type) {
		case 'A':
			(*player).SetBombs(3);
			break;
		case '~':
			switch (way) {
			case 0:
				player->SetPosY(player->GetPosY() - 1);
				break;
			case 1:
				player->SetPosX(player->GetPosX() + 1);
				break;
			case 2:
				player->SetPosY(player->GetPosY() + 1);
				break;
			case 3:
				player->SetPosX(player->GetPosX() - 1);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
};