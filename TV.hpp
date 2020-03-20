#pragma once

#define MAX_CHANNEL 99
#define MAX_VOLUME 100

class TV {
 public:
  TV() : m_volume(MAX_VOLUME / 2), m_channel(0), m_has_power(false){};
  virtual ~TV(){};
  virtual bool turn_on() {
    if (m_has_power) return false;
    return (m_has_power = true);
  };
  virtual bool turn_off() {
    if (!m_has_power) return false;
    return (m_has_power = false);
  };
  virtual bool change_volume(int);
  virtual bool change_channel(int);
  virtual bool change_to_next_channel(int);

 private:
  int m_volume;
  int m_channel;
  bool m_has_power;
};

bool TV::change_volume(int arg) {
  if (m_volume + arg < 0 || m_volume + arg > MAX_VOLUME) return false;

  m_volume += arg;
  return true;
}

bool TV::change_to_next_channel(int arg) {
  m_channel += arg;

  if (m_channel < 0) m_channel = MAX_CHANNEL;

  if (m_channel > MAX_CHANNEL) m_channel = 0;

  return true;
}

bool TV::change_channel(int arg) {
  if (arg > MAX_CHANNEL || arg < 0) return false;

  m_channel = arg;
  return true;
}
