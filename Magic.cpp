#include "Magic.hpp"


using namespace std;

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

void Magic::open(const string& filepath)
{
  m_mime = ::magic_file(m_magic, filepath.c_str());
  m_type = m_mime.substr(0, m_mime.find('/'));
  m_format = m_mime.substr(m_mime.find('/') + 1);
}

const string& Magic::mime() const
{
  return m_mime;
}

const string& Magic::type() const
{
  return m_type;
}

const string& Magic::format() const
{
  return m_format;
}

}