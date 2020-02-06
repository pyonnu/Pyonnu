#pragma once
#include"gameNode.h"
class Font : public gameNode
{
	HFONT _myFont;
	HFONT _oldFont;

	HRESULT init();
};

