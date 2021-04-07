#include "DXUT.h"
#include "ranking_page.h"
#include "global.h"
#include <atlconv.h>
#include <string>
using namespace std;

RankingPage::RankingPage()
{
	keyCount = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/ranking.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


	D3DXCreateFont(DXUTGetD3D9Device(), 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Arial", &font);

}

RankingPage::~RankingPage()
{
	(*backgroundTex)->Release();
	spr->Release();
	font->Release();
}

void RankingPage::Update()
{
	
	if (keyCount <= 0)
	{
		for (int i = 'A'; i <= 'Z'; i++)
		{
			if ((GetAsyncKeyState(i) & 0x8000) != 0)
			{
				keyCount = 10;
				cname.push_back((char)i);
			}
		}
	}
	else
	{
		keyCount--;
	}
	
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0)
	{
		save();
	}
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
	{
		load();
	}

}

void RankingPage::save()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "ranking.txt", "wt");

	for (int i = 0; i < 5; ++i)
	{
		fprintf(fp, "%s %d\n", name, score);
	}

	fclose(fp);
}

void RankingPage::load()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "ranking.txt", "rt");

	if (fp != nullptr)
	{
		for (int i = 0; i < 5; ++i)
		{
			char cname[128];
			int iscore;
			fscanf_s(fp, "%s %d", name, 128, &iscore);
			strcpy_s<128>(name, cname);
			score = iscore;
		}

		fclose(fp);
	}
}

void RankingPage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();



	char text[] = "가나다라마";
	//int score = 80;
	char cscore[256];
	sprintf(cscore, "%d", score);

	USES_CONVERSION;

	WCHAR* w = A2W(cscore);

	RECT rc = { 100, 200, 500, 500 };
	font->DrawText(NULL, w, -1, &rc, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	rc = { 100, 300, 500, 500 };
	string sname(cname.begin(), cname.end());
	strcpy_s(name, sname.c_str());
	w = A2W(name);
	font->DrawText(NULL, w, -1, &rc, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


}
