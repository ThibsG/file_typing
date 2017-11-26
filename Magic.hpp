#ifndef MAGIC_HPP
#define MAGIC_HPP

#include <string>
#include <regex>
#include <tuple>

extern "C" {
#include <magic.h>
}

namespace FileTyping
{

// MIME tuple: <Type, Format>
using TypeFmt = std::tuple<std::string, std::string>;

class Magic
{
  public:
    static TypeFmt type(const std::string& filepath);

    explicit Magic(int flags = MAGIC_MIME_TYPE);
    Magic(const Magic&) = delete;
    Magic(Magic&&) = delete;
    ~Magic();

    void open(const std::string& filepath);

    int flags() const;
    const std::string& error() const;
    const std::string& mime() const;
    const std::string& type() const;
    const std::string& format() const;

  private:
    magic_t m_handle;

    int m_flags;
    std::string m_error;
    std::string m_mime;
    std::string m_type;
    std::string m_format;
};

}

#endif