#include "stdafx.h"
#include "Object.h"
#include <Windows.h>

Object::Object(int x, int y) :	m_x(x),
								m_y(y),
								m_z(0),
								m_size(3),
								m_r(1),
								m_g(1),
								m_b(1),
								m_a(1),
								m_speedVx( (rand()%2 -0.5) * 0.1f ),
								m_speedVy( (rand()%2 -0.5) * 0.1f ),
								m_speedVz( (rand()%2 -0.5) * 0.1f )
{
}


Object::~Object()
{
}


void Object::Update()
{
	float elapsedTime = 1.5f;
	// 현재위치 = 이전위치 + 속도 * 시간
	m_x = m_x + m_speedVx * elapsedTime;
	m_y = m_y + m_speedVy * elapsedTime;
	m_z = m_z + m_speedVz * elapsedTime;

	if (m_x >= 250 || m_x <= -250)
		m_speedVx *= -1;
	if (m_y >= 250 || m_y <= -250)
		m_speedVy *= -1;
	if (m_z >= 250 || m_z <= -250)
		m_speedVz *= -1;

}