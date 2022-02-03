#pragma once
class Player
{
private:
	int Bombs = 3;
	int PosX;
	int PosY;
public:
	void SetPosX(int x) { PosX = x; };
	void SetPosY(int y) { PosY = y; };
	void SetBombs(int num) { Bombs = num; };
	int GetPosX() { return PosX; };
	int GetPosY() { return PosY; };
	int GetBombs() { return Bombs; };
};
