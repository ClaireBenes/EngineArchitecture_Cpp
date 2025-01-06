#pragma once

#include <string>
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "GameTool/Scene.h"
#include "Time.h"

class Engine
{
public:
	Engine(std::string pTitle, std::vector<Scene*> pScene);
	~Engine();

	//functions
	void Initialize();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();

private:
	//variables
	std::string mTitle = "The Title";
	std::vector<Scene*> mScenes{};
	Window* mWindow{};
	Renderer* mRenderer{};

	bool mIsRunning = true;
	int mLoadedScene = 0;

};

