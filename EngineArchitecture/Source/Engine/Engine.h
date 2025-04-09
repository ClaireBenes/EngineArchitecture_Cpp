#pragma once

#include <string>
#include <vector>

#include "Window.h"
#include "Engine/Renderer/IRenderer.h"
#include "GameTool/Scene.h"
#include "Time.h"
#include "GameTool/Utility/Vector/Vector2.h"

class Engine
{
public:
	Engine(std::string pTitle, std::vector<Scene*> pScene, IRenderer::RendererType pRendererType);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine();

	//functions
	void Initialize(IRenderer::RendererType pRendererType);
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();

public:
	static inline bool mInDebugMode = false;
	static inline bool mInWireframeMode = false;

private:
	//variables
	std::string mTitle = "The Title";
	std::vector<Scene*> mScenes{};
	Window* mWindow{};
	IRenderer* mRenderer{};

	bool mIsRunning = true;
	int mLoadedScene = 0;
};

