#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Time.h"

class Pong : public Scene
{
public:
	Pong();

	void Start(Renderer* pRenderer) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnInput(SDL_Event event) override;
	void Close() override;

private:
	Renderer* mRenderer{};

	float mPaddleSpeed = 500.0f;
	float mBallSpeedX = -300.0f;
	float mBallSpeedY = 400.0f;

	bool mIsGoingUp = false;
	bool mIsGoingDown = false;

	const float mBallSize = 20;
	const float mPaddleHeight = 100;
	const float mPaddleWidth = 20;

	Rectangle mBall = Rectangle({ 400.0 - 20.0f / 2, 400.0f - 20.0f / 2 }, { 20,20 });
	Rectangle mPaddleRight = Rectangle({ 0, 400.0f - 100.0f / 2 }, { 20,100 });
	Rectangle mPaddleLeft = Rectangle({ 800 - 20, 400.0f - 100.0f / 2 }, { 20,100 });
};

