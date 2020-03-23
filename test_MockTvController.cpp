#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockTV.hpp"
#include "tv_controller.hpp"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Return;

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

TEST(TvTest, CanSwitchOFF) {
  MockTV tv;
  tv_controller contr(tv);

  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(tv, turn_off())
        .Times(3)
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
  }

  contr.push_button(button::ON);
  contr.push_button(button::OFF);
  contr.push_button(button::OFF);
  contr.push_button(button::OFF);
}

TEST(TvTest, NoBattery) {
  MockTV tv;
  tv_controller controller(tv, false);  // no battery

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

TEST(TvTest, VolumeUP) {
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME / 2;

  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_volume(_))
        .Times(avr_volume)
        .WillRepeatedly(Return(true));

    EXPECT_CALL(tv, change_volume(_))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(false));
  }

  controller.push_button(button::ON);
  for (int i = avr_volume; i <= MAX_VOLUME; ++i) {
    controller.push_button(button::VOLUME_UP);
  }
}

TEST(TvTest, VolumeDOWN) {
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME / 2;

  {
    InSequence seq;

    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_volume(_))
        .Times(avr_volume)
        .WillRepeatedly(Return(true));

    EXPECT_CALL(tv, change_volume(_))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(false));
  }
  controller.push_button(button::ON);
  for (int i = avr_volume; i >= 0; --i) {
    controller.push_button(button::VOLUME_DOWN);
  }
}

TEST(TvTest, ChangeVolume_TVoff) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, change_volume(_)).Times(3).WillRepeatedly(Return(false));

  controller.push_button(button::VOLUME_DOWN);
  controller.push_button(button::VOLUME_DOWN);
  controller.push_button(button::VOLUME_UP);
}

TEST(TvTest, ChannelUP) {
  MockTV tv;
  tv_controller controller(tv);

  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_to_next_channel(Eq(1)))
        .Times(3)
        .WillRepeatedly(Return(true));
  }

  controller.push_button(button::ON);
  controller.push_button(button::NEXT_CHANNEL);
  controller.push_button(button::NEXT_CHANNEL);
  controller.push_button(button::NEXT_CHANNEL);
}

TEST(TvTest, ChannelDOWN) {
  MockTV tv;
  tv_controller controller(tv);

  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_to_next_channel(Eq(-1)))
        .Times(3)
        .WillRepeatedly(Return(true));
  }

  controller.push_button(button::ON);
  controller.push_button(button::PREVIOUS_CHANNEL);
  controller.push_button(button::PREVIOUS_CHANNEL);
  controller.push_button(button::PREVIOUS_CHANNEL);
}

TEST(TvTest, ChangeChannel_TVoff) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, change_to_next_channel(_))
      .Times(3)
      .WillRepeatedly(Return(false));

  controller.push_button(button::PREVIOUS_CHANNEL);
  controller.push_button(button::PREVIOUS_CHANNEL);
  controller.push_button(button::NEXT_CHANNEL);
}

TEST(TvTest, ChangeToTypedChannel) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

  EXPECT_CALL(tv, change_channel(50))
      .Times(2)
      .WillOnce(Return(true))
      .WillOnce(Return(false));

  controller.push_button(button::ON);
  controller.type_number(50);
  controller.type_number(50);
}

TEST(TvTest, TypedUnassignedNumber) {
  MockTV tv;
  tv_controller controller(tv);

  EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

  EXPECT_CALL(tv, change_channel(_)).Times(2).WillRepeatedly(Return(false));

  controller.push_button(button::ON);
  controller.type_number(MAX_CHANNEL + 1);
  controller.type_number(-MAX_CHANNEL);
}
