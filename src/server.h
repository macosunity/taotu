/**
 * @file server.h
 * @author Sigma711 (sigma711 at foxmail dot com)
 * @brief Declaration of class "Server" which is the encapsulation of the
 * server.
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022 Sigma711
 *
 */

#ifndef TAOTU_SRC_SERVER_H_
#define TAOTU_SRC_SERVER_H_

#include <atomic>
#include <functional>

#include "connecting.h"
#include "io_buffer.h"
#include "net_address.h"
#include "non_copyable_movable.h"
#include "reactor_manager.h"
#include "thread_pool.h"
#include "time_point.h"

namespace taotu {

class ServerReactorManager;

/**
 * @brief "Server" offer APIs which can handle server-end new TCP connection
 * creations to users.
 *
 */
class Server : NonCopyableMovable {
 public:
  explicit Server(const NetAddress& listen_address,
                  bool should_reuse_port = false, size_t io_thread_amount = 6,
                  size_t calculation_thread_amount = 4);
  ~Server();

  void SetConnectionCallback(const std::function<void(Connecting&)>& cb);
  void SetMessageCallback(
      const std::function<void(Connecting&, IoBuffer*, TimePoint)>& cb);
  void SetWriteCompleteCallback(const std::function<void(Connecting&)>& cb);
  void SetCloseCallback(const std::function<void(Connecting&)>& cb);

  ThreadPool& GetThreadPool() { return thread_pool_; }

  // Start all "Reactors" (make all event loops run)
  void Start();

  void RemoveConnection(Connecting& connection);

 private:
  void DefaultOnConnectionCallback(Connecting& connection);
  void DefaultOnMessageCallback(Connecting& connection, IoBuffer* io_buffer,
                                TimePoint time_point);

  // Reactor manager (the "engine")
  ServerReactorManager reactor_manager_;

  // Thread pool for caculation
  ThreadPool thread_pool_;

  std::atomic_bool is_started_;
};

}  // namespace taotu

#endif  // !TAOTU_SRC_SERVER_H_
