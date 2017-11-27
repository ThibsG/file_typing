#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>

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
    // Using filepath
    Magic m;
    m.open(filepath);

    cout << "\t\tUsed flags : 0x" << setfill('0') << setw(6) << hex << m.flags() << endl;

    // Using filepath via static call
    {
      string type, format;
      tie(type, format) = Magic::type(filepath);

      check(type, m.type(), "[Static call] Type detection failed");
      check(format, m.format(), "[Static call] Format detection failed");
    }

    // Loading file into a buffer as raw
    {
      std::ifstream fileStreamer(filepath.c_str(), std::ios::binary);
      vector<unsigned char> rawVec(
        (istreambuf_iterator<char>(fileStreamer)),
         istreambuf_iterator<char>());

      Magic rawM;
      rawM.load(rawVec);

      check(rawM.type(), m.type(), "[Raw loading call] Type detection failed");
      check(rawM.format(), m.format(), "[Raw loading call] Format detection failed");
    }

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