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

#ifndef SRC_ZMQ_SUB_H_
#define SRC_ZMQ_SUB_H_

#include "zmqwrap_base.hpp"

namespace matrix_labs {

// ZMQ_SUB wrapper. It pairs with ZMQ_PUB sockets.

// This socket is receive-only.

// A ZMQ subscriber can connect to many publishers and the routing
// strategy is fair-queued, so a single publisher won't clog the receiver.

// When the hight-water-mark is reached the messages are dropped and the
// socket doesn't block.
// NOTE: *** HWM is not working for subscribers! *** It didn't work in an
// unit test.

// A ZMQ subscriber is often connected to a remote publisher.
// The opposite can also be done but it didn't work in the unit test.
// In separate programs it worked.

class ZmqWrapSub : public ZmqWrapBase {
 public:
  ZmqWrapSub() {}
  // Initialization.
  void Init(int n_threads) { ZmqWrapBase::Init(n_threads, ZMQ_SUB); }
  // Subscribe to topic. Multiple topics can be set.
  void Subscribe(const std::string& topic);
};

}  // namespace matrix_labs

#endif  // SRC_ZMQ_PUB_H_
