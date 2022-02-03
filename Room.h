#pragma once
#include <iostream>
#include "Player.h"
#include <string>
class Room{
private:
	int PosX = 0;
	int PosY = 0;
	bool visible = true;
	const std::string sigil = " ";
public:
	Room(int x, int y) {
		PosX = x;
		PosY = y;
	}

	void SetVisible() {visible = false;}
	void SetX(int x) {PosX = x;}
	void SetY(int y) {PosY = y;}

	void repr(int PlayerPosX, int PlayerPosY) {
		if (PlayerPosX == PosX and PlayerPosY == PosY) {
			std::cout << "{" + sigil + "}";
		}
		else {
			std::cout << '[' + sigil + ']';
		}
	}
};