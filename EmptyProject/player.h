#pragma once

class Player
{
public:

	int posX;
	int posY;

	int speed;


	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE spr;

	Player();
	~Player();

	void Update();
	void Render();

	int getPosX() { return posX; }
	int getPosY() { return posY; }
	void move(D3DXVECTOR2 dir) { posX += dir.x; posY += dir.y; }
	void setPos(int x, int y) { posX = x; posY = y; }

	int getSpeed() { return speed; }
	void setSpeed(int speed) { speed = speed; }
	
};