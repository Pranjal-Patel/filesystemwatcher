#include "FileSystemWatcher.h"

FileWatcher::Watcher::Watcher(const char* pTarget_file_path) {
  mLast_mod_time = fs::last_write_time(pTarget_file_path);
  mTarget_file_path = pTarget_file_path;
  running_ = true;
}

void FileWatcher::Watcher::watch(void(*action)(bool&), int p_check_interval)
{
  while (running_) {
    if (!fs::exists(mTarget_file_path)) break;

    std::this_thread::sleep_for(std::chrono::milliseconds(p_check_interval));
    bool trigger_func = false;

    try {

      timepoint current_mod_time = fs::last_write_time(mTarget_file_path);

      // Modified
      trigger_func = (!trigger_func && current_mod_time != mLast_mod_time)? 1:0;

      if (trigger_func)
      { action(running_); mLast_mod_time = current_mod_time; }

    } catch (std::exception &) {
      action(running_);
      break;
    }
  }
}
