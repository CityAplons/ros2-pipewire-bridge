#pragma once

#include "ilogger.hpp"

namespace pw
{
class RosLogger : public ILogger
{
private:

public:
  RosLogger(/* args */);
  ~RosLogger();
};

} // namespace pw
