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

#include "zmqwrap_base.hpp"

#ifndef SRC_ZMQ_PUB_H_
#define SRC_ZMQ_PUB_H_

namespace matrix_labs {

// ZMQ_PUB wrapper. Pairs with ZMQ_SUB sockets.

// This socket type is send-only.
// The outgoing routing strategy is fan out, thus the messages
// will be sent to all the connected sockets (that might filter the
// messages with a prefix).

// When the high-water-mark is reached the messages are dropped and
// the socket doesn't block.

// A publisher is often bound to an address. But it can also start the

// connection.
// Unfortunately connecting to the remote host doesn't work in the
// unit test. In a manual test that used separate programs it worked.

class ZmqWrapPub : public ZmqWrapBase {
 public:
  ZmqWrapPub() {}
  // Initialization.
  void Init(int n_threads) { ZmqWrapBase::Init(n_threads, ZMQ_PUB); }
  // Send with a topic.
  bool Send(const std::string& topic, const std::string& message_str);
};

}  // namespace matrix_labs

#endif  // SRC_ZMQ_PUB_H_
