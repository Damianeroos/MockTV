#pragma once

#include <gmock/gmock.h>
#include "TV.hpp"

class MockTV : public TV {
 public:
  MockTV() : TV(){};
  MOCK_METHOD(bool, turn_on, (), (override));
  MOCK_METHOD(bool, turn_off, (), (override));
  MOCK_METHOD(bool, change_volume, (int arg), (override));
  MOCK_METHOD(bool, change_channel, (int arg), (override));
  MOCK_METHOD(bool, change_to_next_channel, (int arg), (override));
};
