#pragma once
#include "singletonBase.h"
class cameraManager:public singletonBase<cameraManager>
{
private:
	
	HDC _cameraDC;			//�׷��� dc
	HBITMAP _hbit;			//bit��
	HBITMAP _oldHbit;		//oldBit��

	int _Width, _Height;
	//ī�޶��� ��ġ�� ������ xy����
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

