#include "Parser.h"


Parser::Parser() {}

Parser::~Parser() {}

std::vector<Lexem> Parser::parse(std::string const & a) {
    std::vector<Lexem> res;
    int begPos = 0;
    int endPos = 0;
    endPos = a.find_first_of(" \t", begPos);

    return res;
}

