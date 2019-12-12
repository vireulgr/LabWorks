#pragma once
#include "Lexem.h"
#include <vector>
#include <string>

class Parser {
public:
    Parser();
    ~Parser();

    std::vector<Lexem> parse(std::string const & a);
};

