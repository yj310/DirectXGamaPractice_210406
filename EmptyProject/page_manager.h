#pragma once
#include "page.h"

class PageManager
{
public:

	Page* currentPage;

	PageManager();

	void Update();
	void Render();
	void DeleteCurrentPage();


	void CreateTitlePage();
	void CreateFirstGamePage();
	void CreateSecondGamePage();
	void CreateIntroPage();
	void CreateManualPage();
	void CreateRankingPage();
	


};