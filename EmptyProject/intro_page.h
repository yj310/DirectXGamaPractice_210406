#pragma once
#include "page.h"

class IntroPage : public Page
{
public:

	IntroPage();
	virtual ~IntroPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;


	void Update() override;
	void Render() override;


};