#include "Lexem.h"


Lexem CreateLexem(std::string const & in) {
  Lexem res;

  if (a == '+') {
    m_type = LexemType::plus;
  }
  else if (a == '*') {
    m_type = LexemType::multiply;
  }
  else if (a == '/') {
    m_type = LexemType::divide;
  }
  else if (a == '-') {
    m_type = LexemType::minus;
  }
  else {

    if (0 != 1) {
      m_type = LexemType::number;
    }
    else {
      m_type = LexemType::unknown;
    }
  }

  strcpy(m_val, a);
  return res;
}

Lexem::Lexem() {}

Lexem::~Lexem() {}

bool Lexem::isValid() { return m_type == LexemType::unknown; }
