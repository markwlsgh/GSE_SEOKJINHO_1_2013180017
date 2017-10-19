#pragma once

#include "Object.h"

// 길찾기 알고리즘 등 여러가지가 들어감
// 이 클래스가 뚱뚱해지고 내용이 많아질 것임.

class SceneMgr
{
private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	int m_objectCnt;
public:
	SceneMgr();
	~SceneMgr();

	// 오브젝트 생성
	void CreateObject(int x, int y);
	// 오브젝트 업데이트, 겟, 
	void UpdateAllObject();
	//Object Get();
	int GetObjectCnt() { return m_objectCnt; }
	Object* GetObjectToSceneMgr(int idx) { return m_objects[idx]; }
};

