#include "DXUT.h"
#include "first_game_page.h"
#include <stack>
using namespace std;

FirstGamePage::FirstGamePage()
{
	player = new Player();
	myLand = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/firstGame_background.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);

	floorTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/floor.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, floorTex);

	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/firstGame_mask.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, maskTex);




	D3DLOCKED_RECT lr;
	RECT rc = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(floorP, p, FLOOR_PIXEL * sizeof(DWORD));
		(*floorTex)->UnlockRect(0);
	}

	if (SUCCEEDED((*maskTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(maskP, p, FLOOR_PIXEL * sizeof(DWORD));
		(*maskTex)->UnlockRect(0);
	}

	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		map[i] = MAP_EMPTY;
	}

	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		map[y * FLOOR_WIDTH + 0] = MAP_EDGE;
		map[y * FLOOR_WIDTH + FLOOR_WIDTH - 1] = MAP_EDGE;
	}

	for (int x = 0; x < FLOOR_WIDTH; ++x)
	{
		map[0 * FLOOR_WIDTH + x] = MAP_EDGE;
		map[(FLOOR_HEIGHT - 1) * FLOOR_WIDTH + x] = MAP_EDGE;
	}
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


	
	D3DXCreateFont(DXUTGetD3D9Device(), 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Arial", &font);
	


	MapUpdate();


}

FirstGamePage::~FirstGamePage()
{
	(*backgroundTex)->Release();
	(*floorTex)->Release();
	(*maskTex)->Release();
	font->Release();
	spr->Release();

	delete player;
}

void FirstGamePage::MapUpdate()
{

	D3DLOCKED_RECT lr;
	RECT rc = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (map[i] == MAP_EMPTY)
			{
				p[i] = maskP[i];
			}
			else if (map[i] == MAP_EDGE)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
			else if (map[i] == MAP_VISITED)
			{
				p[i] = floorP[i];
			}
			else if (map[i] == MAP_VISITING)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 255, 0);
			}
			else if (map[i] == MAP_TEMP)
			{
				p[i] = D3DCOLOR_ARGB(255, 0, 0, 0, 0);
			}

		}
		(*floorTex)->UnlockRect(0);
	}

}

void FirstGamePage::FloodFill()
{
	stack<Point> points;
	points.push(Point(300, 300));

	while (!points.empty())
	{
		Point p = points.top();
		points.pop();

		if (p.x < 0 || p.x >= FLOOR_WIDTH
			|| p.y < 0 || p.y >= FLOOR_HEIGHT)
			continue;

		if (virtualMap[p.y * FLOOR_WIDTH + p.x] == MAP_TEMP)
			virtualMap[p.y * FLOOR_WIDTH + p.x] = MAP_EMPTY;
		else
			continue;

		points.push(Point(p.x - 1, p.y));
		points.push(Point(p.x + 1, p.y));
		points.push(Point(p.x, p.y - 1));
		points.push(Point(p.x, p.y + 1));

	}
}


void FirstGamePage::Bordering()
{
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		for (int x = 0; x < FLOOR_WIDTH; ++x)
		{
			int top_left = map[(y - 1) * FLOOR_WIDTH + x - 1];
			int top = map[(y - 1) * FLOOR_WIDTH + x];
			int top_right = map[(y - 1) * FLOOR_WIDTH + x + 1];

			int left = map[y * FLOOR_WIDTH + x - 1];
			int right = map[y * FLOOR_WIDTH + x + 1];

			int bottom_left = map[(y + 1) * FLOOR_WIDTH + x - 1];
			int bottom = map[(y + 1) * FLOOR_WIDTH + x];
			int bottom_right = map[(y + 1) * FLOOR_WIDTH + x + 1];


			if (y - 1 >= 0)
			{
				if (x - 1 >= 0)
				{
					if (top_left == MAP_EMPTY)
						continue;
				}
				if (top == MAP_EMPTY)
					continue;
				if (x + 1 < FLOOR_WIDTH)
				{
					if (top_right == MAP_EMPTY)
						continue;
				}
			}

			if (x - 1 >= 0)
			{
				if (left == MAP_EMPTY)
					continue;
			}
			if (x + 1 < FLOOR_WIDTH)
			{
				if (right == MAP_EMPTY)
					continue;
			}


			if (y + 1 < FLOOR_HEIGHT)
			{
				if (x - 1 >= 0)
				{
					if (bottom_left == MAP_EMPTY)
						continue;
				}
				if (bottom == MAP_EMPTY)
					continue;
				if (x + 1 < FLOOR_WIDTH)
				{
					if (bottom_right == MAP_EMPTY)
						continue;
				}
			}

			map[y * FLOOR_WIDTH + x] = MAP_VISITED;

		}
	}


	
}


void FirstGamePage::GetLand()
{
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_EMPTY)
			virtualMap[i] = MAP_TEMP;
		else
			virtualMap[i] = map[i];
	}


	FloodFill();


	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (virtualMap[i] == MAP_TEMP)
			map[i] = MAP_VISITED;
		else if (virtualMap[i] == MAP_VISITING)
			map[i] = MAP_EDGE;
		else
			map[i] = virtualMap[i];
	}

	Bordering();

	myLand = 0;
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_VISITED)
			myLand++;
	}
}

void FirstGamePage::PlayerMove(D3DXVECTOR2 dir)
{
	for (int i = 0; i < player->getSpeed(); i++)
	{
		int x = player->getPosX();
		int y = player->getPosY();
		int nextX = x + dir.x;
		int nextY = y + dir.y;
		if (nextX >= 0 && nextX < FLOOR_WIDTH
			&& nextY >= 0 && nextY < FLOOR_HEIGHT)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_EDGE
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
			{
				player->move(dir);
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_EDGE
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
				&& isSpace)
			{
				isVisiting = true;
				visitingX = x;
				visitingY = y;
				map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
				player->move(dir);
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_VISITING
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
				&& isSpace)
			{
				map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
				player->move(dir);
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_VISITING
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
				&& isSpace)
			{
				isVisiting = false;
				player->move(dir);

				GetLand();
			}
		}
	}
}

void FirstGamePage::KeyInput()
{
	// left
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
	{
		isSpace = true;
	}
	else
	{
		isSpace = false;
		if (isVisiting)
		{
			isVisiting = false;
			player->setPos(visitingX, visitingY );
		}
	}

	// left
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	{
		PlayerMove({ -1, 0 });
	}
	// right
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	{
		PlayerMove({ 1, 0 });
	}
	// up
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	{
		PlayerMove({ 0, -1 });
	}
	// down
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	{
		PlayerMove({ 0, 1 });
	}

}

void FirstGamePage::Update()
{
	player->Update();
	KeyInput();
	MapUpdate();
}
#include <atlconv.h>

void FirstGamePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pos = { (float)GAME_X, (float)GAME_Y, 0 };
	spr->Draw(*floorTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();


	player->Render();

	char text[] = "가나다라마";
	float score = 100.512025845;
	char cscore[256];
	sprintf(cscore, "%.1f", score);

	USES_CONVERSION;

	WCHAR* w = A2W(cscore);



	
	RECT rc = { 10, 200, 500, 500 };
	font->DrawText(NULL, w, -1, &rc, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}
