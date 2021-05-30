#include "OpenGL.h"

#include "Game.h"

OpenGL::OpenGL()
	: m_width(700), m_height(480), m_title("Pong"), m_window(nullptr)
{}


OpenGL::~OpenGL()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

int OpenGL::Init()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Error - Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//Create the window
	if (!(m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr)))
	{
		std::cout << "Error - Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Make Current Context
	glfwMakeContextCurrent(m_window);

	//Set Vsync
	glfwSwapInterval(1);

	glfwSetErrorCallback(ErrorCallback);

	//Return if Succesfull
	return 0;
}

void OpenGL::Draw(unsigned int type, std::vector<Position> Vertices, std::vector<float> color)
{
	glBegin(type);
	glColor3f(color[0], color[1], color[2]);
	//std::cout << "Color" << color[0] << " " << color[1] << " "<< color[2] << std::endl;
	for (int i = 0; i < Vertices.size(); i++)
	{
		glVertex2f(2*Vertices[i].x/m_width, 2*Vertices[i].y/m_height);
		//std::cout << Vertices[i].x << ", " << Vertices[i].y << std::endl;

	}
	glEnd();
}

int OpenGL::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void OpenGL::Clear()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green background
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void OpenGL::PollEvents()
{
	glfwPollEvents();
	glfwGetWindowSize(m_window, &m_width, &m_height);//Get Window Height and Width
}

void OpenGL::CloseWindow()
{
	glfwSetWindowShouldClose(m_window, GLFW_FALSE);
}

void OpenGL::SetKeyCallback(GLFWkeyfun func)
{
	glfwSetKeyCallback(m_window, func);
}

void OpenGL::ErrorCallback(int error_code, const char* error_msg)
{
	std::cout << "GLFW Error:" << error_code
		<< ", Error Message: " << error_msg << std::endl;
}

