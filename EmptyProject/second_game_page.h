#pragma once
#include "page.h"

class SecondGamePage : public Page
{
public:

	SecondGamePage();
	virtual ~SecondGamePage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;


	void Update() override;
	void Render() override;


};