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

#include "Object.h"

Renderer *g_Renderer = NULL;
Object *g_Object = NULL;

int g_clickedMouse = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	g_Renderer->DrawSolidRect(g_Object->GetPositionX(), g_Object->GetPositionY(), g_Object->GetPositionZ(), g_Object->GetSize(),
		g_Object->GetColorRed(), g_Object->GetColorGreen(), g_Object->GetColorBlue(), g_Object->GetColorAlpha()); // 100 x 100 흰색 사각형 그림

	glutSwapBuffers();
}

void Idle(void)
{
	// Renderer Test
	RenderScene();
	g_Object->Update();
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
		g_Object->SetPositionX((500 + x) * 0.5f);
		g_Object->SetPositionY(y);
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
	glutInitWindowSize(500, 500);
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
	g_Object = new Object(0, 0);


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	g_Object = NULL;
	delete g_Object;
    return 0;
}

