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
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  EXPECT_CALL(tv, turn_on())
      .Times(3)
      .WillOnce(Return(true))
      .WillRepeatedly(Return(false));

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::ON));
}

TEST(TvTest, CanSwitchOFF) {
  // Given:
  MockTV tv;
  tv_controller contr(tv);

  // When:
  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(tv, turn_off())
        .Times(3)
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
  }

  // Then:
  EXPECT_TRUE(contr.push_button(button::ON));
  EXPECT_TRUE(contr.push_button(button::OFF));
  EXPECT_TRUE(contr.push_button(button::OFF));
  EXPECT_TRUE(contr.push_button(button::OFF));
}

TEST(TvTest, NoBattery) {
  // Given:
  MockTV tv;
  tv_controller controller(tv, false);  // no battery

  // When:
  EXPECT_CALL(tv, turn_on()).Times(0);
  EXPECT_CALL(tv, turn_off()).Times(0);
  EXPECT_CALL(tv, change_volume(_)).Times(0);
  EXPECT_CALL(tv, change_channel(_)).Times(0);
  EXPECT_CALL(tv, change_to_next_channel(_)).Times(0);

  // Then:
  EXPECT_FALSE(controller.push_button(button::ON));
  EXPECT_FALSE(controller.push_button(button::OFF));
  EXPECT_FALSE(controller.push_button(button::VOLUME_UP));
  EXPECT_FALSE(controller.push_button(button::VOLUME_DOWN));
  EXPECT_FALSE(controller.push_button(button::NEXT_CHANNEL));
  EXPECT_FALSE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_FALSE(controller.type_number(666));
}

TEST(TvTest, VolumeUP) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME / 2;

  // When:
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

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  for (int i = avr_volume; i <= MAX_VOLUME; ++i) {
    EXPECT_TRUE(controller.push_button(button::VOLUME_UP));
  }
}

TEST(TvTest, VolumeDOWN) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);
  int avr_volume = MAX_VOLUME / 2;

  // When:
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

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  for (int i = avr_volume; i >= 0; --i) {
    EXPECT_TRUE(controller.push_button(button::VOLUME_DOWN));
  }
}

TEST(TvTest, ChangeVolume_TVoff) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When :
  EXPECT_CALL(tv, change_volume(_)).Times(3).WillRepeatedly(Return(false));

  // Then :
  EXPECT_TRUE(controller.push_button(button::VOLUME_DOWN));
  EXPECT_TRUE(controller.push_button(button::VOLUME_DOWN));
  EXPECT_TRUE(controller.push_button(button::VOLUME_UP));
}

TEST(TvTest, ChannelUP) {
  // Give:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_to_next_channel(Eq(1)))
        .Times(3)
        .WillRepeatedly(Return(true));
  }

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::NEXT_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::NEXT_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::NEXT_CHANNEL));
}

TEST(TvTest, ChannelDOWN) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  {
    InSequence seq;
    EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(tv, change_to_next_channel(Eq(-1)))
        .Times(3)
        .WillRepeatedly(Return(true));
  }

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::PREVIOUS_CHANNEL));
}

TEST(TvTest, ChangeChannel_TVoff) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  EXPECT_CALL(tv, change_to_next_channel(_))
      .Times(3)
      .WillRepeatedly(Return(false));

  // Then:
  EXPECT_TRUE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::PREVIOUS_CHANNEL));
  EXPECT_TRUE(controller.push_button(button::NEXT_CHANNEL));
}

TEST(TvTest, ChangeToTypedChannel) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));

  EXPECT_CALL(tv, change_channel(50))
      .Times(2)
      .WillOnce(Return(true))
      .WillOnce(Return(false));

  // Then:
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.type_number(50));
  EXPECT_TRUE(controller.type_number(50));
}

TEST(TvTest, TypedUnassignedNumber) {
  // Given:
  MockTV tv;
  tv_controller controller(tv);

  // When:
  EXPECT_CALL(tv, turn_on()).Times(1).WillOnce(Return(true));
  EXPECT_CALL(tv, change_channel(_)).Times(2).WillRepeatedly(Return(false));

  // Then
  EXPECT_TRUE(controller.push_button(button::ON));
  EXPECT_TRUE(controller.type_number(MAX_CHANNEL + 1));
  EXPECT_TRUE(controller.type_number(-MAX_CHANNEL));
}
