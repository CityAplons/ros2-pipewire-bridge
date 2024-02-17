#pragma once

#include <string>

namespace pw
{
class ILogger
{
public:
  ILogger();
  virtual ~ILogger() = 0;
  virtual void Log(const std::string & str) = 0;
};
} // namespace pw
