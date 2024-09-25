#pragma once

#include <chrono>
#include <ctime>
#include <vector>

class Clock {
  long long in_time = -1;
  std::vector<double> last_times;
  int current_time_index = -1;
  double deltaTime = 0.0;
  double avg_deltaTime = 0.0;
  double variance_deltaTime = 0.0;

public:
  Clock(int n = 20) : last_times(n, 0.0) {}

  void tick() {
    if (in_time == -1) {
      in_time =
          std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    long long current_time =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();

    deltaTime = (current_time - in_time) / 1000000.0;
    const auto n = last_times.size();
    current_time_index++;
    if (current_time >= n) {
      current_time_index = 0;
    }

    last_times[current_time_index] = deltaTime;

    if (n >= 2) {
      double sum = 0;
      double squareSum = 0;

      for (double t : last_times) {
        sum += t;
        squareSum += t * t;
      }

      avg_deltaTime = sum / n;
      variance_deltaTime =
          (squareSum - n * avg_deltaTime * variance_deltaTime) / (n - 1);
    }
  }

  double get_deltaTime_millis() { return deltaTime; }

  double get_avg_deltaTime_millis() { return avg_deltaTime; }
};
