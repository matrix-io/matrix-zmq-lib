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

#include <string>

#include <chrono>
#include <thread>

#include "gtest/gtest.h"

#include "./zmqwrap_pull.hpp"
#include "./zmqwrap_push.hpp"

namespace ml = matrix_labs;

namespace {

class TestPushPull : public ::testing::Test {
 public:
  TestPushPull() {}

 protected:
  ml::ZmqWrapPush push;
  ml::ZmqWrapPull pull;
  ml::ZmqWrapPull pull_2;

  void Sleep(int milliseconds = 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  }

  const int n_threads = 2;
  const char* address_1 = "tcp://127.0.0.1:25556";
  const char* address_2 = "tcp://127.0.0.1:25557";
  const int max_sleep_time = 1000;
  const int min_sleep_time = 100;
};

TEST_F(TestPushPull, MessageArrives) {
  push.Init(n_threads);
  pull.Init(n_threads);

  // Push binds.
  push.Bind(address_1);
  pull.Connect(address_1);

  Sleep(min_sleep_time);

  push.Send("message");
  // A message must be available.
  ASSERT_TRUE(pull.Poll(min_sleep_time));
  // Message and topic come together.
  EXPECT_EQ(pull.Read(), "message");
}

TEST_F(TestPushPull, PullBinds) {
  push.Init(n_threads);
  pull.Init(n_threads);

  // Pull binds.
  pull.Bind(address_1);
  push.Connect(address_1);

  Sleep(min_sleep_time);

  push.Send("message");
  // A message must be available.
  ASSERT_TRUE(pull.Poll(min_sleep_time));
  // Message and topic come together.
  EXPECT_EQ(pull.Read(), "message");
}

TEST_F(TestPushPull, RoundRobin) {
  push.Init(n_threads);
  pull.Init(n_threads);
  pull_2.Init(n_threads);

  // Pull binds.
  push.Bind(address_1);
  pull.Connect(address_1);
  pull_2.Connect(address_1);

  Sleep(min_sleep_time);

  push.Send("message");
  push.Send("message");

  ASSERT_TRUE(pull.Poll(min_sleep_time));
  EXPECT_EQ(pull.Read(), "message");

  ASSERT_TRUE(pull_2.Poll(min_sleep_time));
  EXPECT_EQ(pull_2.Read(), "message");
}

TEST_F(TestPushPull, RoundRobinPushConnects) {
  push.Init(n_threads);
  pull.Init(n_threads);
  pull_2.Init(n_threads);

  // Pull binds.
  pull.Bind(address_1);
  pull_2.Bind(address_2);
  push.Connect(address_1);
  push.Connect(address_2);

  Sleep(min_sleep_time);

  push.Send("message");
  push.Send("message");

  ASSERT_TRUE(pull.Poll(min_sleep_time));
  EXPECT_EQ(pull.Read(), "message");

  ASSERT_TRUE(pull_2.Poll(min_sleep_time));
  EXPECT_EQ(pull_2.Read(), "message");
}

}  // namespace
