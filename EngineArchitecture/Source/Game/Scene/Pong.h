#pragma once

#include "Engine/GameTool/Scene.h"
#include "Engine/Renderer.h"
#include "Engine/Time.h"

class Pong : public Scene
{
public:
	Pong();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	//void OnInput(SDL_Event event) override;

private:
	//const objects size
	const float mBallSize = 20;
	const float mPaddleHeight = 100;
	const float mPaddleWidth = 20;

	//speed
	float mPaddleSpeed = 500.0f;
	float mBallSpeedX = -300.0f;
	float mBallSpeedY = 400.0f;

	//score
	int mScorePlayer = 0;
	int mScoreAI = 0;

	//bool
	bool mIsGoingUp = false;
	bool mIsGoingDown = false;
	bool mBallIsMoving = false;

	//Objects
	Rectangle mBall {};
	Rectangle mPaddleRight {};
	Rectangle mPaddleLeft {};
};

