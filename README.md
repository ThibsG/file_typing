# File typing [![Build Status](https://travis-ci.org/ThibsG/file_typing.svg?branch=master)](https://travis-ci.org/ThibsG/file_typing)


Simple C++ wrapper for file typing using libmagic.


Example
-------
```c++
  Magic m;
  m.open("data/test.jpg");

  std::cout << m.mime() << std::endl;
  std::cout << m.type() << std::endl;
  std::cout << m.format() << std::endl;

  // or with a buffer (loaded data stored as a std::vector<unsigned char>)

  m.load(myBuffer);

  std::cout << m.mime() << std::endl;
  std::cout << m.type() << std::endl;
  std::cout << m.format() << std::endl;
```


Output
-------
```bash
image/jpeg
image
jpeg
```