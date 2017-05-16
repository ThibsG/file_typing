#include <iostream>

#include "Magic.hpp"

using namespace std;
using namespace File;

int main(int argc, char** argv)
{
  cout << ":: File typing" << endl;
  Magic m;

  m.open(argv[1]);
  std::cout << "Mime : " << m.mime() << std::endl;

  return 0;
};