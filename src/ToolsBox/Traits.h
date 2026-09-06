/**
* @file Traits.h
* @brief A bunch of usefull traits
*
* @version 0.1
* @date 2026-07-25
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <functional>


template<typename A, typename B>
struct is_same {
	static const bool value = false;
};

template<typename C>
struct is_same<C, C> {
	static const bool value = true;
};


template<typename T>
struct remove_pointer {
	using type = T;
};

template<typename T>
struct remove_pointer<T*> {
	using type = T;
};


template<typename T>
struct function_traits;

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
	using return_type = R;
	using args_tuple = std::tuple<Args...>;
};


template<typename T>
struct member_traits;

template<typename R, typename C, typename... Args>
struct member_traits<R(C::*)(Args...) const> {
	using return_type = R;
	using class_type = C;
	using args_tuple = std::tuple<Args...>;
};

template<typename R, typename C, typename... Args>
struct member_traits<R(C::*)(Args...)> {
	using return_type = R;
	using class_type = C;
	using args_tuple = std::tuple<Args...>;
};


template<typename T>
struct lambda_function_traits : lambda_function_traits<decltype(&T::operator())> {};

template<typename R, typename C, typename... Args>
struct lambda_function_traits<R(C::*)(Args...) const>
{
	using signature = std::function<R(Args...)>;
	using return_type = R;
	using args_tuple = std::tuple<Args...>;
};

template<typename R, typename C, typename... Args>
struct lambda_function_traits<R(C::*)(Args...)>
{
	using signature = std::function<R(Args...)>;
	using return_type = R;
	using args_tuple = std::tuple<Args...>;
};