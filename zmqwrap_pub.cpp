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

#include "zmqwrap_pub.hpp"

namespace matrix_labs {

bool ZmqWrapPub::Send(const std::string& topic,
                      const std::string& message_str) {
  if (topic.empty()) return ZmqWrapBase::Send(message_str);
  return ZmqWrapBase::Send(topic + message_str);
}

}  // namespace matrix_labs
