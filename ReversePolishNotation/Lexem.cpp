#include "Lexem.h"
#include <cstring>


Lexem CreateLexem(std::string const & in) {
  Lexem res;

  if (in[0] == '+') {
    res.m_type = LexemType::plus;
  }
  else if (in[0] == '*') {
    res.m_type = LexemType::multiply;
  }
  else if (in[0] == '/') {
    res.m_type = LexemType::divide;
  }
  else if (in[0] == '-') {
    res.m_type = LexemType::minus;
  }
  else {
    // TODO
    double number = strtod( in.c_str() );
    // 2 3 + 3 - 123 - 123 - # ((((2 + 3) - 3) - 123) - 123)
    // 2 3 5 3 - + * - # - (2 * (3 + (5 - 3)))
    if (0 != 1) {
      res.m_type = LexemType::number;
    }
    else {
      res.m_type = LexemType::unknown;
    }
  }

  strcpy(res.m_val, in.c_str());
  return res;
}

Lexem::Lexem() {}

Lexem::~Lexem() {}

bool Lexem::isValid() { return m_type == LexemType::unknown; }
