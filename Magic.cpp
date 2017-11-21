#include "Magic.hpp"

using namespace std;

namespace FileTyping
{

static const regex MimeReg("(\\w+)/(\\w+)");

TypeFmt Magic::type(const string& filepath)
{
  Magic m;
  auto ok = m.open(filepath);
  if(not ok)
    throw std::runtime_error(m.error());
  return TypeFmt(m.type(), m.format());
}

Magic::Magic(int flags) :
  m_handle(::magic_open(flags)),
  m_flags(flags)
{
  ::magic_load(m_handle, NULL);
}

Magic::~Magic()
{
  ::magic_close(m_handle);
}

bool Magic::open(const string& filepath)
{
  m_error.clear();
  m_mime.clear();
  m_type.clear();
  m_format.clear();
  string mime = ::magic_file(m_handle, filepath.c_str());

  smatch sm;
  if(regex_match(mime, sm, MimeReg)) {
    m_mime   = mime;
    m_type   = sm[1];
    m_format = sm[2];
    return true;
  }

  m_error = mime;
  return false;
}

int Magic::flags() const
{
  return m_flags;
}

const string& Magic::error() const
{
  return m_error;
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