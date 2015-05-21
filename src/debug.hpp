#ifndef _ENIGMA_DEBUG_H
#define _ENIGMA_DEBUG_H
#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <string>

inline void D_PRINT(std::string format, ...) {
  #ifdef DEBUG
  char buf[format.size() * 2];
  va_list args;
  va_start(args, format);
  vsprintf(buf, format.c_str(), args);
  std::cout << buf << std::endl;
  va_end(args);
  #else
  (void) format;
  #endif
}

#endif
