#include "DXUT.h"
#include "player.h"
#include "global.h"

#define PLAYER_WIDTH 6
#define PLAYER_HEIGHT 6

Player::Player()
{
	posX = 0;
	posY = 0;
	speed = 10;

	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/player.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, playerTex);


	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


}

Player::~Player()
{
	(*playerTex)->Release();
	spr->Release();
}

void Player::Update()
{ 
	if (posX < 0)
		posX = 0;
	if (posX >= FLOOR_WIDTH)
		posX = FLOOR_WIDTH - 1;
	if (posY < 0)
		posY = 0;
	if (posY >= FLOOR_HEIGHT)
		posY = FLOOR_HEIGHT - 1;
}

void Player::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { (float)GAME_X + posX - (PLAYER_WIDTH / 2), (float)GAME_Y + posY - (PLAYER_HEIGHT / 2), 0 };
	spr->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();
}
