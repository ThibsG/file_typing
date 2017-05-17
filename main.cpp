#include <iostream>

#include "Magic.hpp"

using namespace std;
using namespace File;

int main(int argc, char** argv)
{
  cout << ":: File typing" << endl;

  Magic m;
  if(m.open(argv[1])) {
    std::cout << "Mime : " << m.mime() << std::endl;
    std::cout << "Type : " << m.type() << std::endl;
    std::cout << "Format : " << m.format() << std::endl;
  } else {
    std::cout << "Error : " << m.error() << std::endl;
  }

  return 0;
};