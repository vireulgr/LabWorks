#pragma once
#include <vector>
#include "Lexem.h"

class RPNComputer {
public:
    RPNComputer();
    ~RPNComputer();

    double compute(std::vector<Lexem> const & a);
};

