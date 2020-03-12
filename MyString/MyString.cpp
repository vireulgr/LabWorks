#include "MyString.h"

// DONE
MyString::MyString() : m_str(nullptr), m_length(0) {
}

// TODO: TEST
MyString::MyString(const char _char) {
    m_length = 2;
    m_str = new char[2];

    m_str[0] = _char;
    m_str[1] = '\0';
}

// TODO: TEST
MyString::MyString(const char* _string) {
    m_length = strlen(_string); // length without '\0'
    m_str = new char[m_length+1];

    strcpy(m_str, _string);
}

// TODO: TEST
MyString::MyString(const MyString& _string) {
    m_length = _string.GetLength();
    m_str = new char[m_length+1];

    strcpy(m_str, _string.GetString());
}

// TODO TEST
MyString::~MyString() {
    if (m_str != nullptr) {
        delete[] m_str;
    }
    m_length = 0;
}

// DONE
size_t MyString::GetLength() const {
    return m_length;
}

// DONE
const char* MyString::GetString() const {
    return m_str;
}

// TODO: TEST
char& MyString::operator [] (const size_t index) const {
    return m_str[index];
}

// TODO: TEST
MyString& MyString::operator = (const MyString& rightString) {
    if (this == &rightString) return *this;

    size_t const otherLen = rightString.GetLength();
    if (otherLen != m_length) {
        delete[] m_str;
        m_str = new char[otherLen+1];
    }

    strcpy(m_str, rightString.GetString());
}

// TODO: TEST
MyString& MyString::operator = (const char* rightChars) {
    size_t const otherLen = strlen(rightChars);  // length without '\0'
    if (otherLen != m_length) {
        delete[] m_str;
        m_str = new char[otherLen+1];
    }

    strcpy(m_str, rightChars);
}

// TODO: TEST
MyString& MyString::operator = (const char rightChar) {
    if (2 != m_length) {
        delete[] m_str;
        m_str = new char[2];
    }

    m_str[0] = rightChar;
    m_str[1] = '\0';
}

MyString& MyString::operator += (const MyString& rightString) {
}

MyString& MyString::operator += (const char* rightChars) {
    size_t otherLen = strlen(rightChars);  // length without '\0'
}

MyString& MyString::operator += (const char rightChar) {
}

const MyString  MyString::operator + (const MyString& rightString) const {
}

const MyString  MyString::operator + (const char* rightChars) const {
    size_t otherLen = strlen(rightChars);  // length without '\0'
}

const MyString  MyString::operator + (const char rightChar) const {
}

// TODO: TEST
bool MyString::operator == (const MyString& rightString) const {
    if (rightString.GetLength() != m_length)
        return false;

    return 0 == strcmp(m_str, rightString.GetString());
}

// TODO: TEST
bool MyString::operator != (const MyString& rightString) const {
    return !(*this == rightString);
}

// TODO: TEST
std::ostream& operator << (std::ostream& os, const MyString& myString) {
    os << myString.GetString();
    return os;
}

// TODO
std::istream& operator >> (std::istream& is, MyString& myString) {
    return is;
}
