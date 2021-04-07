#include "DXUT.h"
#include "super_enemy.h"
#include "global.h"

SuperEnemy::SuperEnemy()
{
	posX = WINDOW_WIDTH - 1;
	posY = WINDOW_HEIGHT - 50;
	enemyTex = new LPDIRECT3DTEXTURE9();
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
		, enemyTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}


SuperEnemy::~SuperEnemy()
{
	(*enemyTex)->Release();
	spr->Release();
}

void SuperEnemy::Update()
{

}

void SuperEnemy::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { (float)GAME_X + posX, (float)GAME_Y + posY, 0 };
	spr->Draw(*enemyTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();
}