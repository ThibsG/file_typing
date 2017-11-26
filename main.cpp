#include <iostream>
#include <iomanip>
#include <tuple>

#include "Magic.hpp"

using namespace std;
using namespace FileTyping;

int main(int argc, char** argv)
{
  const string filepath(argv[1]);

  cout << ":: File typing" << endl;
  cout << "::\t" << filepath << endl;

  auto check = [&](auto&& first, auto&& second, const string& exc) {
    if(first != second)
      throw runtime_error(exc);
  };

  try {
    Magic m;
    m.open(filepath);

    cout << "\t\tUsed flags : 0x" << setfill('0') << setw(6) << hex << m.flags() << endl;

    string type, format;
    std::tie(type, format) = Magic::type(filepath);

    check(type, m.type(), "Type detection failed");
    check(format, m.format(), "Format detection failed");

    if(argc > 2) {
      const string cmpMimetype(argv[2]);
      check(cmpMimetype, m.mime(), "Mimetype comparison failed");
    }

    cout << "\t\tMime type : " << m.mime() << endl;

  } catch(const runtime_error& re) {
    cout << "\t\tFile typing error : " << re.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
};