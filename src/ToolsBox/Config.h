#pragma once
/**
* @file Config.h
* @brief Just some config for macro
*
* @version 0.1
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

#if CPP_VERSION >= 201703L
#define CPP_17
#endif

#if CPP_VERSION >= 202002L
#define CPP_20
#endif