#pragma once

class SuperEnemy
{
public:

	SuperEnemy();
	~SuperEnemy();


	LPDIRECT3DTEXTURE9* enemyTex;
	LPD3DXSPRITE spr;

	int posX;
	int posY;
	int dirX;
	int dirY;

	int xCount;
	int yCount;


	void Update();
	void Render();


};