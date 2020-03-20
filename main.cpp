#include "tv_controller.hpp"
#include "TV.hpp"

int main(){
  TV tv;
  tv_controller pilot(tv);
  pilot.push_button(button::VOLUME_UP);
  
}
