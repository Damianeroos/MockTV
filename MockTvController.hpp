#pragma once

#include <gmock/gmock.h>
#include "TV.hpp"
#include "tv_controller.hpp"

class MockTvController : public tv_controller {
 public:
  MockTvController(TV &tv, bool has_battery = true)
      : tv_controller(tv, has_battery){};
  MOCK_METHOD(void, set_battery, (), (override));
  MOCK_METHOD(void, type_number, (int arg), (override));
  MOCK_METHOD(void, push_button, (button), (override));
};
