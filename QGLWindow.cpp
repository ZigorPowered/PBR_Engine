#include "QGLWindow.h"

QGLWindow::QGLWindow()
{
	if (GL_CONTEXT_INIT(4, 5) < 0)
	{
		QErrorLog CONTEXT_FAIL(2668393, "OPENGL CONTEXT ERROR (GLFW FAILED)", "..");
		CONTEXT_FAIL.OUTPUT_LOG();
	}
	else
	{
		this->QWIN_WIDTH = 800;
		this->QWIN_HEIGHT = 600;
		this->QWIN_TITLE = "QENGINE WINDOW GL VERSION 4.5";
		this->QWIN_RESIZABLE = false;
		this->QWIN_HANDLE = glfwCreateWindow(this->QWIN_WIDTH, this->QWIN_HEIGHT, this->QWIN_TITLE, NULL, NULL);
	
		glfwMakeContextCurrent(this->QWIN_HANDLE);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
}
QGLWindow::QGLWindow(unsigned int SCRN_WIDTH, unsigned int SCRN_HEIGHT, char* WIN_TITLE, bool WIN_RESIZEABLE)
{
	this->QWIN_RESIZABLE = WIN_RESIZEABLE;
	if (GL_CONTEXT_INIT(4, 5) < 0)
	{
		QErrorLog CONTEXT_FAIL(2668393, "OPENGL CONTEXT ERROR (GLFW FAILED)", "..");
		CONTEXT_FAIL.OUTPUT_LOG();
	}
	else
	{
		(this->QWIN_RESIZABLE == true) ? glfwWindowHint(GLFW_RESIZABLE, 1) : glfwWindowHint(GLFW_RESIZABLE, 0);

		this->QWIN_WIDTH = SCRN_WIDTH;
		this->QWIN_HEIGHT = SCRN_HEIGHT;
		this->QWIN_TITLE = (WIN_TITLE == nullptr) ? "QENGINE WINDOW OPENGL VERSION 4.5" : WIN_TITLE;
		this->QWIN_HANDLE = glfwCreateWindow(this->QWIN_WIDTH, this->QWIN_HEIGHT, this->QWIN_TITLE, NULL, NULL);
	
		glfwMakeContextCurrent(this->QWIN_HANDLE);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
}
QGLWindow::~QGLWindow()
{
	glfwTerminate();
}

//-- PUBLIC METHODS --//
void QGLWindow::QWIN_RENDER(float* BG_RGB)
{
	while(!glfwWindowShouldClose(this->QWIN_HANDLE))
	{
		QWIN_PROCESS_INPUT(this->QWIN_HANDLE);

		glClearColor(BG_RGB[0], BG_RGB[1], BG_RGB[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(this->QWIN_HANDLE);
		glfwPollEvents();
	}
}
void QGLWindow::QWIN_CALLBACK_FRMBUFFSZ(void (*GL_FRMBUFF_SZ)(GLFWwindow*, int, int))
{
	glfwSetFramebufferSizeCallback(this->QWIN_HANDLE, GL_FRMBUFF_SZ);
}
void QGLWindow::QWIN_ADD_KEY_HANDLE(int GL_KEY, int GL_KEY_CONDITION, void (*QWIN_KEY_EVENT)())
{
	QWinKeyInput NEW_KEY_HANDLE;
	NEW_KEY_HANDLE.GL_KEY = GL_KEY;
	NEW_KEY_HANDLE.GL_KEY_TOGGLE = GL_KEY_CONDITION;
	NEW_KEY_HANDLE.QWIN_KEY_EVENT = QWIN_KEY_EVENT;
	this->QWIN_KEY_HANDLES.push_back(NEW_KEY_HANDLE);
}

//-- PRIVATE METHODS --//
int QGLWindow::GL_CONTEXT_INIT(const int GL_VS_MAJ, const int GL_VS_MIN)
{
	if (glfwInit() == GLFW_FALSE)
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VS_MAJ);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VS_MIN);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return 0;
}
void QGLWindow::QWIN_PROCESS_INPUT(Q_GLWIN WIN_HANDLE)
{
	for(std::vector<QWinKeyInput>::iterator i = this->QWIN_KEY_HANDLES.begin(); i != this->QWIN_KEY_HANDLES.end(); i++)
		i->ENABLE_EVENT(WIN_HANDLE);
}
