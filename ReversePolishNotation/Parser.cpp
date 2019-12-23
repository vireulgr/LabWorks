#include "Parser.h"


Parser::Parser() {}

Parser::~Parser() {}

std::vector<Lexem> Parser::parse(std::string const & a) {
    std::vector<Lexem> res;
    res.reserve(a.length() / 2);

    int begPos = 0;
    int endPos = a.find(' ', begPos);

    while (true) {
      std::string tmp = a.substr(begPos, endPos - begPos);
      Lexem aLexem = CreateLexem(tmp);
      if (aLexem.isValid()) {
        res.push_back(aLexem);
      }

      if(endPos == std::string::npos) break;

      begPos = endPos + 1;
      endPos = a.find(' ', begPos);
    }

    return res;
}

