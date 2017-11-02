#include "stdafx.h"
#include "Object.h"
#include <Windows.h>

Object::Object(int x, int y) :
	m_x(x),
	m_y(y),
	m_z(0),
	m_size(30),
	m_speedVx((rand() % 1500 - 750)),
	m_speedVy((rand() % 1500 - 750)),
	m_speedVz((rand() % 1500 - 750)),
	m_isColision(false),
	m_life(1000),
	m_lifeTime(1000)
{
		m_color[0]	= 1.0f;	// red
		m_color[1]	= 1.0f;	// green
		m_color[2]  = 1.0f; // blue
		m_color[3]	= 1.0f; // alpha
}


Object::~Object()
{
}


void Object::Update(float elapsedTime)
{
	m_life -= 0.1f;
	m_lifeTime -= 0.1f;
	// elapsed time * 0.001f
	float pixelPerSecond = elapsedTime * 0.001f ;
	// 현재위치 = 이전위치 + 속도 * 시간
	m_x = m_x + m_speedVx * pixelPerSecond;
	m_y = m_y + m_speedVy * pixelPerSecond;
	m_z = m_z + m_speedVz * pixelPerSecond;

	if (m_x + m_size *0.5 > 250) {
		m_speedVx *= -1;
		m_x = 250 - m_size * 0.5f;
	}
	if (m_x - m_size *0.5 < -250) {
		m_speedVx *= -1;
		m_x = -250 + m_size * 0.5f;
	}	
	if (m_y + m_size *0.5 > 250) {
		m_speedVy *= -1;
		m_y = 250 - m_size * 0.5f;
	}
	if (m_y - m_size *0.5 < -250) {
		m_speedVy *= -1;
		m_y = -250 + m_size * 0.5f;
	}

	if (m_isColision == true)
		SetColor(1, 0, 0, 0);
	if (m_isColision == false)
		SetColor(1, 1, 1, 1);


	//if (m_life <= 0 || m_lifeTime <= 0)
		//delete this;
}
