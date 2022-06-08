#include <iostream>

#include "FileSystemWatcher.h"

void print(bool &running_);

int main() {
  const char* path = "./file_to_be_monitored.txt";
  
  FileWatcher::Watcher dog(path);

  std::cout << "watching...\n";
  dog.watch(print);
}

void print(bool &running_) {
  // you can set `running_` to false if you don't wanna monitor the file anymore

  std::cout << "File Changed\n";
}
