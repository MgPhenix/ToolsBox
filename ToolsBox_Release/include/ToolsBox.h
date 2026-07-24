/**
* @file ToolsBox.h
* @brief Main file, include only this file because this file include all of the other file from the project
* 
* @version 0.1
* @date 2026-07-04
* 
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "Config.h"
#include "PrimitiveTypes.h"
#include "Utils.h"
#include "Timer.h"
#include "ObjectPool.h"
#include "Vector2.h"
#include "AssetEngine.h"
#include "UniquePtr.h"
#include "SharedPtr.h"
#include "EventSystem.h"
#include "Logger.h"
#include "ThreadPool.h"
#include "ScopeProfiler.h"

#ifdef _DEBUG
/**
* @brief Throw an error and stop programm if condition is false
* @brief This function will do nothing on Release (only work in debug)
*/
#define DEBUG_ASSERT( condition ) if ( condition == false ) throw;
/**
* @brief Print and save an Warn log (File must be open with OPEN_FILE( FILE )
* @brief This function will do nothing on Release (only work in debug)
*/
#define LOG_DEBUG( message )	Logfile::GetInstance().LOG(Severity::DEBUG,    message);
#else
/*
* @brief Function desactived in Release
*/
#define DEBUG_ASSERT( condition ) {}
/*
* @brief Function desactived in Release
*/
#define LOG_DEBUG( message ) {}
#endif 

/**
* @brief Throw an error and stop programm if condition is false
*/
#define ASSERT( condition ) if ( condition == false ) throw;

/**
* @brief Open a file for write log in it
* @brief -Use .log file for better understanding but it's optional
* @param string : path of your file
*/
#define OPEN_FILE( path )       Logfile::GetInstance().OpenFile(path);
/**
* @brief Close a file if one is open
*/
#define CLOSE_FILE				Logfile::GetInstance().CloseFile();
/**
* @brief Print and save an Info log (File must be open with OPEN_FILE( FILE )
*/
#define LOG_INFO( message )		Logfile::GetInstance().LOG(Severity::INFO,     message);
/**
* @brief Print and save an Warn log (File must be open with OPEN_FILE( FILE )
*/
#define LOG_WARN( message )		Logfile::GetInstance().LOG(Severity::WARN,     message);
/**
* @brief Print and save an Error log (File must be open with OPEN_FILE( FILE )
*/
#define LOG_ERROR( message )	Logfile::GetInstance().LOG(Severity::ERROR,    message);
/**
* @brief Print and save an Critical Error log (File must be open with OPEN_FILE( FILE )
*/
#define LOG_CRITICAL( message ) Logfile::GetInstance().LOG(Severity::CRITICAL, messsage);

/**
* @brief Print the time that the scope take to execute
* @brief Never use twice in the same scope (for now maybe i will find an other way later)
* @param string : name of your task
*/
#define SCOPE_PROFILER( name ) ScopeProfiler profiler(name);


using Vector2i = Vector2<int32>;
using Vector2f = Vector2<float32>;

constexpr float32 PI = 3.1415927f;
constexpr float32 RAD_TO_DEG = float32(180.0f / PI);
constexpr float32 DEG_TO_RAD = float32(PI / 180.0f);
constexpr float32 GRAVITY = 9.80665f;

using Radians = float32;
using Degrees = float32;