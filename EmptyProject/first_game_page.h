#pragma once
#include "page.h"
#include "global.h"
#include "player.h"

class FirstGamePage : public Page
{
public:

	FirstGamePage();
	virtual ~FirstGamePage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* floorTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPD3DXSPRITE spr;
	ID3DXFont* font;

	Player* player;

	bool isSpace;
	bool isVisiting;

	int visitingX;
	int visitingY;

	int myLand;


	DWORD floorP[FLOOR_PIXEL];
	DWORD maskP[FLOOR_PIXEL];

	int map[FLOOR_PIXEL];
	int virtualMap[FLOOR_PIXEL];



	struct Point
	{
		int x;
		int y;
		Point(int x, int y)
			: x(x), y(y) 
		{}
	};




	void Bordering();
	void FloodFill();
	void GetLand();
	void MapUpdate();
	void PlayerMove(D3DXVECTOR2 dir);
	void KeyInput();
	void Update() override;
	void Render() override;


};