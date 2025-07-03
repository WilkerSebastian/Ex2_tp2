#include "String.h"
#include <cstring>

namespace tcii::ex
{ // begin namespace tcii::ex


//////////////////////////////////////////////////////////
//
// String implementation
// ======
void
String::copy(const char* const s, unsigned size)
{
  if ((_size = size) > 0)
  {
    if (isShort())
      _data = _buffer;
    else
    {
      _capacity = (_size / maxBuffer + 1) * maxBuffer;
      _data = new char[_capacity + 1];
    }
    strncpy(_data, s, _size + 1);
  }
}

void
String::move(String& other) noexcept
{
  _size = other._size;
  if (isShort())
  {
    _data = _buffer;
    strncpy(_data, other._data, _size + 1);
  }
  else
  {
    _capacity = other._capacity;
    _data = other._data;
  }
  other._size = 0;
}

// insert your code here

String::~String() 
{

    if (!isShort())
        delete[] _data;

}

String::String()
{

    _size = 0;
    _data = _buffer;
    _data[0] = '\0';

}

String::String(const char* const s)
{
    
    if (s == nullptr)
    {

        _size = 0;
        _data = _buffer;
        _data[0] = '\0';

        return;

    }

    copy(s, strlen(s));

}

String::String(const String& other)
{
    
    copy(other._data, other._size);

}

String::String(String&& other) noexcept
{

    move(other);

}

String& String::operator=(const String& other)
{

    if (this == &other)
        return *this;


    if (!isShort())
        delete[] _data;

    copy(other._data, other._size);

    return *this;

}

String& String::operator=(const char* const s)
{
    
    if (!isShort())
        delete[] _data;

    if (s == nullptr)
        copy("", 0);

    else
        copy(s, strlen(s));

    return *this;

}

String& String::operator=(String&& other) noexcept
{
    
  if (this == &other)
  
    return *this;
  
  if (!isShort())
    delete[] _data;
  

  move(other);

  return *this;

}

} // end namespace tcii::ex
