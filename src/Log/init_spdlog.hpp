/**
 * @file init_spdlog.hpp
 * @author huizeyu (huizeyu@siasun.com)
 * @brief
 * @version 0.1
 * @date 2024-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <memory>

#include "spdlog/common.h"
#include "spdlog/sinks/ringbuffer_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/udp_sink.h"
#include "spdlog/spdlog.h"

namespace spdlog {
inline void InitSpdLog() {
  std::vector<spdlog::sink_ptr> sinks;
  //   sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
  sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "log/logfile.txt", 1024 * 1024 * 5, 2));

  // buffer中的log条数
  sinks.push_back(std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(5000));

  // udp
  spdlog::sinks::udp_sink_config config("127.0.0.1", 12345);
  sinks.push_back(std::make_shared<spdlog::sinks::udp_sink_mt>(config));

  auto logger =
      std::make_shared<spdlog::logger>("me", begin(sinks), end(sinks));

  spdlog::register_logger(logger);
  spdlog::set_default_logger(logger);
  spdlog::set_pattern("[%m-%d %H:%M:%S.%e][thread %t][%n][%s:%#]%^[%L] %v%$");
  spdlog::set_level(spdlog::level::trace);
}
}  // namespace spdlog