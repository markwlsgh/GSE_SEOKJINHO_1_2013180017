#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int x , int y)
{
	m_Renderer = new Renderer(x, y);

	if (m_Renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Render could not be initailized.\n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = NULL;
	}

	m_buildingTexture_team1 = m_Renderer->CreatePngTexture("./Resource/enemyBuilding.png");
	m_buildingTexture_team2 = m_Renderer->CreatePngTexture("./Resource/MyBuilding.png");
	m_charactorTexture_team1 = m_Renderer->CreatePngTexture("./Resource/enemyChar.png");
	m_charactorTexture_team2 = m_Renderer->CreatePngTexture("./Resource/MyChar.png");
	m_backgroundTexture = m_Renderer->CreatePngTexture("./Resource/background.png");
	m_enemyParticleTexture = m_Renderer->CreatePngTexture("./Resource/Team1Particle.png");
	m_particleTexture = m_Renderer->CreatePngTexture("./Resource/Team2Particle.png");


}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

int SceneMgr::CreateObject(float x, float y, int objectType, int teamType)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, objectType, teamType);
			return i;
		}
	}
}

float particleTime;
void SceneMgr::UpdateAllObject(float elapsedTime)
{
	DoColisionTest();

	DoFrameUpdate(elapsedTime);

	enemyCooltime += elapsedTime * 0.001f;

	//적을 5초마다 한번씩 생성
	if (enemyCooltime > 5.f)
	{
		CreateObject(float( rand() % 250 - 250 ) , float  ( rand() % 200 + 50 ) , OBJECT_CHARACTER, TEAM_1);
		enemyCooltime = 0.f;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL) {
			if (m_objects[i]->GetLife() < 0.0001f || m_objects[i]->GetLifeTime() < 0.0001f)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
			else
			{
				m_objects[i]->Update(elapsedTime);
				// 빌딩이면 총알 생성
				if (m_objects[i]->GetType() == OBJECT_BUILDING)
				{
					if (m_objects[i]->GetLastBullet() > 5.f)
					{
						int bulletID = CreateObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), OBJECT_BULLET, m_objects[i]->GetTeamType());
						m_objects[i]->SetLastBullet(0.f);
						if (bulletID >= 0)
						{
							m_objects[bulletID]->SetParentID(i);
						}
					}
				}
				// 캐릭터이면 화살생성
				else if (m_objects[i]->GetType() == OBJECT_CHARACTER)
				{
					if (m_objects[i]->GetLastArrow() > 3.f)
					{
						int arrowID = CreateObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), OBJECT_ARROW, m_objects[i]->GetTeamType());
						m_objects[i]->SetLastArrow(0.f);
						if (arrowID >= 0)
						{
							m_objects[arrowID]->SetParentID(i);
						}
					}
				}
			}
		}
	}
}

void SceneMgr::DoColisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objects[i] != NULL)
		{
			for (int j = i + 1; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] != NULL && m_objects[i] != NULL && m_objects[j]->GetTeamType() != m_objects[i]->GetTeamType())
				{
					if (BoxColisionTest(m_objects[i], m_objects[j]))
					{
						//빌딩 - 캐릭터 ( building - charactor ) 
						if (m_objects[i]->GetType() == OBJECT_BUILDING  && m_objects[j]->GetType() == OBJECT_CHARACTER)
						{
							m_objects[i]->SetDamage(m_objects[j]->GetLife());
							m_objects[j]->SetLife(0.f);
							collisionCount++;
						}
						else if (m_objects[j]->GetType() == OBJECT_BUILDING && m_objects[i]->GetType() == OBJECT_CHARACTER)
						{
							m_objects[j]->SetDamage(m_objects[i]->GetLife());
							m_objects[i]->SetLife(0.f);
							collisionCount++;
						}
						// 빌딩 - 총알 ( building - bullet ) 
						if (m_objects[i]->GetType() == OBJECT_BUILDING  && m_objects[j]->GetType() == OBJECT_BULLET)
						{
							m_objects[i]->SetDamage(m_objects[j]->GetLife());
							m_objects[j]->SetLife(0.f);
							collisionCount++;
						}
						else if (m_objects[j]->GetType() == OBJECT_BUILDING && m_objects[i]->GetType() == OBJECT_BULLET)
						{
							m_objects[j]->SetDamage(m_objects[i]->GetLife());
							m_objects[i]->SetLife(0.f);
							collisionCount++;
						}
						// 캐릭터 - 총알 ( charactor - bullet ) 
						else if (m_objects[i]->GetType() == OBJECT_CHARACTER && m_objects[j]->GetType() == OBJECT_BULLET)
						{
							m_objects[i]->SetDamage(m_objects[j]->GetLife());
							m_objects[j]->SetLife(0.f);
						}
						else if (m_objects[j]->GetType() == OBJECT_CHARACTER && m_objects[i]->GetType() == OBJECT_BULLET)
						{
							m_objects[j]->SetDamage(m_objects[i]->GetLife());
							m_objects[i]->SetLife(0.f);
						}
						// 빌딩 - 화살 ( building - arrow ) 
						else if (m_objects[i]->GetType() == OBJECT_BUILDING && m_objects[j]->GetType() == OBJECT_ARROW)
						{
							m_objects[i]->SetDamage(m_objects[j]->GetLife());
							m_objects[j]->SetLife(0.f);
						}
						else if (m_objects[j]->GetType() == OBJECT_BUILDING && m_objects[i]->GetType() == OBJECT_ARROW)
						{
							m_objects[j]->SetDamage(m_objects[i]->GetLife());
							m_objects[i]->SetLife(0.f);
						}
						// 캐릭터 - 화살 ( charactor - arrow ) 
						else if (m_objects[i]->GetType() == OBJECT_CHARACTER && m_objects[j]->GetType() == OBJECT_ARROW )
						{
							if (m_objects[j]->GetParentID() != i)
							{
								m_objects[i]->SetDamage(m_objects[j]->GetLife());
								m_objects[j]->SetLife(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->GetParentID() == i)
										{
											m_objects[k]->SetParentID(-1);
										}
									}
								}
							}
						}
						else if (m_objects[j]->GetType() == OBJECT_CHARACTER && m_objects[i]->GetType() == OBJECT_ARROW)
						{
							if (m_objects[i]->GetParentID() != j)
							{
								m_objects[j]->SetDamage(m_objects[i]->GetLife());
								m_objects[i]->SetLife(0.f);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->GetParentID() == j)
										{
											m_objects[k]->SetParentID(-1);
										}
									}
								}
							}

						}
					}
				}
			}
			//if (collisionCount > 0)
			//{
			//}
			//else
			//{

			//	if (m_objects[i] != NULL && m_objects[i]->GetType() == OBJECT_BUILDING)
			//	{
			//		m_objects[i]->SetColor(1, 1, 0, 1);
			//	}
			//}
		}
	}
}

void SceneMgr::DrawAllObject()
{
	//배경 그리기
	m_Renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, m_backgroundTexture, LEVEL_UNDERGROUND);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) 
	{

			if (m_objects[i] != NULL) 
			{
				//drawing building & life gauge
				if (m_objects[i]->GetType() == OBJECT_BUILDING )
				{
					if (m_objects[i]->GetTeamType() == TEAM_1)
					{
						m_Renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_buildingTexture_team1, m_objects[i]->GetFrameX(), m_objects[i]->GetFrameY(), 9, 6, m_objects[i]->GetLevel());
						m_Renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetHalfSize() + 10, 0, m_objects[i]->GetSize(), 2, 1, 0, 0, 1, m_objects[i]->GetGauge(), m_objects[i]->GetLevel());

					}
					else if (m_objects[i]->GetTeamType() == TEAM_2)
					{
						m_Renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_buildingTexture_team2, m_objects[i]->GetFrameX(), m_objects[i]->GetFrameY(), 3, 8, m_objects[i]->GetLevel());
						m_Renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetHalfSize() + 10, 0, m_objects[i]->GetSize(), 2, 0, 0, 1, 1, m_objects[i]->GetGauge(), m_objects[i]->GetLevel());
					}
				}
				// drawing charactor & life gauge
				else if (m_objects[i]->GetType() == OBJECT_CHARACTER)
				{
					if (m_objects[i]->GetTeamType() == TEAM_1)
					{
						m_Renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_charactorTexture_team1, m_objects[i]->GetFrameX() , m_objects[i]->GetFrameY() , 4, 8, m_objects[i]->GetLevel());
						m_Renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetHalfSize() + 10, 0, m_objects[i]->GetSize(), 2, 1, 0, 0, 1, m_objects[i]->GetGauge(), m_objects[i]->GetLevel());

					}
					else if (m_objects[i]->GetTeamType() == TEAM_2)
					{
						m_Renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_charactorTexture_team2 , m_objects[i]->GetFrameX(), m_objects[i]->GetFrameY(), 4, 4, m_objects[i]->GetLevel());
						m_Renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetHalfSize() + 10, 0, m_objects[i]->GetSize(), 2, 0, 0, 1, 1, m_objects[i]->GetGauge(), m_objects[i]->GetLevel());
					}
				}
				// draw bullet particle
				else if (m_objects[i]->GetType() == OBJECT_BULLET)
				{
					m_Renderer->DrawSolidRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[i]->GetPositionZ(),
						m_objects[i]->GetSize(), m_objects[i]->GetColorRed(),
						m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(),
						m_objects[i]->GetColorAlpha(), m_objects[i]->GetLevel());
					if (m_objects[i]->GetTeamType() == TEAM_1)
					{
						m_Renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0,
							m_objects[i]->GetSize(), 1, 1, 1, 1, m_objects[i]->GetMoveDirX() * -10, m_objects[i]->GetMoveDirY() * -10, m_enemyParticleTexture, particleTime);
					}
					else if (m_objects[i]->GetTeamType() == TEAM_2)
					{
						m_Renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0,
							m_objects[i]->GetSize(), 1, 1, 1, 1, m_objects[i]->GetMoveDirX() * -10, m_objects[i]->GetMoveDirY() * -10, m_particleTexture, particleTime);
					}
				}
				else
				{
					m_Renderer->DrawSolidRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0,
						m_objects[i]->GetSize(), m_objects[i]->GetColorRed(),
						m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(),
						m_objects[i]->GetColorAlpha(), m_objects[i]->GetLevel());
				}


			}
	}

}

bool SceneMgr::BoxColisionTest(Object* a, Object* b)
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

void SceneMgr::DoFrameUpdate(float elapsedTime)
{
	particleTime += elapsedTime * 0.001;
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			m_objects[i]->SetFrameTime(m_objects[i]->GetFrameTime() + elapsedTime * 0.001f);
			if (m_objects[i]->GetTeamType() == TEAM_1)
			{
				if (m_objects[i]->GetType() == OBJECT_BUILDING &&  m_objects[i]->GetFrameTime() > 0.1f)
				{
					m_objects[i]->SetFrameX(m_objects[i]->GetFrameX() + 1);
					int tempX = m_objects[i]->GetFrameX();
					tempX %= 6;
					m_objects[i]->SetFrameX(tempX);
					m_objects[i]->SetFrameTime(0);
				}

				else if (m_objects[i]->GetType() == OBJECT_CHARACTER &&  m_objects[i]->GetFrameTime() > 0.1f)
				{
					m_objects[i]->SetFrameX(m_objects[i]->GetFrameX() + 1);
					int tempX = m_objects[i]->GetFrameX();
					tempX %= 5;
					m_objects[i]->SetFrameX(tempX);
					if (tempX == 7)
					{
						m_objects[i]->SetFrameY(m_objects[i]->GetFrameY() + 1);
						int tempY = m_objects[i]->GetFrameY();
						tempY %= 9;
						m_objects[i]->SetFrameY(tempY);
					}
					m_objects[i]->SetFrameTime(0);
				}
			}
			else if (m_objects[i]->GetTeamType() == TEAM_2)
			{
				if (m_objects[i]->GetType() == OBJECT_BUILDING &&  m_objects[i]->GetFrameTime() > 0.1f)
				{
					m_objects[i]->SetFrameX(m_objects[i]->GetFrameX() + 1);
					int tempX = m_objects[i]->GetFrameX();
					tempX %= 4;
					m_objects[i]->SetFrameX(tempX);
					m_objects[i]->SetFrameTime(0);
				}
				else if (m_objects[i]->GetType() == OBJECT_CHARACTER &&  m_objects[i]->GetFrameTime() > 0.1f)
				{
					m_objects[i]->SetFrameX(m_objects[i]->GetFrameX() + 1);
					int tempX = m_objects[i]->GetFrameX();
					int tempY = m_objects[i]->GetFrameY();

					tempX %= 5;
					if (tempX == 4)
					{
						m_objects[i]->SetFrameY(m_objects[i]->GetFrameY() + 1);
						tempY = (m_objects[i]->GetFrameY()) % 2;
						m_objects[i]->SetFrameY(tempY);
					}
					m_objects[i]->SetFrameX(tempX);
					m_objects[i]->SetFrameTime(0);
				}
			}


		}
	}
}