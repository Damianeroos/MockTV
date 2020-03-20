#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockTV.hpp"
#include "tv_controller.hpp"

using ::testing::Return;

TEST(TvTest, CanSwichON) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, turn_on())
      .Times(3)
      .WillOnce(Return(true))
      .WillRepeatedly(Return(false));

  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::ON));
}
