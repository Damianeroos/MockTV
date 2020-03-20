#pragma once

#include <gmock/gmock.h>
#include "TV.hpp"

class MockTV: public TV{
public:
  MOCK_METHOD(bool, turn_on,(),(override));
  MOCK_METHOD(bool, turn_off, (),(override));
  MOCK_METHOD(bool, change_volume, (int),(override));
  MOCK_METHOD(bool, change_channel, (int),(override));
  MOCK_METHOD(bool, change_to_next_channel,(int),(override));
};
