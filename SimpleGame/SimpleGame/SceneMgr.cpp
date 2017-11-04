#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int x , int y)
{
	m_Renderer = new Renderer(x, y);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = NULL;
	}
}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

int SceneMgr::CreateObject(int x, int y, int objectType)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (objectType == OBJECT_CHARACTER) {
			if (m_objects[i] == NULL) {
				m_objects[i] = new Object(x, y);
				m_objects[i]->SetObjectType(objectType);
				m_objects[i]->SetColor(1, 1, 1, 1);
				m_objects[i]->SetSpeed(300);
				m_objects[i]->SetSize(10);
				m_objects[i]->SetLife(10);

				return i;
			}
		}
	}
	if (objectType == OBJECT_BUILDING) {
		m_buildingObjects[0] = new Object(x, y);
		m_buildingObjects[0]->SetColor(1, 0, 1, 0);
		m_buildingObjects[0]->SetSize(50);
		m_buildingObjects[0]->SetLife(500);
		m_buildingObjects[0]->SetObjectType(objectType);
		m_buildingObjects[0]->SetSpeed(0);
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (objectType == OBJECT_BULLET) {
			if (m_bulletObjects[i] == NULL) {
				m_bulletObjects[i] = new Object(x, y);
				m_bulletObjects[i]->SetColor(1, 0, 0, 0);
				m_bulletObjects[i]->SetSize(2);
				m_bulletObjects[i]->SetLife(20);
				m_bulletObjects[i]->SetObjectType(objectType);
				m_bulletObjects[i]->SetSpeed(600);
				return i;
			}
		}
	}
	if (objectType == OBJECT_ARROW) {
		m_arrowObjects[0] = new Object(x, y);
		m_arrowObjects[0]->SetColor(0, 1, 0, 0);
		m_arrowObjects[0]->SetSize(2);
		m_arrowObjects[0]->SetLife(10);
		m_arrowObjects[0]->SetObjectType(objectType);
		m_arrowObjects[0]->SetSpeed(100);
	}
}

void SceneMgr::UpdateAllObject(float elapsedTime)
{
	float timer = 0.0f;
	timer += elapsedTime;
	if (timer >= 0.0005f && m_buildingObjects[0] != NULL) {
		CreateObject(m_buildingObjects[0]->GetPositionX(), m_buildingObjects[0]->GetPositionY(), OBJECT_BULLET);
	}
	//총알 update
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_bulletObjects[i] != NULL)
			m_bulletObjects[i]->Update(elapsedTime);
		}

	// 충돌 변수 초기화
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (m_objects[i] != NULL) {
			m_objects[i]->SetIsColision(false);
		}
	// 충돌검사 오브젝트 - 벽
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (m_objects[i] != NULL && m_buildingObjects[0] != NULL) {
				if (ColisionTest(m_objects[i], m_buildingObjects[0]) == true) {
					m_objects[i]->SetIsColision(true);
					m_buildingObjects[0]->SetIsColision(true);
					m_buildingObjects[0]->SetLife(m_buildingObjects[0]->GetLife() - m_objects[i]->GetLife());
					std::cout << " 빌딩 체력 : " << m_buildingObjects[0]->GetLife() << std::endl;
				}
			}
	}
	// 충돌검사 오브젝트 - 총알
	for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (m_objects[i] != NULL && m_bulletObjects[j] != NULL) {
				if (ColisionTest(m_objects[i], m_bulletObjects[j]) == true) {
					m_objects[i]->SetIsColision(true);
					m_objects[i]->SetLife(m_objects[i]->GetLife() - m_bulletObjects[j]->GetLife());
					delete m_bulletObjects[j];
					m_bulletObjects[j] = NULL;
				}
			}
		}
	}


	//빌딩 체력검사
	if (m_buildingObjects[0] != NULL) {
		if (m_buildingObjects[0]->GetLife() < 0.0001f || m_buildingObjects[0]->GetLifeTime() < 0.0001f)
		{
			delete m_buildingObjects[0];
			m_buildingObjects[0] = NULL;
		}
		else m_buildingObjects[0]->Update(elapsedTime);
	}
	// 오브젝트 체력검사
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL) {
			if (m_objects[i]->GetLife() < 0.0001f || m_objects[i]->GetLifeTime() < 0.0001f || m_objects[i]->GetIsColision() == true)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
			else {
				m_objects[i]->Update(elapsedTime);
			}
		}
	}

}

void SceneMgr::DrawAllObject()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (m_objects[i] != NULL) {
				m_Renderer->DrawSolidRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[i]->GetPositionZ(),
					m_objects[i]->GetSize(), m_objects[i]->GetColorRed(),
					m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(),
					m_objects[i]->GetColorAlpha());
			}
		}
		if (m_buildingObjects[0] != NULL) {
			m_Renderer->DrawSolidRect(m_buildingObjects[0]->GetPositionX(), m_buildingObjects[0]->GetPositionY(), m_buildingObjects[0]->GetPositionZ(),
				m_buildingObjects[0]->GetSize(), m_buildingObjects[0]->GetColorRed(),
				m_buildingObjects[0]->GetColorGreen(), m_buildingObjects[0]->GetColorBlue(),
				m_buildingObjects[0]->GetColorAlpha());
		}

		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (m_bulletObjects[i] != NULL) {
				m_Renderer->DrawSolidRect(m_bulletObjects[i]->GetPositionX(), m_bulletObjects[i]->GetPositionY(), m_bulletObjects[i]->GetPositionZ(),
					m_bulletObjects[i]->GetSize(), m_bulletObjects[i]->GetColorRed(),
					m_bulletObjects[i]->GetColorGreen(), m_bulletObjects[i]->GetColorBlue(),
					m_bulletObjects[i]->GetColorAlpha());
			}
		}
}

bool SceneMgr::ColisionTest(Object* a, Object* b)
{
	if (a->GetPositionX() + a->GetHalfSize() < b->GetPositionX() - b->GetHalfSize()
			|| a->GetPositionX() - a->GetHalfSize() > b->GetPositionX() + b->GetHalfSize()) {
			return false;
		}

		if (a->GetPositionY() + a->GetHalfSize() < b->GetPositionY() - b->GetHalfSize()
			|| a->GetPositionY() - a->GetHalfSize() > b->GetPositionY() + b->GetHalfSize()) {
			return false;
		}

	return true;
}

void SceneMgr::DeleteObject(int index)
{
	if (m_objects[index] != NULL) {
		delete m_objects[index];
		m_objects[index] = NULL;
	}
}