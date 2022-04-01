/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2018 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

#include <sstream>
#include <string>

namespace ai
{
	namespace detail
	{
		// Base case: No args to stream
		void StreamArgs(std::ostringstream& ss)
		{
		}

		// Recursively stream each arg in the parameter pack
		template<typename T, typename... Ts>
		void StreamArgs(std::ostringstream& ss, const T& t, const Ts&... ts)
		{
			ss << t;
			StreamArgs(ss, ts...);
		}

	} // namespace detail

	/*
	* Stream arbitrary number of arguments to std::string
	*/
	template<typename... Args>
	inline std::string StreamArgs(const Args&... args)
	{
		std::ostringstream ss;
		// TODO: In C++17, fold expression can be used to expand the pack
		// (ss << ... << args);
		detail::StreamArgs(ss, args...);
		return ss.str();
	}

	/*
	* Utility to create std::string using ostringstream.
	*/
	template<typename T>
	inline std::string to_string(const T& value)
	{
		return StreamArgs(value);
	}

} // namespace ai