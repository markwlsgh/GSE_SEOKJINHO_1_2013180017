#pragma once

#include "Object.h"
#include "Renderer.h"
// 길찾기 알고리즘 등 여러가지가 들어감
// 이 클래스가 뚱뚱해지고 내용이 많아질 것임.

#define MAX_OBJECTS_COUNT 10



class SceneMgr
{

public:
	SceneMgr(int x , int y);
	~SceneMgr();

	// 오브젝트 생성
	int CreateObject(int x, int y, int objectType);
	void DeleteObject(int index);
	// 오브젝트 업데이트, 겟, 
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

