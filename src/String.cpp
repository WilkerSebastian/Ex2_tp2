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

String String::operator+(const char* const s) const
{

    String result(*this);

    result += s;

    return result;

}

String String::operator+(const String& other) const
{
    
    String result(*this);

    result += other;

    return result;

}

String& String::operator+=(const char* const s)
{
    
    if (s == nullptr || *s == '\0')
        return *this;
  

    const unsigned s_len = strlen(s);
    const unsigned newSize = _size + s_len;

    if (newSize > capacity())
    {

        const unsigned newCapacity = (newSize / maxBuffer + 1) * maxBuffer;
        char* newData = new char[newCapacity + 1];

        memcpy(newData, _data, _size);

        if (!isShort())
            delete[] _data;
        
        _data = newData;
        _capacity = newCapacity;

    }

    memcpy(_data + _size, s, s_len);

    _size = newSize;
    _data[_size] = '\0';

    return *this;

}

String& String::operator+=(const String& other)
{
    
    if (other.empty())
        return *this;

    const unsigned newSize = _size + other._size;

    if (newSize > capacity())
    {

        const unsigned newCapacity = (newSize / maxBuffer + 1) * maxBuffer;
        char* newData = new char[newCapacity + 1];

        memcpy(newData, _data, _size);

        if (!isShort())
            delete[] _data;


        _data = newData;
        _capacity = newCapacity;

    }

    memcpy(_data + _size, other._data, other._size);

    _size = newSize;
    _data[_size] = '\0';

    return *this;

}

} // end namespace tcii::ex
