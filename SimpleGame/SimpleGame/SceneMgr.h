#pragma once

#include "Object.h"
#include "Renderer.h"
// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

#define MAX_OBJECTS_COUNT 10



class SceneMgr
{

public:
	SceneMgr(int x , int y);
	~SceneMgr();

	// ������Ʈ ����
	int CreateObject(int x, int y, int objectType);
	void DeleteObject(int index);
	// ������Ʈ ������Ʈ, ��, 
	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();
	// Get();
	int GetObjectCnt() { return MAX_OBJECTS_COUNT; }
	Object* GetActorObject(int index);

	//Set()
	 bool ColisionTest(Object* a, Object* b);

private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	Object *m_buildingObjects[MAX_OBJECTS_COUNT];
	Object *m_bulletObjects[MAX_OBJECTS_COUNT];
	Object *m_arrowObjects[MAX_OBJECTS_COUNT];

	Renderer* m_Renderer;
	int prevTime;
	int currentTime;

	int objectType;
};

