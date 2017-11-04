#include "stdafx.h"
#include "Object.h"
#include <Windows.h>

Object::Object(int x, int y) :
	m_x(x),
	m_y(y),
	m_z(0),
	m_size(30),
	m_isColision(false),
	m_lifeTime(1000),
	objectType(0)
{
	m_moveDir[0] = (rand() % 20 - 10)*0.1;
	m_moveDir[1] = (rand() % 20 - 10)*0.1;
	m_moveDir[2] = (rand() % 20 - 10)*0.1;
}


Object::~Object()
{
}


void Object::Update(float elapsedTime)
{
	//m_life -= 0.1f;
	//m_lifeTime -= 0.1f;
	// elapsed time * 0.001f
	float pixelPerSecond = elapsedTime * 0.001f ;
	// 현재위치 = 이전위치 + 속도 * 시간
	if (m_type == OBJECT_CHARACTER) {
		if (m_isColision == true)
			SetColor(1, 0, 0, 0);
		if (m_isColision == false)
			SetColor(1, 1, 1, 1);
	}

		m_x = m_x + m_speed * m_moveDir[0] * pixelPerSecond;
		m_y = m_y + m_speed * m_moveDir[1] * pixelPerSecond;
		m_z = m_z + m_speed * m_moveDir[2] * pixelPerSecond;
	
		if (m_x + m_size *0.5 > 250) {
		m_moveDir[0] *= -1;
		m_x = 250 - m_size * 0.5f;
	}
	if (m_x - m_size *0.5 < -250) {
		m_moveDir[0] *= -1;
		m_x = -250 + m_size * 0.5f;
	}	
	if (m_y + m_size *0.5 > 250) {
		m_moveDir[1] *= -1;
		m_y = 250 - m_size * 0.5f;
	}
	if (m_y - m_size *0.5 < -250) {
		m_moveDir[1] *= -1;
		m_y = -250 + m_size * 0.5f;
	}




}
