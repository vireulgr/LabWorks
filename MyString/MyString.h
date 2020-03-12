#pragma once

#include <iostream>

class MyString {

private:
    char* m_str;
    size_t m_length; // number of chars not including first '\0' character
public:
    MyString();
    MyString(const char _char);
    MyString(const char* _string);
    MyString(const MyString& _string);
    ~MyString();
    size_t GetLength() const;
    const char* GetString() const;
    char& operator [] (const size_t index) const;
    MyString& operator = (const MyString& rightString);
    MyString& operator = (const char* rightChars);
    MyString& operator = (const char rightChar);
    bool operator == (const MyString& rightString) const;
    bool operator != (const MyString& rightString) const;
    MyString& operator += (const MyString& rightString);
    MyString& operator += (const char* rightString);
    MyString& operator += (const char rightChar);
    const MyString operator + (const MyString& rightString) const;
    const MyString operator + (const char* rightString) const;
    const MyString operator + (const char rightChar) const;

    friend std::ostream& operator << (std::ostream& os, const MyString& myString);
    friend std::istream& operator >> (std::istream& is, MyString& myString);
};

std::ostream& operator << (std::ostream& os, const MyString& myString);

std::istream& operator >> (std::istream& is, MyString& myString);

