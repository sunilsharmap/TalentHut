#pragma once

#ifdef _WIN32

#if defined(BUILD_SHARED_LIB)
#define LIB_EXTERN __declspec(dllexport)
#elif defined(USE_SHARED_LIB)
#define LIB_EXTERN __declspec(dllimport)
#else
#define LIB_EXTERN /* Nothing */
#endif

#elif __GNUC__ >= 4
#define LIB_EXTERN __attribute__((visibility("default")))
#else
#define LIB_EXTERN /* nothing */

#endif
