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

#include "./zmqwrap_pub.hpp"
#include "./zmqwrap_sub.hpp"

namespace ml = matrix_labs;

namespace {

class TestPubSub : public ::testing::Test {
 public:
  TestPubSub() {}

 protected:
  ml::ZmqWrapPub pub;
  ml::ZmqWrapPub pub_2;
  ml::ZmqWrapSub sub;

  void Sleep(int milliseconds = 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  }

  const int n_threads = 2;
  const char* address_1 = "tcp://127.0.0.1:25556";
  const char* address_2 = "tcp://127.0.0.1:25557";
  const int max_sleep_time = 1000;
  const int min_sleep_time = 100;
};

TEST_F(TestPubSub, MessageArrivesWithSubscription) {
  pub.Init(n_threads);
  sub.Init(n_threads);

  // Pub binds.
  pub.Bind(address_1);
  sub.Connect(address_1);

  sub.Subscribe("topic");
  // The subscription doesn't happen right away.
  Sleep(min_sleep_time);
  pub.Send("topic", "message");
  // A message must be available.
  ASSERT_TRUE(sub.Poll(min_sleep_time));
  // Message and topic come together.
  EXPECT_EQ(sub.Read(), "topicmessage");
}

TEST_F(TestPubSub, MessageDoesntArriveWithoutSubscription) {
  pub.Init(n_threads);
  sub.Init(n_threads);

  pub.Bind(address_1);
  sub.Connect(address_1);

  Sleep(min_sleep_time);

  // No subscription is made and the publisher sends a message.
  pub.Send("topic", "message");
  // A message must be available.
  EXPECT_FALSE(sub.Poll(max_sleep_time));
}

TEST_F(TestPubSub, SubscriberConnectsToMultiplePublishers) {
  pub.Init(n_threads);
  pub_2.Init(n_threads);
  sub.Init(n_threads);
  sub.Subscribe("topic1");
  sub.Subscribe("topic2");

  pub.Bind(address_1);
  pub_2.Bind(address_2);

  sub.Connect(address_1);
  sub.Connect(address_2);

  Sleep(min_sleep_time);

  // No subscription is made and the publisher sends a message.
  pub.Send("topic1", "message");
  pub_2.Send("topic2", "message");
  // A message must be available.
  EXPECT_TRUE(sub.Poll(max_sleep_time));
  const std::string read_1 = sub.Read();
  EXPECT_TRUE(read_1 == "topic1message" || read_1 == "topic2message");
  EXPECT_TRUE(sub.Poll(max_sleep_time));
  sub.Read();
  EXPECT_TRUE(read_1 == "topic1message" || read_1 == "topic2message");
}

}  // namespace
