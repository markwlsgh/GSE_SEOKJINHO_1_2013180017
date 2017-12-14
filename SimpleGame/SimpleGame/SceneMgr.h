#pragma once

#include "Object.h"
#include "Renderer.h"
#include "Sound.h"
// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

#define MAX_OBJECTS_COUNT 300

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

#define LEVEL_GOD 0
#define LEVEL_SKY 0.1
#define LEVEL_GROUND 0.2
#define LEVEL_UNDERGROUND 0.3


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
	 void DoFrameUpdate(float elapsedTime);

private:
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer* m_Renderer;
	Sound* m_Sound;
	int prevTime;
	int currentTime;

	float enemyCooltime = 0.f;
	float m_shakeTime = 0.f;
	float m_textColor[3]; //r, g, b
	float m_textTime = 0.f;
	float m_climateTime;
	int textColorR = 5;
	int textColorG = 1;
	int textColorB = 9;
	float moveTexture = 0.f;

	bool m_Start = true;
	bool m_isShake = false;
	int SoundEffect;
	int createSound_enemy;
	int createSound_my;

	int objectType;

	GLuint m_buildingTexture_team1 = 0;
	GLuint m_buildingTexture_team2 = 0;
	GLuint m_charactorTexture_team1 = 0;
	GLuint m_charactorTexture_team2 = 0;
	GLuint m_backgroundTexture = 0;
	GLuint m_particleTexture = 0;
	GLuint m_enemyParticleTexture = 0;
	GLuint m_climateTexture = 0;
};

