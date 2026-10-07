#pragma once
/**
* @file Config.h
* @brief Just some config for macro
*
* @version 1.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#ifdef _MSVC_LANG
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif


#if CPP_VERSION >= 202002L
#define CPP_20
#endif

#if CPP_VERSION >= 201703L
#define CPP_17
#endif

#if CPP_VERSION >= 201402L
#define CPP_14
#endif


#ifdef _WIN32
#define WINDOWS
#endif

#ifdef __linux__
#define LINUX
#endif 

#ifdef __APPLE__
#define MACOS
#endif
