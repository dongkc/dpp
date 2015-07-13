#include <string>
#include <Poco/DirectoryIterator.h>
#include <iostream>

using namespace std;
using namespace Poco;

int main(int argc, char *argv[])
{
  string path("/tmp");
  DirectoryIterator it(path);
  DirectoryIterator end;
  while (it != end) {
    cout << it.name()<< endl;
    it++;
  }
  return 0;
}
