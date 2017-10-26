#pragma once

#include "Object.h"
#include "Renderer.h"
// 길찾기 알고리즘 등 여러가지가 들어감
// 이 클래스가 뚱뚱해지고 내용이 많아질 것임.

class SceneMgr
{
private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	int m_objectCnt;
	Renderer* m_Renderer;
	int prevTime;
	int currentTime;
public:
	SceneMgr(int x , int y);
	~SceneMgr();

	// 오브젝트 생성
	void CreateObject(int x, int y);
	// 오브젝트 업데이트, 겟, 
	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();
	// Get();
	int GetObjectCnt() { return m_objectCnt; }

	//Set()
	void SetRenderer(int x, int y) { m_Renderer = new Renderer(500, 500); }
};

