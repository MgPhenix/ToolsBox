/**
* @file Utils.h
* @brief Just random function that can be usefull
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <string>
#include <vector>
#include "PrimitiveTypes.h"

using ID = uint64;
namespace UUID
{
	/**
	* @brief Get a unique ID 
	* 
	* - Warning : will be reset when the program stop 
	* @return ID(uint64) : unique id
	*/
	ID Generate();
}

/**
* @brief Enum to store the different type of log you can have
*/
enum class Severity
{
	DEBUG,
	INFO,
	WARN,
	ERROR,
	CRITICAL
};

/**
* @brief Convert enum class Severity to string
* @return std::string : string format of Severity
*/
std::string SevertityToString(Severity severity);
/**
 * @brief Hash a string
 * @param std::string 
 * @return uint64 : the hash of a string using FNV_1A
 */
uint64 HashFNV_1A(const std::string& str);
/**
 * @brief When you provide a path with an extension like "C:/folder/file.txt" it will return ".txt"
 * 
 * If your path doesn't have an extension it will just return the path
 * 
 * @param std::string : path
 * @return std::string : only the extension if one is present
 */
std::string GetPathExtension(const std::string& path);
// When you provide a path like "C:/folder/file.txt" it will return "file"
/**
 * @brief When you provide a path like "C:/folder/file.txt" it will return "file"
 * @param std::string : path
 * @return std::string : the name of the file without the path
 */
std::string GetPathName(const std::string& path);
/**
 * @brief Get the local time of your computer 
 * @return std::string : time in the format hours:minutes:seconds
 */
std::string GetLocalTime();
/**
* @brief Get a random number using c++ random lib
* @param int32 : minimum value
* @param int32 : maximum value
* @return int32 : a random number between minimum and maximum
*/
int32 GetRandomNumber(int32 min, int32 max);
/**
* @brief Clamp a T value between two other 
* @tparam T value you want to clamp 
* @tparam T minimum value
* @tparam T maximum value
* @return T value after beeing clamp
*/
template<typename T>
T Clamp(T val, T min, T max);
/**
* @brief Get a random element from a vector
* @tparam vector<T> : the vector you want to get a value from
* @return T : A random element from the vector you provided
*/
template<typename T>
T GetRandomValue(const std::vector<T>& vector);

#include "Utils.inl"