#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockTvController.hpp"
#include "TV.hpp"

TEST(TvTest, CanSwichON) {
  TV tv;
  MockTvController controller(tv, false);
  EXPECT_CALL(controller, push_button(button::ON)).Times(1);

  EXPECT_TRUE(tv.turn_on());
}
