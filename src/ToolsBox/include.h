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

#ifdef _DEBUG

#define DEBUG_ASSERT( condition ) if ( condition == false ) throw;
#define LOG_DEBUG( message )	Logfile::GetInstance().LOG(Severity::DEBUG,    message);

#else
#define DEBUG_ASSERT( condition );
#define LOG_DEBUG( message );
#endif 

#define ASSERT( condition ) if ( condition == false ) throw;

#define LOG_INFO( message )		Logfile::GetInstance().LOG(Severity::INFO,     message);
#define LOG_WARN( message )		Logfile::GetInstance().LOG(Severity::WARN,     message);
#define LOG_ERROR( message )	Logfile::GetInstance().LOG(Severity::ERROR,    message);
#define LOG_CRITICAL( message ) Logfile::GetInstance().LOG(Severity::CRITICAL, messsage);

using Vector2i = Vector2<int32>;
using Vector2f = Vector2<float32>;