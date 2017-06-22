#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "QErrorLog.h"

typedef GLFWwindow* Q_GLWIN;


struct QWinKeyInput
{
	int GL_KEY;
	int GL_KEY_TOGGLE;
	void (*QWIN_KEY_EVENT)();
	void ENABLE_EVENT(Q_GLWIN WIN_HANDLE)
	{
		if (glfwGetKey(WIN_HANDLE, this->GL_KEY) == this->GL_KEY_TOGGLE)
			(*QWIN_KEY_EVENT)();
	}
};

class QGLWindow
{
public:
	//-- QWIN CONSTRUCTORS --//
	QGLWindow();
	QGLWindow(unsigned int SCRN_WIDTH, unsigned int SCRN_HEIGHT, char* WIN_TITLE = nullptr, bool WIN_RESIZABLE = false);
	~QGLWindow();

	//-- QWIN PUBLIC METHODS --//
	void QWIN_RENDER(float* BG_RGBA);
	void QWIN_CALLBACK_FRMBUFFSZ(void (*GL_FRMBUFF_SZ)(GLFWwindow*, int, int));
	void QWIN_ADD_KEY_HANDLE(int GL_KEY, int GL_KEY_CONDITION, void (*QWIN_KEY_EVENT)());
private:
	//-- QWIN PRIVATE MEMBERS --//
	unsigned int QWIN_WIDTH;
	unsigned int QWIN_HEIGHT;
	char* QWIN_TITLE;
	bool QWIN_RESIZABLE;
	Q_GLWIN QWIN_HANDLE; 
	std::vector<QWinKeyInput> QWIN_KEY_HANDLES;

	//-- QWIN PRIVATE METHODS --//
	int GL_CONTEXT_INIT(const int GL_VS_MAJ, const int GL_VS_MIN);
	void QWIN_PROCESS_INPUT(Q_GLWIN WIN_HANDLE);
};

