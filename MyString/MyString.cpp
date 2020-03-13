#include "MyString.h"
#include <cstring>

// =============================================================
MyString::MyString() : m_str(nullptr), m_length(0) {}

// =============================================================
void MyString::initialize(char const * str, size_t const len) {
    m_length = len;
    m_str = new char[len + 1];

    strcpy_s(m_str, (len + 1) * sizeof(char), str);
}

// =============================================================
MyString::MyString(char const _char) {
    // hack
    initialize("a", 1);
    m_str[0] = _char;
}

// =============================================================
MyString::MyString(char const * _string) {
    size_t const otherLen = strlen(_string); // length without '\0'
    if(otherLen > 0) {
        initialize(_string, otherLen);
    }
}

// =============================================================
MyString::MyString(MyString const & _string) {
    size_t const otherLen = _string.GetLength();
    if(otherLen > 0) {
        initialize(_string.GetString(), otherLen);
    }
}

// =============================================================
MyString::~MyString() {
    if (m_str != nullptr) {
        delete[] m_str;
    }
    m_length = 0;
}

// =============================================================
size_t MyString::GetLength() const {
    return m_length;
}

// =============================================================
const char* MyString::GetString() const {
    return m_str;
}

// =============================================================
char& MyString::operator [] (size_t const index) const {
    return m_str[index];
}

// =============================================================
MyString& MyString::operator = (MyString const & rightString) {
    if (this == &rightString) return *this;

    size_t const otherLen = rightString.GetLength();

    if (otherLen == 0) {
        delete[] m_str;
        m_str = nullptr;
        m_length = 0;
    } 
    else if (m_length < otherLen) {
        delete[] m_str;
        initialize(rightString.GetString(), otherLen);
    }
    else {
        strcpy_s(m_str, (otherLen + 1)*sizeof(char), rightString.GetString());
        m_length = otherLen;
    }

    return *this;
}

// =============================================================
MyString& MyString::operator = (char const * rightChars) {
    size_t const otherLen = strlen(rightChars);  // length without '\0'

    if (otherLen == 0) {
        delete[] m_str;
        m_str = nullptr;
        m_length = 0;
    } 
    else if (m_length < otherLen) {
        delete[] m_str;
        initialize(rightChars, otherLen);
    }
    else {
        strcpy_s(m_str, (otherLen + 1)*sizeof(char), rightChars);
        m_length = otherLen;
    }

    return *this;
}

// =============================================================
MyString& MyString::operator = (const char rightChar) {

    if(m_length > 1) {
        m_str[0] = rightChar;
        m_str[1] = '\0';
        m_length = 1;
    }
    else {
        // hack
        initialize("a", 1);
        m_str[0] = rightChar;
    }

    return *this;
}

// =============================================================
void MyString::append(char const * rightString, size_t len) {

    char * tmp = new char[len + m_length + 1];
    strcpy_s(tmp,            (m_length + 1) * sizeof(char), m_str);
    strcpy_s(tmp + m_length, (len + 1) * sizeof(char)     , rightString);

    if (m_str != nullptr) {
        delete[] m_str;
    }
    m_str = tmp;

    m_length += len;
}

// =============================================================
MyString& MyString::operator += (const MyString& rightString) {
    size_t const otherLen = rightString.GetLength();

    if (otherLen == 0) {
        return *this;
    }

    append(rightString.GetString(), otherLen);

    return *this;
}

// =============================================================
MyString& MyString::operator += (const char* rightChars) {

    if (rightChars == nullptr) {
        return *this;
    }

    size_t const otherLen = strlen(rightChars);  // length without '\0'

    if (otherLen == 0) {
        return *this;
    }

    append(rightChars, otherLen);

    return *this;
}

// =============================================================
MyString& MyString::operator += (const char rightChar) {

    // hack
    append("a", 1);
    m_str[m_length - 1] = rightChar;

    return *this;
}

// =============================================================
const MyString MyString::operator + (const MyString& rightString) const {
    MyString myCopy(*this);
    myCopy += rightString;
    return myCopy;
}

// =============================================================
const MyString MyString::operator + (const char* rightChars) const {
    MyString myCopy(*this);
    myCopy += rightChars;
    return myCopy;
}

// =============================================================
const MyString MyString::operator + (const char rightChar) const {
    MyString myCopy(*this);
    myCopy += rightChar;
    return myCopy;
}

// TODO: TEST
size_t MyString::findChar(char const symbol) const {
    for (int i = 0; i < m_length; i++) {
        if (m_str[i] == symbol) {
            return i;
        }
    }
    return (size_t)-1;
}

// TODO: TEST
size_t MyString::findSubstring(char const * str) const {
    size_t const otherLen = strlen(str);
    if (otherLen == 0 ) {
        return 0;
    }
    if (otherLen < m_length) {
        return (size_t)-1;
    }

    char * tmp = strstr(m_str, str);
    if(tmp == nullptr) {
        return (size_t)-1;
    }

    //size_t i = 0;
    //for (; i < m_length; i++) {
    //    if (tmp == m_str + i) {
    //        break;
    //    }
    //}
    size_t i = (tmp - m_str) / sizeof(char);
    return i;
}

// =============================================================
bool MyString::operator == (const MyString& rightString) const {
    if (rightString.GetLength() != m_length)
        return false;

    return 0 == strcmp(m_str, rightString.GetString());
}

// =============================================================
bool MyString::operator != (const MyString& rightString) const {
    return !(*this == rightString);
}

// TODO
MyString& MyString::insert(MyString const & str, size_t const pos) {
    return *this;
}

// TODO: TEST
MyString::iterator MyString::begin() {
    return iterator(*this, 0);
}

// TODO: TEST
MyString::iterator MyString::end() {
    return iterator(*this, m_length);
}

// TODO: TEST
char& MyString::iterator::operator*() {
    return object[position];
}

// TODO: TEST
MyString::iterator& MyString::iterator::operator++() {
    ++position;
    return *this;
}

// TODO: TEST
MyString::iterator MyString::iterator::operator++(int) {
    iterator tmp((*this));
    ++position;
    return tmp;
}

// =============================================================
std::ostream& operator << (std::ostream& os, const MyString& myString) {
    if (myString.GetLength() != 0) {
        os << myString.GetString();
    }
    return os;
}

// TODO
std::istream& operator >> (std::istream& is, MyString& myString) {
    return is;
}
