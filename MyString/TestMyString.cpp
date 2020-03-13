#include "TestMyString.h"
#include "MyString.h"
#include <cassert>

void TEST_MyString_ConstructFromChar() {
    MyString t = 'a'; // конструктор копирования символа
    assert(t.GetLength() == 1);
    assert(t.GetString() != nullptr);
    assert(strcmp(t.GetString(), "a") == 0);
}

void TEST_MyString_ConstructFromCString() {
    MyString s = "Hello"; // конструктор копирования C-строки
    assert(s.GetLength() == 5);
    assert(s.GetString() != nullptr);
    assert(strcmp(s.GetString(), "Hello") == 0);

    MyString t = ""; // конструктор копирования пустой C-строки
    assert(t.GetLength() == 0);
}

void TEST_MyString_DefaultConstructor() {
    MyString u;       // конструктор по умолчанию
    assert(u.GetLength() == 0);
    assert(u.GetString() == nullptr);
}

void TEST_MyString_CopyConstructor() {
    MyString s = "Hello"; // конструктор копирования C-строки
    MyString v((s)); // конструктор копирования
    assert(v.GetLength() == 5);
    assert(v.GetString() != nullptr);
    assert(strcmp(v.GetString(), "Hello") == 0);
}

void TEST_MyString_NotEqualOperator() {
    MyString s = "Hello";
    MyString t = "allo";
    MyString u = "allo";
    assert(s != t);
    assert(false == (t != u));
}
void TEST_MyString_EqualOperator() {
    MyString s = "Hello";
    MyString t = "Hello";
    MyString u = "allo";
    assert(s == t);
    assert(false == (s == u));
}

void TEST_MyString_PlusMyStringOperator() {
    MyString s = "Hello";
    MyString v = " world";
    MyString a = s + v;
    assert(a.GetLength() == 11);
    assert(strcmp(a.GetString(), "Hello world") == 0);
}
void TEST_MyString_PlusCStringOperator() {
    MyString s = "Hello";
    MyString a = s + " world";
    assert(a.GetLength() == 11);
    assert(strcmp(a.GetString(), "Hello world") == 0);
}

void TEST_MyString_PlusCharOperator() {
    MyString s = "Hello";
    MyString a = s + '!';
    assert(a.GetLength() == 6);
    assert(strcmp(a.GetString(), "Hello!") == 0);
}

void TEST_MyString_AssignMyStringOperator() {
    MyString s = "Hello";
    MyString a;
    a = s; // присваивание пустому объекту
    assert(a.GetLength() == 5);
    assert(strcmp(a.GetString(), "Hello") == 0);

    MyString b = "This is a test";
    b = s; // присваивание непустому объекту, который длиннее, чем присваиваемый
    assert(b.GetLength() == 5);
    assert(strcmp(b.GetString(), "Hello") == 0);

    MyString c;
    b = c; // присваивание пустого объекта
    assert(b.GetLength() == 0);
    assert(b.GetString() == nullptr);
}

void TEST_MyString_AssignCStringOperator() {
    MyString a;
    a = "Hello";
    assert(a.GetLength() == 5);
    assert(strcmp(a.GetString(), "Hello") == 0);

    a = ""; // присваивание пустой строки
    assert(a.GetLength() == 0);
    assert(a.GetString() == nullptr);
}

void TEST_MyString_AssignCharOperator() {
    MyString a;
    a = 'c';
    assert(a.GetLength() == 1);
    assert(strcmp(a.GetString(), "c") == 0);
}

void TEST_MyString_IndexingOperator() {
    MyString s = "Hello";
    assert(s[0] == 'H');
    s[1] = 'a'; // оператор индексирования
    assert(s.GetLength() == 5);
    assert(strcmp(s.GetString(), "Hallo") == 0);
}

void TEST_MyString_StreamOutputOperator() {

    MyString a;
    MyString b = "Hello World";
    // Оператор вывода в поток
    std::cout << "Empty string: >" << a << "<\n";
    std::cout << "String: " << b << std::endl;
}

void TEST_MyString_FindSymbol() {
    MyString b = "Hello World";
    size_t found = b.findChar('W');
    assert(found == 6);

    found = b.findChar('p');
    assert(found == (size_t)-1);
}

void TEST_MyString_FindSubstring() {
    MyString b = "Hello World";
    size_t found = b.findSubstring("World");
    assert(found == 6);

    found = b.findSubstring("worlD");
    assert(found == (size_t)-1);

    found = b.findSubstring("");
    assert(found == 0);
}

void TEST_MyString_All() {
    TEST_MyString_ConstructFromChar();
    TEST_MyString_ConstructFromCString();
    TEST_MyString_DefaultConstructor();
    TEST_MyString_CopyConstructor();

    TEST_MyString_EqualOperator();
    TEST_MyString_NotEqualOperator();

    TEST_MyString_PlusMyStringOperator();
    TEST_MyString_PlusCStringOperator();
    TEST_MyString_PlusCharOperator();

    TEST_MyString_AssignMyStringOperator();
    TEST_MyString_AssignCStringOperator();
    TEST_MyString_AssignCharOperator();

    TEST_MyString_IndexingOperator();

    TEST_MyString_StreamOutputOperator();
}
