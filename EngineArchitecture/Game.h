#pragma once

#include <string>
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "Rectangle.h"
#include "Scene.h"
#include "Time.h"

class Game
{
public:
	Game(std::string pTitle, std::vector<Scene*> pScene);

	void Initialize();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();

private:
	std::string mTitle = "The Title";
	std::vector<Scene*> mScenes{};
	Window* mWindow{};
	Renderer* mRenderer{};

	bool mIsRunning = true;
	int mLoadedScene = 0;

};

