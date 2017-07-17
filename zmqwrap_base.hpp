/*
 * Copyright 2017 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 *
 * ZmqWrap is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_ZMQ_BASE_H_
#define SRC_ZMQ_BASE_H_

#include <memory>
#include <string>

#include "third_party/zmq.hpp"

namespace matrix_labs {

// Read http://api.zeromq.org/2-1:zmq-socket for different ways of using
// sockets. The tables there are really useful.

class ZmqWrapBase {
 public:
  ZmqWrapBase() {}

  // Initialize the socket and the context.
  void Init(int n_threads, int type);

  // You need to call this *BEFORE* binding the socket
  // Set the amount of messages that can remain in the queue. Actions for
  // different kinds of sockets.
  // ZMQ_PUB: drop.
  // ZMQ_SUB: drop.
  // ZMQ_PUSH: block.
  // ZMQ_PULL: N/A.
  void SetHighWaterMark(int high_water_mark) {
    socket_->setsockopt(ZMQ_SNDHWM, (void*)&high_water_mark,
                        sizeof(high_water_mark));
    socket_->setsockopt(ZMQ_RCVHWM, (void*)&high_water_mark,
                        sizeof(high_water_mark));
  }

  // You can bind a socket or connect a socket. This is confusing when
  // using ZMQ because a PUB or SUB can be used as a client or as a server.

  // Bind socket.
  void Bind(const std::string& bind_string) { socket_->bind(bind_string); }
  // Connect socket.
  void Connect(const std::string& conn_string) {
    socket_->connect(conn_string);
  }

  // The following methods only make sense when you're using
  // the socket in read mode.

  // Poll (for socket types where this makes sense. Use -1 for infinity.
  bool Poll(int timeout_ms);
  // Read a string from the socket.
  std::string Read();

  // The following methods only make sense when you're using
  // the socket in write mode. Some subclasses might provide
  // specialized versions (with topics for pub/sub, for instance).

  bool Send(const std::string& message_str);

 protected:
  std::unique_ptr<zmq::context_t> context_;
  std::unique_ptr<zmq::socket_t> socket_;
};

}  // namespace matrix_labs

#endif  // SRC_ZMQ_BASE_H_
