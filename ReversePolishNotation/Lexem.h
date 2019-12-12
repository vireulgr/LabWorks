#pragma once
#include <string>

enum LexemType {
    unknown,
    number,
    minus,
    plus,
    multiply,
    divide,
    unary_minus
};

class Lexem {
    LexemType m_type;
    char m_val[20];
public:
    Lexem();
    Lexem(char const * a, int len);
    ~Lexem();
};

