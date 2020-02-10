#pragma once
#include "singletonBase.h"
enum class cameraType
{
	MAPTOOL,PLAY,OPTION
};
class cameraManager:public singletonBase<cameraManager>
{
private:
	cameraType _cameraType;

	HDC _cameraDC;			//그려줄 dc
	HBITMAP _hbit;			//bit맵
	HBITMAP _oldHbit;		//oldBit맵

	HDC _backDC;
	HBITMAP _backHDCBit;
	HBITMAP _oldBackHDCBit;

	RECT _cameraSizeRect;

	POINT _cameraSize;
	//카메라의 위치를 조정할 xy변수
	POINT _pos;
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void render();

	void setCameraPos(float x, float y);
	inline HDC getCameraDC() { return _cameraDC; }
	inline HDC getbackDC() { return _backDC; }
	//inline float getCameraX() { return _x; }
	//inline float getCameraY() { return _y; }

	inline RECT getCameraRect() { return _cameraSizeRect; }

	inline POINT getCameraSize() { return _cameraSize; }
	inline POINT getCameraPos() { return _pos; }

	inline void setCameraSize(POINT cameraSize) { _cameraSize = cameraSize; }
};

