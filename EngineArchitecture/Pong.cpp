#include "Pong.h"

Pong::Pong() : Scene()
{
}

void Pong::Start(Renderer* pRenderer)
{
	mRenderer = pRenderer;
}

void Pong::Update()
{
}

void Pong::Render()
{
	Rectangle ball = Rectangle({ 400.0f - 20.0f/2, 400.0f - 20.0f / 2 }, { 20,20 });
	Rectangle paddleRight = Rectangle({ 0, 400.0f - 100.0f / 2 }, { 20,100 });
	Rectangle paddleLeft = Rectangle({ 800 - 20, 400.0f - 100.0f / 2 }, { 20,100 });

	mRenderer->DrawRect(ball);
	mRenderer->DrawRect(paddleRight);
	mRenderer->DrawRect(paddleLeft);
}

void Pong::OnInput(SDL_Event)
{
}

void Pong::Close()
{
}
