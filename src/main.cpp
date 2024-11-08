#include <chrono>
#include <iostream>
#include <thread>

#include "Log/init_spdlog.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

int main(int argc, char** argv) {
  spdlog::InitSpdLog();

  double a = 1.2;
  double b = 23.4;
  SPDLOG_TRACE("trance log");
  SPDLOG_DEBUG("debug log {}", 1);
  SPDLOG_INFO("info log {}", b);

  std::atomic_bool is_exit = false;
  int aa = 0;
  while (!is_exit.load()) {
    // logger->debug("debug log");
    spdlog::stopwatch sw;
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    SPDLOG_DEBUG("sleep time {}", sw);
    aa++;
    if (aa > 20000) {
      is_exit.store(true);
    }
  }
  SPDLOG_INFO("buffer log ...");
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  auto sinks_vec = spdlog::get("me")->sinks();
  int num_sink = 0;
  std::vector<std::string> log_messages;
  for (auto& sink : sinks_vec) {
    auto ringbuffer_sink =
        std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink);
    if (ringbuffer_sink) {
      log_messages = ringbuffer_sink->last_formatted(5000);
      SPDLOG_DEBUG("in sinks vec {} ", num_sink);
      break;
    }
    num_sink++;
  }

  SPDLOG_INFO("Get buffer log {} msg", log_messages.size());
  // for (auto& log : log_messages) {
  //   std::cout << log << std::endl;
  // }

  return 0;
}
