#pragma once

#include "Object.h"
#include "Renderer.h"
// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

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

	// ������Ʈ ����
	void CreateObject(int x, int y);
	// ������Ʈ ������Ʈ, ��, 
	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();
	// Get();
	int GetObjectCnt() { return m_objectCnt; }

	//Set()
	void SetRenderer(int x, int y) { m_Renderer = new Renderer(500, 500); }
};

