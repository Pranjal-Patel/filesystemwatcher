#pragma once

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <filesystem>

namespace fs = std::filesystem;

typedef fs::file_time_type timepoint;

namespace FileWatcher {
  enum Status {
    Untouched,
    Modified,
    Deleted,
  };

  class Watcher {

  private:
    timepoint mLast_mod_time;
    const char* mTarget_file_path;
    bool running_;

  public:
    Watcher(const char* pTarget_file_path);

  public:
    // a boolean is passed so that the even loop can be stopped
    virtual void watch(Status p_trigger, void(*action)(bool&), int p_check_interval=1000);
  };
}
