#include "Magic.hpp"

using namespace std;

namespace FileTyping
{

static const regex MimeReg("(\\w+)/(\\w+)");

TypeFmt Magic::type(const string& filepath)
{
  Magic m;
  m.open(filepath);
  return TypeFmt(m.type(), m.format());
}

TypeFmt Magic::type(const vector<unsigned char>& raw)
{
  Magic m;
  m.load(raw);
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

void Magic::clear()
{
  m_error.clear();
  m_mime.clear();
  m_type.clear();
  m_format.clear();
}

void Magic::open(const string& filepath)
{
  clear();

  string mime = ::magic_file(m_handle, filepath.c_str());

  evaluate(mime);
}

void Magic::load(const vector<unsigned char>& raw)
{
  clear();

  string mime = ::magic_buffer(m_handle, raw.data(), raw.size());

  evaluate(mime);
}

void Magic::evaluate(const string& mime)
{
  smatch sm;
  if(regex_match(mime, sm, MimeReg)) {
    m_mime   = mime;
    m_type   = sm[1];
    m_format = sm[2];
  } else {
    m_error = mime;
    throw runtime_error(mime);
  }
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