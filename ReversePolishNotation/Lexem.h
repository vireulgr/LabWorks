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
    ~Lexem();

    bool isValid();

    friend Lexem CreateLexem(std::string const & in);
};

Lexem CreateLexem(std::string const & a);
