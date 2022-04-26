#include "simple_timer.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

SimpleTimerInterface *timer_instance = nullptr;

int main(int argc, char **argv) {
  // direct use StopWatchTimer
  StopWatchTimer simple_timer{"simple_timer"};

  simple_timer.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  simple_timer.stop();

  simple_timer.print_stats();

  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  simple_timer.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  simple_timer.stop();
  simple_timer.print_stats();

  // direct use SimpleTimerArrayInterface
  std::vector<std::string> name{"simple_timer_array1", "simple_timer_array2"};
  SimpleTimerArrayInterface timer_array{name, 2};

  timer_array.start(0);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  timer_array.stop(0);
  timer_array.print_stats(0);

  timer_array.start(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  timer_array.stop(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  timer_array.start(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  timer_array.stop(1);
  timer_array.print_all_stats();

  // use helper function to manager multiple timers
  std::vector<std::string> timer_names = {"timer1", "timer2", "timer3"};

  if (!createTimerWithName(&timer_instance, timer_names, timer_names.size())) {
    std::cout << "Failed to create timer" << std::endl;
    return -1;
  }

  startTimer(&timer_instance, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  stopTimer(&timer_instance, 0);
  displayTimer(&timer_instance, 0);

  startTimer(&timer_instance, 1);
  startTimer(&timer_instance, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  stopTimer(&timer_instance, 0);
  stopTimer(&timer_instance, 1);
  displayTimer(&timer_instance, 0);
  displayTimer(&timer_instance, 1);

  resetTimer(&timer_instance, 1);
  startTimer(&timer_instance, 1);
  startTimer(&timer_instance, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  stopTimer(&timer_instance, 1);

  std::this_thread::sleep_for(std::chrono::milliseconds(110));
  stopTimer(&timer_instance, 2);

  displayAllTimer(&timer_instance);

  double time1_elapsed = getTimerElapsed(&timer_instance, 0);
  double time2_elapsed = getTimerElapsed(&timer_instance, 1);
  double time3_elapsed = getTimerElapsed(&timer_instance, 2);

  double time1_elapsed_ms = getTimerElapsedMs(&timer_instance, 0);
  double time2_elapsed_ms = getTimerElapsedMs(&timer_instance, 1);
  double time3_elapsed_ms = getTimerElapsedMs(&timer_instance, 2);

  deleteTimer(&timer_instance);
}