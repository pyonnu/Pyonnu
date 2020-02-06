#pragma once
#include "singletonBase.h"
class cameraManager:public singletonBase<cameraManager>
{
private:
	
	HDC _cameraDC;			//그려줄 dc
	HBITMAP _hbit;			//bit맵
	HBITMAP _oldHbit;		//oldBit맵

	int _Width, _Height;
	//카메라의 위치를 조정할 xy변수
	float _x, _y;
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void render();

	void setCameraPos(float x, float y);
	inline HDC getCameraDC() { return _cameraDC; }
	inline float getCameraX() { return _x; }
	inline float getCameraY() { return _y; }
	
};

