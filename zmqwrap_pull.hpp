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

#ifndef SRC_ZMQ_PULL_H_
#define SRC_ZMQ_PULL_H_

#include "zmqwrap_base.hpp"

namespace matrix_labs {

// ZMQ_PULL wrapper. It pairs with ZMQ_PUSH sockets.

// This socket is receive-only. Since the ZMQ_PUSH socket type uses
// round-robin strategy, this socket type might not get all the messages
// sent by the pusher.

// High-water-mark is not defined by this socket type. Probably because
// messages are never discarded.

class ZmqWrapPull : public ZmqWrapBase {
 public:
  ZmqWrapPull() {}
  // Initialization.
  void Init(int n_threads) { ZmqWrapBase::Init(n_threads, ZMQ_PULL); }
};

}  // namespace matrix_labs

#endif  // SRC_ZMQ_PULL_H_
