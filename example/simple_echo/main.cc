/**
 * @file main.cc
 * @author Sigma711 (sigma711 at foxmail dot com)
 * @brief  // TODO:
 * @date 2022-02-22
 *
 * @copyright Copyright (c) 2022 Sigma711
 *
 */

#include <stddef.h>
#include <stdint.h>

#include <string>

#include "echo.h"

int main(int argc, char* argv[]) {
  if (1 == argc) {
    EchoServer echo_server{taotu::NetAddress{4567}, false};
    echo_server.Start();
  } else if (2 == argc) {
    EchoServer echo_server{taotu::NetAddress{static_cast<uint16_t>(
                               std::stoi(std::string{argv[1]}))},
                           false};
    echo_server.Start();
  } else if (3 == argc) {
    EchoServer echo_server{
        taotu::NetAddress{
            static_cast<uint16_t>(std::stoi(std::string{argv[1]}))},
        false, static_cast<size_t>(std::stoi(std::string{argv[2]}))};
    echo_server.Start();
  } else {
    EchoServer echo_server{
        taotu::NetAddress{
            static_cast<uint16_t>(std::stoi(std::string{argv[1]}))},
        false, static_cast<size_t>(std::stoi(std::string{argv[2]})),
        static_cast<size_t>(std::stoi(std::string{argv[3]}))};
    echo_server.Start();
  }
  return 0;
}
