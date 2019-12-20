#include "Parser.h"


Parser::Parser() {}

Parser::~Parser() {}

std::vector<Lexem> Parser::parse(std::string const & a) {
    std::vector<Lexem> res;

    int begPos = 0;
    int endPos = 0;
    endPos = a.find(' ', begPos);
    while (begPos != std::string::npos) {
      std::string tmp = a.substr(begPos, endPos - begPos);
      Lexem aLexem = CreateLexem(tmp);
      if (aLexem.isValid()) {
        res.push_back(aLexem);
      }
      begPos = endPos + 1;
      endPos = a.find(' ', begPos);
    }

    return res;
}

