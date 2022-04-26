#include "simple_timer.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

SimpleTimerInterface **timer_instance;

int main(int argc, char **argv) {
  std::vector<std::string> timer_names = {"timer1", "timer2", "timer3"};

  if (!createTimerWithName(timer_instance, timer_names, timer_names.size())) {
    std::cout << "Failed to create timer" << std::endl;
    return -1;
  }

  startTimer(timer_instance, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  stopTimer(timer_instance, 0);
  displayTimer(timer_instance, 0);

  startTimer(timer_instance, 1);
  startTimer(timer_instance, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  stopTimer(timer_instance, 0);
  stopTimer(timer_instance, 1);
  displayTimer(timer_instance, 0);
  displayTimer(timer_instance, 1);

  resetTimer(timer_instance, 1);
  startTimer(timer_instance, 1);
  startTimer(timer_instance, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  stopTimer(timer_instance, 1);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  stopTimer(timer_instance, 2);

  displayAllTimer(timer_instance);
}