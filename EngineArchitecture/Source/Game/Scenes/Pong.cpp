#include "Pong.h"

Pong::Pong() : Scene()
{
}

//Initialize
void Pong::Start()
{
	//initialize objects
	Vector2 winDimension = mWindow->GetDimensions();
	mBall = { { winDimension.y / 2 - mBallSize / 2, winDimension.y / 2 - mBallSize / 2 }, { mBallSize, mBallSize } };
	mPaddleRight = { { 10, winDimension.y / 2 - mPaddleHeight / 2 }, { mPaddleWidth, mPaddleHeight } };
	mPaddleLeft = { { winDimension.x - mPaddleWidth - 10, winDimension.y / 2 - mPaddleHeight / 2 }, { mPaddleWidth, mPaddleHeight } };
}

//Update
void Pong::Update(float deltaTime)
{
	//player paddle movement
	if(mIsGoingUp && (mPaddleRight.position.y > 0))
	{
		mPaddleRight.position.y -= mPaddleSpeed * Time::deltaTime;
	}
	if(mIsGoingDown && (mPaddleRight.position.y < mWindow->GetDimensions().y - mPaddleHeight ))
	{
		mPaddleRight.position.y += mPaddleSpeed * Time::deltaTime;
	}

	//ai paddle movement
	if(mBallIsMoving && mBall.position.y > 0 && mBall.position.y < mWindow->GetDimensions().y - mPaddleHeight)
	{
		mPaddleLeft.position.y = mBall.position.y;
	}

	//ball movement
	if(mBallIsMoving)
	{
		mBall.position.y += mBallSpeedY * Time::deltaTime;
		mBall.position.x += mBallSpeedX * Time::deltaTime;
	}

	//ball collision
	if(Rectangle::Collision(mBall, mPaddleLeft) || Rectangle::Collision(mBall, mPaddleRight))
	{
		mBallSpeedX = -mBallSpeedX;
	}

	if(mBall.position.y < 0 )
	{
		mBallSpeedY = abs(mBallSpeedY);
	}
	else if(mBall.position.y > mWindow->GetDimensions().y - mBallSize)
	{
		mBallSpeedY = -abs(mBallSpeedY);
	}

	//death
	if(mBall.position.x < 0 || mBall.position.x > mWindow->GetDimensions().x - mBallSize)
	{
		//score
		if(mBall.position.x < 0)
		{
			mScoreAI += 1;
		}
		else
		{
			mScorePlayer += 1;
		}

		printf("Score : %i - %i\n", mScorePlayer, mScoreAI);

		//reset ball position
		mBall.position = { mWindow->GetDimensions().y / 2 - mBallSize / 2, mWindow->GetDimensions().y / 2 - mBallSize / 2 };
		mBallIsMoving = false;
	}
}


//Function has now be deleted when refactoring
//Draw
//void Pong::Render()
//{
//	Color ballColor = { 100, 0, 200, 255 };
//	Color paddleColor = { 0, 0, 200, 255 };
//
//	mRenderer->DrawRect(mBall, ballColor );
//	mRenderer->DrawRect(mPaddleRight, paddleColor);
//	mRenderer->DrawRect(mPaddleLeft, paddleColor);
//}

//Input Handler
//void Pong::OnInput(SDL_Event event)
//{
//	switch(event.type)
//	{
//		case SDL_KEYDOWN:
//			//Move paddle up and down
//			if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z)
//			{
//				mIsGoingUp = true;
//				mIsGoingDown = false;
//			}
//			if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
//			{
//				mIsGoingDown = true;
//				mIsGoingUp = false;
//			}
//			//Start to move ball
//			if(event.key.keysym.sym == SDLK_SPACE)
//			{
//				mBallIsMoving = true;
//			}
//			break;
//
//		case SDL_KEYUP:
//			//stop moving paddle up and down
//			mIsGoingDown = false;
//			mIsGoingUp = false;
//			break;
//
//		default:
//			break;
//	}
//}
