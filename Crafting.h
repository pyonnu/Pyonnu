#pragma once

#define MaxItem 60
class Crafting
{
private:
	RECT _craftRect1[MaxItem];
	RECT _craftRect2[MaxItem];
	RECT _craftRect3[MaxItem];
	RECT _craftRect4[MaxItem];
	int a;
	int _craftPage;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);
};