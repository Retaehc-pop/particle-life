#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class ThreadController {
private:
  std::thread worker_thread;
  std::mutex mutex_;
  std::condition_variable cv;
  std::atomic<bool> running;
  std::atomic<bool> stop;
  std::function<void()> custom_function;

  void worker() {
    while (!stop) {
      std::unique_lock<std::mutex> lock(mutex_);
      cv.wait(lock, [this] { return running || stop; });
      if (stop)
        break;
      if (custom_function) {
        while (running && !stop) {
          custom_function();
          // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
      }
    }
  }

public:
  ThreadController() : running(false), stop(false) {}

  ~ThreadController() {
    stop_thread(); // Ensure the thread is stopped when the object is destroyed
  }

  void start(std::function<void()> custom_function = nullptr) {
    if (custom_function) {
      this->custom_function = custom_function;
    }
    worker_thread = std::thread(&ThreadController::worker, this);
  }

  void stop_thread() {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      stop = true;
    }
    cv.notify_all();
    if (worker_thread.joinable()) {
      worker_thread.join();
    }
  }
  void set_running(bool value) {
    {
      std::lock_guard<std::mutex> locak(mutex_);
      running = value;
    }
    cv.notify_all();
  }

  void set_function(std::function<void()> func) {
    std::lock_guard<std::mutex> lock(mutex_);
    custom_function = func;
  }
};
