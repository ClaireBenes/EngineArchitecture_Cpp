#pragma once

#include <string>
#include <SDL_log.h>


enum class LogType;

/**
 * @brief Log class provides static methods for logging messages to the SDL log system.
 * It includes functions for printing informational messages and errors with
 * specific categories, using SDL's built-in logging capabilities.
 */
class Log
{
public:
	// Deleted constructor and assignment operator to prevent instantiation of Log class
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	/**
	 * @brief Logs an informational message to the SDL log system.
	 * @param message The message to be logged.
	 */
	static void Info(const std::string& message);
	/**
	 * @brief Logs an error message with a specified category to the SDL log system.
	 * @param category The category of the error (e.g., Render, System).
	 * @param message The error message to be logged.
	 */
	static void Error(LogType category, const std::string& message);
};

/**
 * @brief LogType enum defines different categories of log messages.
 * These categories allow logging to be filtered based on the type of event
 * (e.g., application, audio, video, etc.).
 */
enum class LogType
{
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System = SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO
};

