#include <iostream>
#include <iomanip>

#include "Magic.hpp"

using namespace std;
using namespace File;

int main(int argc, char** argv)
{
  cout << ":: File typing" << endl;

  Magic m;
  if(m.open(argv[1])) {
    cout << "Mime : " << m.mime() << endl;
    cout << "Type : " << m.type() << endl;
    cout << "Format : " << m.format() << endl;
    cout << "Flags : 0x" << setfill('0') << setw(6) << hex << m.flags() << endl;
  } else {
    cout << "Error : " << m.error() << endl;
  }

  return 0;
};