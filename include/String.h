#ifndef __String_h
#define __String_h

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <cassert>
#include <string>

namespace tcii::ex
{ // begin namespace tcii::ex


//////////////////////////////////////////////////////////
//
// String class
// ======
class String
{
public:
  ~String();

  String();
  String(const char* const);
  String(const String&);
  String(String&&) noexcept;

  void clear();

  inline auto size() const
  {
    return _size;
  }

  inline auto capacity() const
  {
    return isShort() ? maxBuffer - 1 : _capacity;
  }

  inline auto empty() const
  {
    return _size == 0;
  }

  inline char* c_str() const
  {
    return _data;
  }

  String& operator =(const char* const);
  String& operator =(const String&);
  String& operator =(String&&) noexcept;

  String operator +(const char* const) const;
  String operator +(const String&) const;

  String& operator +=(const char* const);
  String& operator +=(const String&);

  inline auto& operator [](unsigned i)
  {
    assert(i <= _size);
    return _data[i];
  }

  inline auto operator [](unsigned i) const
  {
    assert(i <= _size);
    return _data[i];
  }

  bool operator ==(const char* const) const;
  bool operator ==(const String&) const;

  inline auto operator !=(const char* const s) const
  {
    return !operator ==(s);
  }

  inline auto operator !=(const String& s) const
  {
    return !operator ==(s);
  }

private:
  static constexpr auto maxBuffer = 16u;

  unsigned _size;
  char* _data;
  union
  {
    unsigned _capacity;
    char _buffer[maxBuffer];
  };

  inline bool isShort() const
  {
    return _size < maxBuffer;
  }

  void copy(const char* const, unsigned);
  void move(String&) noexcept;

}; // String

} // end namespace tcii::ex

#endif // __String_h
