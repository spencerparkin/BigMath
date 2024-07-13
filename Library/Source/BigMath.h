#pragma once

#if defined BIG_MATH_EXPORT
#	define BIG_MATH_API			__declspec(dllexport)
#elif defined BIG_MATH_IMPORT
#	define BIG_MATH_API			__declspec(dllimport)
#else
#	define BIG_MATH_API
#endif