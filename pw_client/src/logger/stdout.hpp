#pragma once

#include "ilogger.hpp"

#include <cstdio>

namespace pw
{
class SimpleLogger : public ILogger
{
public:
  void Log(const std::string & str) final
  {
    printf("[DEBUG][PW] %s\n", str.c_str());
  }
};

} // namespace pw
