#include "stdafx.h"
#include "Object.h"
#include <Windows.h>

Object::Object() :	x(0),
					y(-250),
					z(0),
					size(10),
					r(1),
					g(0),
					b(1),
					a(1),
					movingSpeed(1.0f),
					speedVx(0.1f),
					speedVy(0.1f),
					speedVz(0.1f)
{
}


Object::~Object()
{
}


void Object::Update()
{
	float elapsedTime = 1.5f;
	// 현재위치 = 이전위치 + 속도 * 시간
	x = x + speedVx * elapsedTime;
	y = y + speedVy * elapsedTime;
	z = z + speedVz * elapsedTime;

	if (x >= 250 || x <= -250)
		speedVx *= -1;
	if (y >= 250 || y <= -250)
		speedVy *= -1;
	if (z >= 250 || z <= -250)
		speedVz *= -1;

}