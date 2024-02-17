#include <gtest/gtest.h>

#include <client.hpp>

TEST(client_impl, alloc)
{
  ASSERT_STREQ(pw::Client("test").get_name().c_str(), "test");
  ASSERT_STREQ(pw::Client().get_name().c_str(), "ros2_generic_client");
}

TEST(client_impl, connect)
{
  auto client = pw::Client("test");
  ASSERT_TRUE(client.connect());
  client.disconnect();
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
