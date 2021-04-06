#pragma once
#include "page.h"

class RankingPage : public Page
{
public:

	RankingPage();
	virtual ~RankingPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;


	void Update() override;
	void Render() override;


};