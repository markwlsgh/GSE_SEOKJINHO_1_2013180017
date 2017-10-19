#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr() : m_objectCnt(0)
{
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::CreateObject(int x, int y)
{
	if (m_objectCnt < MAX_OBJECTS_COUNT) {
		m_objects[m_objectCnt] = new Object(x, y);
		++m_objectCnt;
	}
}

void SceneMgr::UpdateAllObject()
{
	for (int i = 0; i < m_objectCnt; ++i)
	{
		m_objects[i]->Update();
	}
}

