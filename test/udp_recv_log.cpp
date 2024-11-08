#include <array>
#include <asio.hpp>
#include <iostream>

using asio::ip::udp;

int main() {
  try {
    // 创建 io_context
    asio::io_context io_context;

    // 创建 UDP 端点，监听 127.0.0.1 的端口 12345
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));

    std::cout << "UDP Server listening on 127.0.0.1:12345" << std::endl;

    // 循环接收数据
    while (true) {
      // 定义接收缓存区和发送端的端点
      std::array<char, 1024> recv_buffer;
      udp::endpoint sender_endpoint;

      // 阻塞等待接收消息
      std::error_code error;
      size_t len = socket.receive_from(asio::buffer(recv_buffer),
                                       sender_endpoint, 0, error);

      if (!error) {
        // 将接收到的消息打印出来
        std::cout << "Received: " << std::string(recv_buffer.data(), len);
      } else {
        std::cerr << "Receive failed: " << error.message() << std::endl;
      }
    }
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
