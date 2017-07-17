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

#ifndef SRC_ZMQ_PUSH_H_
#define SRC_ZMQ_PUSH_H_

namespace matrix_labs {

// ZMQ_PUSH wrapper. Pairs with ZMQ_PULL sockets.

// This socket type is send-only.

// The outgoing routing strategy is round-robin.

// When the high-water-mark is reached or if no socket is connected
// the socket blocks until it can send messages. The messages are not
// discarded

class ZmqWrapPush : public ZmqWrapBase {
 public:
  ZmqWrapPush() {}
  // Initialization.
  void Init(int n_threads) { ZmqWrapBase::Init(n_threads, ZMQ_PUSH); }
};

}  // namespace matrix_labs

#endif  // SRC_ZMQ_PUSH_H_
