#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockTV.hpp"
#include "tv_controller.hpp"

using ::testing::Return;
using ::testing::_;

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

TEST(TvTest, NoBattery){
  MockTV tv;
  tv_controller controller(tv,false); //no battery

  EXPECT_CALL(tv, turn_on()).Times(0);
  EXPECT_CALL(tv, turn_off()).Times(0);
  EXPECT_CALL(tv, change_volume(_)).Times(0);
  EXPECT_CALL(tv, change_channel(_)).Times(0);
  EXPECT_CALL(tv, change_to_next_channel(_)).Times(0);

  EXPECT_FALSE(controller.push_button(button::ON));
  EXPECT_FALSE(controller.push_button(button::OFF));
  EXPECT_FALSE(controller.push_button(button::VOLUME_UP));
  EXPECT_FALSE(controller.push_button(button::VOLUME_DOWN));
  EXPECT_FALSE(controller.push_button(button::NEXT_CHANNEL));
  EXPECT_FALSE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_FALSE(controller.type_number(666));
}


