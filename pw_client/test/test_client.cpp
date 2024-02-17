#include <gtest/gtest.h>

#include <client.hpp>

TEST(pw_client::client, alloc)
{
  ASSERT_STREQ(pw::Client("test").get_name(), "test");
  ASSERT_STREQ(pw::Client().get_name(), "ros2_generic_client");
}

TEST(pw_client::client, connect)
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
