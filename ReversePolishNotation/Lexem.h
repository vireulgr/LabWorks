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

    bool isValid() const;
    LexemType getType() const;
    double getDoubleValue() const;

    friend Lexem CreateLexem(std::string const & in);
    friend Lexem CreateLexem(double val);
};

Lexem CreateLexem(std::string const & a);
Lexem CreateLexem(double val);
