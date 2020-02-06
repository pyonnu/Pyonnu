#include "stdafx.h"
#include "Font.h"

HRESULT Font::init()
{
	/*SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	AddFontResource("./Resources/Font/terraria_Korean_Font.ttf");
	HFONT hFont, oldFont;
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("terraria_Korean_Font"));
	oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	TextOut(getMemDC(), 20, 20, "글꼴테스트", strlen("글꼴테스트"));*/

	return S_OK;
}
