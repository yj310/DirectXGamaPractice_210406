#pragma once
#include "page.h"

class ManualPage : public Page
{
public:

	ManualPage();
	virtual ~ManualPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;


	void Update() override;
	void Render() override;


};