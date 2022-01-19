/**
 * @file timer.cc
 * @author Sigma711 (sigma711 at foxmail dot com)
 * @brief Implementation of class "Timer" which is the container of time points
 * and the corresponding tasks (callback).
 * @date 2021-12-17
 *
 * @copyright Copyright (c) 2021 Sigma711
 *
 */

#include "timer.h"

#include <utility>

using namespace taotu;

void Timer::AddTimeTask(TimePoint time_point, TimeCallback TimeTask) {
  LockGuard lock_guard(mutex_lock_);
  time_points_.insert({time_point, std::move(TimeTask)});
}

int Timer::GetMinTimePointSet() const {
  LockGuard lock_guard(mutex_lock_);
  return time_points_.begin()->first.GetMillisecond();
}

Timer::ExpiredTimeTasks Timer::GetExpiredTimeTasks() {
  ExpiredTimeTasks expired_time_tasks;
  {
    LockGuard lock_guard(mutex_lock_);
    TimePoints::iterator itr;
    TimePoint now;
    for (itr = time_points_.begin();
         itr != time_points_.end() && itr->first <= now; ++itr) {
      expired_time_tasks.emplace_back(itr->first, itr->second);
    }
    time_points_.erase(time_points_.begin(), itr);
  }
  return expired_time_tasks;
}
