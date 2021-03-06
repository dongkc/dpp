#include <string>
#include <vector>
#include <Poco/DirectoryIterator.h>
#include <iostream>

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

int main(int argc, char *argv[])
{
  string path("/tmp");
  vector<string> vec;
  iterate(path, vec);

  cout << "============= BEGIN ============" << endl;
  for (auto& e : vec) {
    cout << e << endl;
  }
  cout << "============= END ============" << endl;

  return 0;
}
