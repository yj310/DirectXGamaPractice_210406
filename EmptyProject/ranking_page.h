#pragma once
#include "page.h"
#include <vector>
using namespace std;

class RankingPage : public Page
{
public:

	RankingPage();
	virtual ~RankingPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;

	ID3DXFont* font;

	vector<char> cname;
	char nname[128];

	int keyCount;

	void save();
	void load();

	void Update() override;
	void Render() override;


};