#pragma once

//Import OpenGL
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include <vector>

#define TRIANGLE	GL_TRIANGLES
#define SQUARE		GL_QUADS

struct Position
{
	float x, y;
};

struct WindowSize
{
	unsigned int width, height;
};

class OpenGL
{
public:
	OpenGL();
	~OpenGL();

	int Init();
	void Draw(unsigned int type, std::vector<Position> Vertices, std::vector<float> color);
	int ShouldClose();
	void Clear();
	void SwapBuffers();
	void PollEvents();
	void CloseWindow();

	void SetKeyCallback(GLFWkeyfun func);

	static void ErrorCallback(int error_code, const char* error_msg);

private:
	int m_width, m_height;
	std::string m_title;
	GLFWwindow *m_window;
	WindowSize *m_windowsize;

};

