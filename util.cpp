#include <Poco/DirectoryIterator.h>
#include "util.h"
#include "app.h"

using namespace std;
using namespace Poco;

namespace {
std::string to_str(const unsigned char byte)
{
  char buf[2];
  char tmp  = ((byte & 0xF0) >> 4);
  if (tmp > 9) {
    buf[0] = tmp - 10 + 'A';
  } else {
    buf[0] = tmp + '0';
  }
  tmp = byte & 0x0F;
  if (tmp > 9) {
    buf[1] = tmp - 10 + 'A';
  } else {
    buf[1] = tmp + '0';
  }
  std::string res(buf, 2);

  return res;
}
}

void dir_walk(const std::string& path, std::vector<std::string>& vec)
{
  DirectoryIterator it(path);
  DirectoryIterator end;

  while (it != end) {
    if (it->isDirectory()) {
      dir_walk(it.path().toString(), vec);
    } else {
      vec.push_back(it.path().toString());
    }
    it++;
  }
}

//解析一个frame，移动指针到下一个frame的开始，如果出错，设置标志位error
char* parse(char* begin, char* end, LockFrame& lock_frame, bool& error)
{
  error = false;
  char* offset = begin;

  char magic = 0xff;
  if (*offset != magic) {
    LOG(ERROR) << "Parse error, not begin with magic id 0xFF: " << to_str(*offset);
    error = true;
    return begin;
  }

  lock_frame.timestamp = string(++offset, 19);
#if 0
  DateTime datetime;
  int timezone;
  if (!DateTimeParser::tryParse(DateTimeFormat::SORTABLE_FORMAT, timestamp, lock_frame.datetime, timezone)) {
    LOG(ERROR) << "Parse timestamp error";
    error = true;
    return begin;
  }
#endif

  offset += 19;
  uint16_t len;
  memcpy(&len, offset, 2);

  offset += 2;
  if (*offset != 0x7E || *(offset + len - 1) != 0x7E) {
    LOG(ERROR) << "Invalid frame, not begin or end with 0x7E, begin: "
               << to_str(*offset)
               << " end: "
               << to_str(*(offset + len - 1));
    error = true;
    return begin;
  }

  offset++;
  lock_frame.message_id = to_str(*offset) + to_str(*(offset + 1));

  string phone_num;
  for (int i = 4; i < 10; ++i) {
    phone_num += to_str(*(offset + i));
  }

  lock_frame.lock_id = phone_num;
  lock_frame.frame = string(--offset, len);

  return offset + len;
}

