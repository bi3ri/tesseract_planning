/**
 * @file trajopt_taskflow.h
 * @brief TrajOpt Graph Taskflow
 *
 * @author Levi Armstrong
 * @date August 27, 2020
 * @version TODO
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2020, Southwest Research Institute
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TESSERACT_PROCESS_MANAGERS_TRAJOPT_TASKFLOW_H
#define TESSERACT_PROCESS_MANAGERS_TRAJOPT_TASKFLOW_H

#include <tesseract_common/macros.h>
TESSERACT_COMMON_IGNORE_WARNINGS_PUSH
#include <functional>
#include <vector>
#include <thread>
#include <taskflow/taskflow.hpp>
TESSERACT_COMMON_IGNORE_WARNINGS_POP

#include <tesseract_process_managers/core/taskflow_generator.h>
#include <tesseract_command_language/profile_dictionary.h>

namespace tesseract_planning
{
struct TrajOptTaskflowParams
{
  bool enable_post_contact_discrete_check{ true };
  bool enable_post_contact_continuous_check{ false };
  bool enable_time_parameterization{ true };
};

class TrajOptTaskflow : public TaskflowGenerator
{
public:
  using UPtr = std::unique_ptr<TrajOptTaskflow>;

  TrajOptTaskflow(TrajOptTaskflowParams params, std::string name = "TrajOptTaskflow");
  ~TrajOptTaskflow() override = default;
  TrajOptTaskflow(const TrajOptTaskflow&) = delete;
  TrajOptTaskflow& operator=(const TrajOptTaskflow&) = delete;
  TrajOptTaskflow(TrajOptTaskflow&&) = delete;
  TrajOptTaskflow& operator=(TrajOptTaskflow&&) = delete;

  const std::string& getName() const override;

  TaskflowContainer generateTaskflow(TaskInput input, TaskflowVoidFn done_cb, TaskflowVoidFn error_cb) override;

  /**
   * @brief Checks that the TaskInput is in the correct format.
   * @param input TaskInput to be checked
   * @return True if in the correct format
   */
  static bool checkTaskInput(const TaskInput& input);

private:
  std::string name_;
  TrajOptTaskflowParams params_;
};
}  // namespace tesseract_planning
#endif  // TESSERACT_PROCESS_MANAGERS_TRAJOPT_TASKFLOW_H
