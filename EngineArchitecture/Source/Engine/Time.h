#pragma once

/**
 * @brief The Time class provides static utility functions and variables to manage
 * frame timing, delta time computation, frame rate regulation, and tracking
 * the elapsed game time. 
 * It is designed to be a singleton-style class with only static members and no instances.
 */
class Time
{
public:
	Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	/**
     * @brief Computes the time elapsed since the last frame (delta time), clamps
	 * it to a maximum to prevent instability, and stores it in `deltaTime`.
	 * @return Delta time in milliseconds (clamped to MAX_DT).
	 */
	static unsigned int ComputeDeltaTime();
	/**
	 * @brief Delays the frame if it finished too early, in order to maintain a
	 * consistent frame rate defined by FPS.
	 */
	static void DelayTime();
	/**
	 * @brief Returns the total time elapsed since the game started.
	 * @return Elapsed game time in seconds.
	 */
	static float GetGameTime();

	/**
	 * @brief Delta time (in seconds) between the current and previous frame.
	 */
	static float deltaTime;

private:
	/**
	 * @brief Target frames per second
	 */
	const static unsigned int FPS = 60;
	/**
	 * @brief Delay time per frame to maintain the target FPS
	 */
	const static unsigned int FRAME_DELAY = 1000 / FPS; 
	/**
	 * @brief Maximum delta time in milliseconds to avoid big time jumps
	 */
	const static unsigned int MAX_DT = 50;

	/**
	 * @brief Time at which the current frame started
	 */
	static unsigned int mFrameStart;
	/**
	 * @brief Time at which the previous frame started
	 */
	static unsigned int mLastFrame;
	/**
	 * @brief Duration taken to execute the current frame
	 */
	static unsigned int mFrameTime;

	/**
	 * @brief Total elapsed time since the game started
	 */
	static float mGameTime; 
};

