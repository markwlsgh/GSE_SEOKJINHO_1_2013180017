#pragma once

#include "Object.h"
#include "Renderer.h"
// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

#define MAX_OBJECTS_COUNT 300

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3



class SceneMgr
{

public:
	SceneMgr(int x , int y);
	~SceneMgr();

	// ������Ʈ ����
	int CreateObject(float x, float y, int objectType, int teamType);
	void DeleteObject(int index);
	// ������Ʈ ������Ʈ, ��, 
	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();
	// Get();
	int GetObjectCnt() { return MAX_OBJECTS_COUNT; }
	Object* GetActorObject(int index);

	//Set()
	 bool BoxColisionTest(Object* a, Object* b);
	 void DoColisionTest();

private:
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer* m_Renderer;
	int prevTime;
	int currentTime;

	float enemyCooltime = 0.f;

	int objectType;

	GLuint m_buildingTexture_team1 = 0;
	GLuint m_buildingTexture_team2 = 0;
};

