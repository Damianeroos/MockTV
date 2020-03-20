#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockTV.hpp"
#include "tv_controller.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::InSequence;
using ::testing::AtLeast;

TEST(TvTest, CanSwichON) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, turn_on())
      .Times(3)
      .WillOnce(Return(true))
      .WillRepeatedly(Return(false));
  

  controller.push_button(button::ON);
  controller.push_button(button::ON);
  controller.push_button(button::ON);
}

TEST(TvTest, NoBattery){
  MockTV tv;
  tv_controller controller(tv,false); //no battery

  EXPECT_CALL(tv, turn_on()).Times(0);
  EXPECT_CALL(tv, turn_off()).Times(0);
  EXPECT_CALL(tv, change_volume(_)).Times(0);
  EXPECT_CALL(tv, change_channel(_)).Times(0);
  EXPECT_CALL(tv, change_to_next_channel(_)).Times(0);

  controller.push_button(button::ON);
  controller.push_button(button::OFF);
  controller.push_button(button::VOLUME_UP);
  controller.push_button(button::VOLUME_DOWN);
  controller.push_button(button::NEXT_CHANNEL);
  controller.push_button(button::PREVIOUS_CHANNEL);
  controller.type_number(666);
}

TEST(TvTest, VolumeUP){
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME/2;

  {
    InSequence seq;

    EXPECT_CALL(tv, change_volume(_))
      .Times(avr_volume)
      .WillRepeatedly(Return(true));
   
    EXPECT_CALL(tv, change_volume(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(false));   
  }

  for(int i = avr_volume ; i <= MAX_VOLUME ; ++i){
    controller.push_button(button::VOLUME_UP);
  }
 
}

TEST(TvTest, VolumeDOWN){
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME/2;

  {
    InSequence seq;

    EXPECT_CALL(tv, change_volume(_))
      .Times(avr_volume)
      .WillRepeatedly(Return(true));
   
    EXPECT_CALL(tv, change_volume(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(false));   
  }

  for(int i = avr_volume ; i >= 0 ; --i){
    controller.push_button(button::VOLUME_DOWN);
  }
 
}
