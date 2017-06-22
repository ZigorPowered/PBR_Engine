//-- CPP INCLUDES --//
#include <Windows.h>
//-- OPENGL INCLUDES --//
#include <glad\glad.h>
#include <GLFW\glfw3.h>
//-- QENGINE INCLUDES --//
#include "QGLWindow.h"
#include "QErrorLog.h"

//Win Settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//Win Callbacks

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	float bg[3] = {0.6f, 0.6f,0.6f};
	QGLWindow QEngine_MAIN(SCR_WIDTH, SCR_HEIGHT);
	QEngine_MAIN.QWIN_RENDER(bg);
	return 0;
}