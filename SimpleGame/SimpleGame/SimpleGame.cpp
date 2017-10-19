/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
SceneMgr *g_SceneMgr = new SceneMgr;

int g_clickedMouse = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	if (g_SceneMgr->GetObjectCnt() != 0) {
		for (int i = 0; i < g_SceneMgr->GetObjectCnt(); ++i) {
			g_Renderer->DrawSolidRect(g_SceneMgr->GetObjectToSceneMgr(i)->GetPositionX(), g_SceneMgr->GetObjectToSceneMgr(i)->GetPositionY(), g_SceneMgr->GetObjectToSceneMgr(i)->GetPositionZ(),
				g_SceneMgr->GetObjectToSceneMgr(i)->GetSize(), g_SceneMgr->GetObjectToSceneMgr(i)->GetColorRed(),
				g_SceneMgr->GetObjectToSceneMgr(i)->GetColorGreen(), g_SceneMgr->GetObjectToSceneMgr(i)->GetColorBlue(),
				g_SceneMgr->GetObjectToSceneMgr(i)->GetColorAlpha()); // 100 x 100 흰색 사각형 그림
		}
	}
	glutSwapBuffers();
}

void Idle(void)
{
	g_SceneMgr->UpdateAllObject();
	// Renderer Test
	RenderScene();
}

// button
// GLUT_LEFT_BUTTON , GLUT_MIDDLE_BUTTON , GLUT_RIGHT_BUTTON
// state
// GLUT_UP , GLUT_DOWN
// 클릭이나 드래그 같은것이 구현되지 않아서 직접 구현 해야 함.
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		g_clickedMouse = 1;
	if (state == GLUT_UP && g_clickedMouse == 1)
		g_clickedMouse = 2;

	if (g_clickedMouse == 2) {
		//g_Object = new Object(x - (WINDOWSIZE_WIDTH * 0.5f) , (WINDOWSIZE_HEIGHT *0.5f) - y );
		//g_Object->SetPositionX(x - (WINDOWSIZE_WIDTH *0.5f) );
		//g_Object->SetPositionY((WINDOWSIZE_HEIGHT *0.5f) -y);
		g_SceneMgr->CreateObject(x - (WINDOWSIZE_WIDTH * 0.5f), (WINDOWSIZE_HEIGHT *0.5f) - y);
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete g_SceneMgr;
    return 0;
}

