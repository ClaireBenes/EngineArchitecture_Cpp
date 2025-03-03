#pragma once

#include <string>
#include <vector>

#include "Window.h"
#include "Engine/Renderer/RendererSDL.h"
#include "GameTool/Scene.h"
#include "Time.h"

class Engine
{
public:
	Engine(std::string pTitle, std::vector<Scene*> pScene);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine();

	//functions
	void Initialize();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();

public:
	static inline bool mInDebugMode = true;

private:
	//variables
	std::string mTitle = "The Title";
	std::vector<Scene*> mScenes{};
	Window* mWindow{};
	RendererSDL* mRenderer{};

	bool mIsRunning = true;
	int mLoadedScene = 0;

};

