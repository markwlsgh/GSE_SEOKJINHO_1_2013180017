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

#include "SceneMgr.h"


SceneMgr *g_SceneMgr = NULL;

DWORD g_prevTime = 0;

int g_clickedMouse = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;
	// g_SceneMgr -> UpdateAllActorObject( float(elapsedTime) )
	g_SceneMgr->UpdateAllObject(float(elapsedTime));
	g_SceneMgr -> DrawAllObject();

	glutSwapBuffers();
}

void Idle(void)
{
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

	//Initialize Renderer

   g_SceneMgr = new SceneMgr(500,500);
   //for (int i = 0 ; i< 200; i++)
   //{
   // 오브젝트 생성 x ,y 좌표값.랜덤 생성
   // g_SceneMgr -> AddActorObject(x,y,);
   //}
	g_prevTime = timeGetTime();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_SceneMgr;
    return 0;
}

