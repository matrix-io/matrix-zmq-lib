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

namespace matrix_labs {

void ZmqWrapBase::Init(int n_threads, int type) {
  context_.reset(new zmq::context_t(n_threads));
  socket_.reset(new zmq::socket_t(*(context_.get()), type));
}

bool ZmqWrapBase::Poll(int timeout_ms) {
  // Polling a single socket.
  zmq::pollitem_t poll_items[] = {
      {static_cast<void *>(*socket_.get()), 0, ZMQ_POLLIN, 0},
  };
  // Wait for message.
  zmq::poll(&poll_items[0], 1, timeout_ms);
  // Returns true if a message arrives.
  return poll_items[0].revents & ZMQ_POLLIN;
}

std::string ZmqWrapBase::Read() {
  zmq::message_t message;
  // Read the message from the socket.
  socket_->recv(&message);
  // Convert to string and return.
  std::string ret;
  ret.assign(static_cast<char *>(message.data()), message.size());
  return ret;
}

bool ZmqWrapBase::Send(const std::string &message_str) {
  zmq::message_t message(message_str.size());
  memcpy(message.data(), message_str.data(), message_str.size());
  return socket_->send(message);
}

}  // namespace matrix_labs
