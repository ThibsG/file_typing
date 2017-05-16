#ifndef MAGIC_HPP
#define MAGIC_HPP

#include <string>
#include <magic.h>

namespace File
{

class Magic
{
  public:
    explicit Magic(int flags = MAGIC_MIME_TYPE);
    ~Magic();

    void open(const std::string& filepath);

    const std::string& mime() const;
//     std::string type() const;
//     std::string format() const;

  private:
    magic_t m_magic;
    std::string m_mime;
};

}

#endif