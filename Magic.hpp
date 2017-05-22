#ifndef MAGIC_HPP
#define MAGIC_HPP

#include <string>
#include <regex>

extern "C" {
#include <magic.h>
}

namespace File
{

class Magic
{
  public:
    explicit Magic(int flags = MAGIC_MIME_TYPE);
    Magic(const Magic&) = delete;
    Magic(Magic&&) = delete;
    ~Magic();

    bool open(const std::string& filepath);

    const std::string& error() const;

    const std::string& mime() const;
    const std::string& type() const;
    const std::string& format() const;

  private:
    magic_t m_handle;
    std::string m_mime;
    std::string m_type;
    std::string m_format;
    std::string m_error;
};

}

#endif