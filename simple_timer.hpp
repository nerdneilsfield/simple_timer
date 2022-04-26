/** Copyright (c) 2022 DengQi<dengqi935@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * kin the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __SIMPLE_TIMER__
#define __SIMPLE_TIMER__

#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Simple timer class with start, stop and pause.
 */
class StopWatchTimer {
public:
  StopWatchTimer(const std::string &name = "deault")
      : name_(name), total_(0.0) {
    reset();
  }

  void set_name(const std::string &name) { name_ = name; }

  /** @brief start the timer */
  void start() { start_ = std::chrono::high_resolution_clock::now(); }

  /** @brife stop(pause) the timer and record the time */
  void stop() {
    end_ = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_);
    total_ += duration.count();
  }

  /** @brief reset the timer */
  void reset() {
    start_ = std::chrono::high_resolution_clock::now();
    end_ = start_;
    total_ = 0;
  }

  /** @brief Returns the elapsed time in microseconds. */
  double elapsed_time_ms() const { return total_; }

  /** @brief Returns the elapsed time in seconds. */
  double elapsed_time() const { return total_ * 1000.0; }

  /** @brief Print the elapsed time in output */
  void print_stats() const {
    std::cout << "Timer: " << name_ << ": " << elapsed_time_ms() << " ms"
              << std::endl;
  }

private:
  std::string name_;
  double total_;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_;
};

class SimpleTimerInterface {
public:
  virtual ~SimpleTimerInterface() = default;

  virtual void start(int index) = 0;
  virtual void stop(int index) = 0;
  virtual void reset(int index) = 0;
  virtual void print_stats(int index) = 0;
  virtual void print_all_stats() = 0;

  virtual double elapsed_time_ms(int index) = 0;
  virtual double elapsed_time(int index) = 0;
};

class SimpleTimerArrayInterface : public SimpleTimerInterface {
public:
  SimpleTimerArrayInterface(int size) : size_(size) {
    for (int i = 0; i < size_; ++i) {
      timers_.push_back(new StopWatchTimer());
    }
  }

  SimpleTimerArrayInterface(const std::vector<std::string> &name, int size)
      : size_(size) {
    for (int i = 0; i < size_; ++i) {
      timers_.push_back(new StopWatchTimer(name[i]));
    }
  }

  void check_id(int id) {
    if (id < 0 || id >= size_) {
      throw std::runtime_error("Invalid id");
    }
  }

  void start(int id) override {
    check_id(id);
    timers_[id]->start();
  }

  void stop(int id) override {
    this->check_id(id);
    timers_[id]->stop();
  }

  void reset(int id) override {
    this->check_id(id);
    timers_[id]->reset();
  }

  double elapsed_time_ms(int id) override {
    check_id(id);
    return timers_[id]->elapsed_time_ms();
  }

  double elapsed_time(int id) override {
    check_id(id);
    return timers_[id]->elapsed_time();
  }

  void print_stats(int id) override {
    check_id(id);
    timers_[id]->print_stats();
  }

  void print_all_stats() override {
    for (int i = 0; i < size_; ++i) {
      timers_[i]->print_stats();
    }
  }

private:
  int size_;
  std::vector<StopWatchTimer *> timers_;
};

inline bool createTimer(SimpleTimerInterface **timer_interface, int size) {
  *timer_interface = reinterpret_cast<SimpleTimerInterface *>(
      new SimpleTimerArrayInterface(size));
  return (*timer_interface != nullptr) ? true : false;
}

inline bool createTimerWithName(SimpleTimerInterface **timer_interface,
                                const std::vector<std::string> &name,
                                int size) {
  *timer_interface = reinterpret_cast<SimpleTimerInterface *>(
      new SimpleTimerArrayInterface(name, size));
  return (*timer_interface != nullptr) ? true : false;
}

inline bool deleteTimer(SimpleTimerInterface **timer_interface) {
  if (*timer_interface != nullptr) {
    delete *timer_interface;
    *timer_interface = nullptr;
  }
  return true;
}

inline bool startTimer(SimpleTimerInterface **timer_interface, int id) {
  if (*timer_interface != nullptr) {
    (*timer_interface)->start(id);
  }
  return true;
}

inline bool stopTimer(SimpleTimerInterface **timer_interface, int id) {
  if (*timer_interface != nullptr) {
    (*timer_interface)->stop(id);
  }
  return true;
}

inline bool resetTimer(SimpleTimerInterface **timer_interface, int id) {
  if (*timer_interface != nullptr) {
    (*timer_interface)->reset(id);
  }
  return true;
}

inline bool displayTimer(SimpleTimerInterface **timer_interface, int id) {
  if (*timer_interface != nullptr) {
    (*timer_interface)->print_stats(id);
  }
  return true;
}

inline bool displayAllTimer(SimpleTimerInterface **timer_interface) {
  if (*timer_interface != nullptr) {
    (*timer_interface)->print_all_stats();
  }
  return true;
}

inline double getTimerElapsed(SimpleTimerInterface **timer_interface, int id) {
  if (*timer_interface != nullptr) {
    return (*timer_interface)->elapsed_time(id);
  }
  return 0.0;
}

inline double getTimerElapsedMs(SimpleTimerInterface **timer_interface,
                                int id) {
  if (*timer_interface != nullptr) {
    return (*timer_interface)->elapsed_time_ms(id);
  }
  return 0.0;
}

#endif // __SIMPLE_TIMER__
