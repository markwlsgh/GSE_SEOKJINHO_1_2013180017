#pragma once

#include "Object.h"

// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

class SceneMgr
{
private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	int m_objectCnt;
public:
	SceneMgr();
	~SceneMgr();

	// ������Ʈ ����
	void CreateObject(int x, int y);
	// ������Ʈ ������Ʈ, ��, 
	void UpdateAllObject();
	//Object Get();
	int GetObjectCnt() { return m_objectCnt; }
	Object* GetObjectToSceneMgr(int idx) { return m_objects[idx]; }
};

