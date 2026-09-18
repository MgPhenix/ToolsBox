/**
* @file Pair.h
* @brief Just a struct pair
*
* @version 0.1
* @date 2026-09-16
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "Traits.h"

/**
* @brief Just a struct that stock 2 value
*/
template<typename F, typename S>
struct Pair
{
	F first;
	S second;
	
	/**
	* @brief Check if the 2 value have the same type
	* @return true if the 2 value have the same type
	*/
	bool IsSameType()
	{
		return is_same<F, S>::value;
	}
};