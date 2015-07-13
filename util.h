#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>

struct LockFrame
{
  std::string    lock_id;
  std::string    message_id;
  std::string    timestamp;
  std::string    frame;
};

void iterate(const std::string& path, std::vector<std::string>& vec);

char* parse(char* begin, char* end, LockFrame& lock_frame, bool& error);
#endif
