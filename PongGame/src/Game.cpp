#include "Game.h"

Game *Game::game;
Game::Game()
{
	//White frame
	m_whiteframe = {
		{-320.0f, -210.0f},
		{ 320.0f, -210.0f},
		{ 320.0f,  210.0f},
		{-320.0f,  210.0f}
	};

	//Second green background
	m_background2 = {
		{-290.0f, -180.0f},
		{ 290.0f, -180.0f},
		{ 290.0f,  180.0f},
		{-290.0f,  180.0f}
	};

	//Black Line
	m_blackline = {
		{-5.0f, -180.0f},
		{ 5.0f, -180.0f},
		{ 5.0f,  180.0f},
		{-5.0f,  180.0f}
	};

	//Empty Goal Posts
	m_greenblock1 = {
		{-320.0f, -80.0f},
		{-290.0f, -80.0f},
		{-290.0f,  80.0f},
		{-320.0f,  80.0f}
	};
	m_greenblock2 = {
		{ 290.0f, -80.0f},
		{ 320.0f, -80.0f},
		{ 320.0f,  80.0f},
		{ 290.0f,  80.0f}
	};

	//Players and Ball
	m_Player1 = {
		{-250.0f, -80.0f},
		{-230.0f, -80.0f},
		{-230.0f,  80.0f},
		{-250.0f,  80.0f}
	};

	m_Player2 = {
		{ 230.0f, -80.0f},
		{ 250.0f, -80.0f},
		{ 250.0f, 80.0f},
		{ 230.0f,  80.0f }
	};

	m_Ball = {
		{-10.0f, -10.0f},
		{ 10.0f, -10.0f},
		{ 10.0f,  10.0f},
		{-10.0f,  10.0f}
	};

	//Start Clock
	m_cstart = std::chrono::high_resolution_clock::now();
}

Game::~Game()
{
	opengl.~OpenGL();
	delete game;
}


int Game::Init()
{

	opengl = OpenGL();
	if (opengl.Init())
		return -1;

	opengl.SetKeyCallback(key_callback_thunk);
}

void Game::Draw()
{
	//While Frame
	opengl.Draw(GL_QUADS, m_whiteframe, { 1.0f, 1.0f, 1.0f });

	//Green Background2
	opengl.Draw(GL_QUADS, m_background2, { 0.0f, 1.0f, 0.0f });

	//Black Line
	opengl.Draw(GL_QUADS, m_blackline, { 0.0f, 0.0f, 0.0f });

	//Goal Posts
	opengl.Draw(GL_QUADS, m_greenblock1, { 0.0f, 1.0f, 0.0f });
	opengl.Draw(GL_QUADS, m_greenblock2, { 0.0f, 1.0f, 0.0f });

	//Draw Players
	opengl.Draw(GL_QUADS, m_Player1, { 0.000f, 0.941f, 0.929f });
	opengl.Draw(GL_QUADS, m_Player2, { 0.941f, 0.000f, 0.764f });

	//Draw Ball
	opengl.Draw(GL_QUADS, m_Ball, { 0.941f, 0.905f, 0.000f });

}

void Game::Update()
{
	m_cend = std::chrono::high_resolution_clock::now();
	auto t_diff = std::chrono::duration_cast<std::chrono::milliseconds>(m_cend - m_cstart).count();

	//If >= 1000ms then update ball position
	if (t_diff >= 0)
	{
		//std::cout <<t_diff<<"[ms]" << std::endl;


		//Check for colission
		if (m_Ball[2].y >= 180 || m_Ball[3].y >= 180)
		{
			m_Ball_Vy *= -1;
		}

		if (m_Ball[0].y <= -180 || m_Ball[1].y <= -180)
		{
			m_Ball_Vy *= -1;
		}

		if (m_Ball[1].x >= 290 || m_Ball[2].x >= 290)
		{
			if (m_Ball[3].y >= 80 && m_Ball[0].y <= -80)
				m_Ball_Vx *= -1;
		}

		if (m_Ball[0].x <= -290 || m_Ball[3].x <= -290)
		{
			if (m_Ball[2].y >= 80 && m_Ball[1].y <= -80)
				m_Ball_Vx *= -1;
		}	

		//Ball Collision with players
		//X collison
		if (m_Ball[0].y <= m_Player1[3].y && m_Ball[3].y >= m_Player1[0].y)
		{
			if (m_Ball[0].x <= m_Player1[1].x && m_Ball[0].x > m_Player1[0].x)
			{
				m_Ball_Vx = abs(m_Ball_Vx);
			}
			if (m_Ball[1].x >= m_Player1[0].x && m_Ball[1].x < m_Player1[1].x)
			{
				m_Ball_Vx = -abs(m_Ball_Vx);
			}
		}

		if (m_Ball[0].y <= m_Player2[3].y && m_Ball[3].y >= m_Player2[0].y)
		{
			if (m_Ball[0].x <= m_Player2[1].x && m_Ball[0].x > m_Player2[0].x)
			{
				m_Ball_Vx = abs(m_Ball_Vx);
			}
			if (m_Ball[1].x >= m_Player2[0].x && m_Ball[1].x < m_Player2[1].x)
			{
				m_Ball_Vx = -abs(m_Ball_Vx);
			}
		}

		//Update Direction
		for (int i = 0; i < m_Ball.size(); i++)
		{
			m_Ball[i].x += m_Ball_Vx;
			m_Ball[i].y += m_Ball_Vy;
		}

		//Check for restart
		if (m_Ball[0].x < -350 || m_Ball[1].x > 350)
			m_restart = true;


		//Update Clock
		m_cstart = std::chrono::high_resolution_clock::now();
	}

}

int Game::ShouldClose()
{
	return opengl.ShouldClose();
}

void Game::Clear()
{
	opengl.Clear();
}

void Game::SwapBuffers()
{
	opengl.SwapBuffers();
}

void Game::PollEvents()
{
	opengl.PollEvents();
}

void Game::key_callback_thunk(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	game->key_callback(window, key, scancode, action, mods);
}

void Game::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//std::cout << "Address:" << this << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//Setup Close window need thunking int OpenGL files
	}
	else if (key == GLFW_KEY_W )
	{
		if (m_Player1[3].y < 180)
		{
			//std::cout << "W" << std::endl;
			for (int i = 0; i < m_Player1.size(); i++)
			{
				m_Player1[i].y += 10.0f;
			}
		}
	}
	else if (key == GLFW_KEY_S )
	{
		if (m_Player1[0].y > -180)
		{
			//std::cout << "S" << std::endl;
			for (int i = 0; i < m_Player1.size(); i++)
			{
				m_Player1[i].y -= 10;
			}
		}
	}
	else if (key == GLFW_KEY_UP ) 
	{
		if (m_Player2[3].y < 180)
		{
			//std::cout << "UP" << std::endl;
			for (int i = 0; i < m_Player2.size(); i++)
			{
				m_Player2[i].y += 10;
			}
		}
	}
	else if (key == GLFW_KEY_DOWN)
	{
		if (m_Player2[0].y > -180)
		{
			//std::cout << "DOWN" << std::endl;
			for (int i = 0; i < m_Player2.size(); i++)
			{
				m_Player2[i].y -= 10;
			}
		}
	}
	else if (key == GLFW_KEY_SPACE && m_restart)
	{
		m_Ball[0].x = -10.0f;
		m_Ball[0].y = -10.0f;

		m_Ball[1].x =  10.0f;
		m_Ball[1].y = -10.0f;

		m_Ball[2].x =  10.0f;
		m_Ball[2].y =  10.0f;

		m_Ball[3].x = -10.0f;
		m_Ball[3].y =  10.0f;
	}
}

Game * Game::GetInstance()
{
	// TODO: insert return statement here
	if (game == nullptr)
		game = new Game();

	return game;
}
