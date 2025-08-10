#pragma once
#if defined(_WIN32) || defined(_WIN64)
  #ifdef RACING_BUILD
    #define RACING_API __declspec(dllexport)
  #else
    #define RACING_API __declspec(dllimport)
  #endif
#else
  #define RACING_API
#endif
