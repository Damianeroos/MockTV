#include "MockTvController.hpp"
#include "TV.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;

TEST(TvTest, CanSwichON){
  TV tv;
  MockTvController controller(tv);
  EXPECT_CALL(controller, push_button(button::ON))
    .Times(AtLeast(1));

  EXPECT_TRUE(tv.turn_on());
}
