#include "Lexem.h"
#include <cstring>

int skipSpaces(std::string const & in) {
    int i = 0;
    for (; i < in.size(); ++i) {
        if (in[i] != ' ') break;
    }
    return i;
}

Lexem CreateLexem(double val) {
    Lexem res;
    res.m_type = LexemType::number;
    char buffer[100] = {0};
    int aSize = sprintf(buffer, "%g", val) + 1;
    int min = (20 < aSize) ? 20 : aSize;
    strncpy(res.m_val, buffer, aSize);
    return res;
}

Lexem CreateLexem(std::string const & in) {
    Lexem res;
    int idx = skipSpaces(in);
    if(in[idx] == '+') {
        res.m_type = LexemType::plus;
    }
    else if(in[idx] == '*') {
        res.m_type = LexemType::multiply;
    }
    else if(in[idx] == '/') {
        res.m_type = LexemType::divide;
    }
    else if(in[idx] == '-') {
        res.m_type = LexemType::minus;
    }
    else {
        // TODO
        // 2 3 + 3 - 123 - 123 - # ((((2 + 3) - 3) - 123) - 123)
        // 2 3 5 3 - + * - # - (2 * (3 + (5 - 3)))
        double number = strtof(in.c_str(), nullptr);
        if(number == 0.0) {
            // TODO Error?
            res.m_type = LexemType::unknown;
        }
        else {
            res.m_type = LexemType::number;
        }
    }

    memset(res.m_val, 0, 20);
    int min = (20 < in.size() - idx) ? 20 : in.size() - idx;
    strncpy(res.m_val, in.c_str() + idx, min);
    return res;
}

Lexem::Lexem() {}

Lexem::~Lexem() {}

bool Lexem::isValid() const { return m_type != LexemType::unknown; }
LexemType Lexem::getType() const { return m_type; }
double Lexem::getDoubleValue() const { return std::stod(m_val, nullptr); }
