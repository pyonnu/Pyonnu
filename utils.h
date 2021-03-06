#pragma once
#define PI 3.141592654f
#define PI2 PI * 2

//각도별 프레임셋팅을 편하게 하기 위한 각도값 매크로
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

namespace SEVENTEEN_UTIL
{
	//거리(빗변) 알아오는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//두 점의 사이각을 알아오는 함수
	float getAngle(float x1, float y1, float x2, float y2);

	LONG getRectWidth(RECT rc);
	LONG getRectHeight(RECT rc);
}