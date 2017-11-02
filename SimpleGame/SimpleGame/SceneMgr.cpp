#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int x , int y) : m_objectCnt(0)
{
	prevTime = timeGetTime();
	m_Renderer = new Renderer(x, y);
}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

void SceneMgr::CreateObject(int x, int y)
{
	if (m_objectCnt < MAX_OBJECTS_COUNT) {
		m_objects[m_objectCnt] = new Object(x, y);
		++m_objectCnt;
	}
}

void SceneMgr::UpdateAllObject(float elapsedTime)
{
	for (int i = 0; i < m_objectCnt; ++i)
		m_objects[i]->SetIsColision(false);
	for (int i = 0; i < m_objectCnt; ++i) {
		for (int j = i+1; j < m_objectCnt; ++j) {
				if (ColisionTest(m_objects[i], m_objects[j]) == true) {
					m_objects[i]->SetIsColision(true);
					m_objects[j]->SetIsColision(true);
				}
		}
	}

	for (int i = 0; i < m_objectCnt; ++i)
	{
		m_objects[i]->Update(elapsedTime);
	}

}

void SceneMgr::DrawAllObject()
{
	if (m_objectCnt != 0) {
		for (int i = 0; i < m_objectCnt; ++i) {
			m_Renderer->DrawSolidRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[i]->GetPositionZ(),
				m_objects[i]->GetSize(), m_objects[i]->GetColorRed(),
				m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(),
				m_objects[i]->GetColorAlpha()); 
		}
	}
}

bool SceneMgr::ColisionTest(Object* a, Object* b)
{
	if (a->GetPositionX() + a->GetHalfSize() < b->GetPositionX() - b->GetHalfSize()
			|| a->GetPositionX() - a->GetHalfSize() > b->GetPositionX() + b->GetHalfSize()) {
//			a->SetIsColision(false);
//			b->SetIsColision(false);
			return false;
		}

		if (a->GetPositionY() + a->GetHalfSize() < b->GetPositionY() - b->GetHalfSize()
			|| a->GetPositionY() - a->GetHalfSize() > b->GetPositionY() + b->GetHalfSize()) {
//			a->SetIsColision(false);
//			b->SetIsColision(false);
			return false;
		}

	return true;
}