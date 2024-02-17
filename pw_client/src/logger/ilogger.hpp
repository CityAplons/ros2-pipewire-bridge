#pragma once

#include <string>

namespace pw
{
class ILogger
{
public:
  virtual ~ILogger() {}
  virtual void Log(const std::string & str) = 0;
};
} // namespace pw
