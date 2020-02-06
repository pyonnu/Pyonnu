#include "stdafx.h"
#include "MapTool.h"

void setWindowsSize(int x, int y, int width, int height);

HRESULT MapTool::init()
{
	_winsize.x = 1600;
	_winsize.y = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _winsize.x, _winsize.y);
	_backBuffer->init(_winsize.x, _winsize.y);
	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
}

void MapTool::render()
{
}
