#pragma once

#include "OpenGL.h"

#include <chrono>


class Game {
private: Game();
public:
	~Game();

	int Init();
	void Draw();
	void Update();
	int ShouldClose();
	void Clear();
	void SwapBuffers();
	void PollEvents();

	//Static used to call member function bc C doesnt have concept of classes
	static void key_callback_thunk(GLFWwindow *window, int key, int scancode, int action, int mods);
	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static Game* GetInstance();

private:
	OpenGL opengl;
	std::vector<Position> m_whiteframe;
	std::vector<float> m_whitecolor;

	std::vector<Position> m_background2;
	std::vector<float> m_backgroundcolor;

	std::vector<Position> m_blackline;
	std::vector<float> m_blacklinecolor;

	std::vector<Position> m_greenblock1;
	std::vector<Position> m_greenblock2;



	std::vector<Position> m_Player1;
	std::vector<Position> m_Player2;
	std::vector<Position> m_Ball;

	//Player and Ball stuff
	float m_Player1V = 10.0f, m_Player2V = 10.0f;
	float m_Ball_Vx = 5.0f, m_Ball_Vy = 5.0f;

	//Singleton
	static Game *game;

	//Time Stuff
	std::chrono::time_point<std::chrono::steady_clock> m_cstart;
	std::chrono::time_point<std::chrono::steady_clock> m_cend;

	//Restart
	bool m_restart = false;

};

