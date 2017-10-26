#include "stdafx.h"
#include "Object.h"
#include <Windows.h>

Object::Object(int x, int y) :	m_x(x),
								m_y(y),
								m_z(0),
								m_size(20),
								m_r(1),
								m_g(1),
								m_b(1),
								m_a(1),
								m_speedVx( (rand()%100 -50) ),
								m_speedVy( (rand()%100 -50) ),
								m_speedVz( (rand()%100 -50) )
{
}


Object::~Object()
{
}


void Object::Update(float elapsedTime)
{
	// elapsed time * 0.001f
	float pixelPerSecond = elapsedTime * 0.001f ;
	// 현재위치 = 이전위치 + 속도 * 시간
	m_x = m_x + m_speedVx * pixelPerSecond;
	m_y = m_y + m_speedVy * pixelPerSecond;
	m_z = m_z + m_speedVz * pixelPerSecond;

	if (m_x >= 250 || m_x <= -250)
		m_speedVx *= -1;
	if (m_y >= 250 || m_y <= -250)
		m_speedVy *= -1;
	if (m_z >= 250 || m_z <= -250)
		m_speedVz *= -1;

}

bool Object::isColide(Object& a, Object& b)
{
	if (a.m_x + m_size < b.m_x - m_size)
		return false;

	else if (a.m_x - m_size > b.m_x + m_size)
		return false;

	else if (a.m_y + m_size < b.m_y - m_size)
		return false;

	else if (a.m_y - m_size > b.m_y + m_size)
		return false;

	return true;
}