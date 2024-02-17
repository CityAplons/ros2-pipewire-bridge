#include <gtest/gtest.h>

#include <client.hpp>
#include <logger/ros.hpp>

auto g_logger = std::make_shared<pw::SimpleLogger>();

TEST(client_impl, alloc)
{
  ASSERT_STREQ(pw::Client("test", g_logger).get_name().c_str(), "test");
  ASSERT_STREQ(pw::Client().get_name().c_str(), "ros2_generic_client");
}

TEST(client_impl, connect)
{
  auto client = pw::Client("test", g_logger);
  ASSERT_TRUE(client.connect());
  client.disconnect();
}

TEST(client_impl, ros_log)
{
  auto ros_logger = rclcpp::get_logger("test");
  ros_logger.set_level(rclcpp::Logger::Level::Debug);

  auto logger = std::make_shared<pw::RosLogger>(ros_logger);
  auto client = pw::Client("test", logger);
  ASSERT_TRUE(client.connect());
  client.disconnect();
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
