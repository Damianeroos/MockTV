#pragma once

#include <memory>
#include "TV.hpp"

enum class button {
  VOLUME_UP,
  VOLUME_DOWN,
  ON,
  OFF,
  NEXT_CHANNEL,
  PREVIOUS_CHANNEL
};

class tv_controller {
 public:
  void push_button(button);
  void type_number(int arg) { m_tv.change_channel(arg); }
  tv_controller(TV &tv, bool has_battery = true)
      : m_has_battery(has_battery), m_tv(tv){};
  void set_battery() { m_has_battery = true; };

 private:
  bool m_has_battery;
  TV &m_tv;
};

void tv_controller::push_button(button arg) {
  if (!m_has_battery) return;

  switch (arg) {
    case button::VOLUME_UP:
      m_tv.change_volume(1);
      break;
    case button::VOLUME_DOWN:
      m_tv.change_volume(-1);
      break;
    case button::ON:
      m_tv.turn_on();
      break;
    case button::OFF:
      m_tv.turn_off();
      break;
    case button::NEXT_CHANNEL:
      m_tv.change_to_next_channel(1);
      break;
    case button::PREVIOUS_CHANNEL:
      m_tv.change_to_next_channel(-1);
      break;
  }
}
