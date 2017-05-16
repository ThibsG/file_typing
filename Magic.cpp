#include "Magic.hpp"


namespace File
{

Magic::Magic(int flags) :
  m_magic(::magic_open(flags))
{
  ::magic_load(m_magic, NULL);
}

Magic::~Magic()
{
  ::magic_close(m_magic);
}

void Magic::open(const std::string& filepath)
{
  m_mime = ::magic_file(m_magic, filepath.c_str());
}

const std::string& Magic::mime() const
{
  return m_mime;
}

}