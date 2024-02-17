#pragma once

#include "ilogger.hpp"
#include <rclcpp/logging.hpp>

namespace pw
{
class RosLogger : public ILogger
{
private:
  rclcpp::Logger impl_;

public:
  RosLogger(const rclcpp::Logger & logger)
  : impl_(logger) {}

  void Log(const std::string & str) final
  {
    RCLCPP_DEBUG(impl_, "[PW] %s", str.c_str());
  }
};

} // namespace pw
