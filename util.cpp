#include <Poco/DirectoryIterator.h>
#include "util.h"

using namespace std;
using namespace Poco;

void iterate(const std::string& path, std::vector<std::string>& vec)
{
  DirectoryIterator it(path);
  DirectoryIterator end;

  while (it != end) {
    if (it->isDirectory()) {
      iterate(it.path().toString(), vec);
    } else {
      vec.push_back(it.path().toString());
    }
    it++;
  }
}
