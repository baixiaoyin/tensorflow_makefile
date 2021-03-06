/* Copyright 2016 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/distributed_runtime/call_options.h"

#include "tensorflow/core/platform/test.h"

namespace tensorflow {

TEST(CallOptions, Cancel) {
  int num_calls = 0;
  CallOptions opts;
  opts.StartCancel();
  EXPECT_EQ(num_calls, 0);
  opts.SetCancelCallback([&num_calls]() { num_calls++; });
  EXPECT_EQ(num_calls, 0);
  opts.StartCancel();
  EXPECT_EQ(num_calls, 1);
  opts.StartCancel();
  EXPECT_EQ(num_calls, 2);
  opts.ClearCancelCallback();
  EXPECT_EQ(num_calls, 2);
  opts.StartCancel();
  EXPECT_EQ(num_calls, 2);
}

}  // namespace tensorflow
