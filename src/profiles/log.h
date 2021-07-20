#pragma once

#include <iostream>

#ifdef RELEASE
#define LOG(x)
#else
#define LOG(x) std::cout << x << "\n"
#endif