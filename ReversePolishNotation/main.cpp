#include "Lexem.h"
#include "Parser.h"
#include "RPNComputer.h"

#include <vector>
#include <string>
#include <cstdio>
#include <cassert>

void TEST_RPNCalculator( ) {
    {
        std::string inputStr = "15 3 / 11 + 3 5 * - 3.2 / 5.6 10 - *"; // ((((15 / 3) + 11) - (3 * 5)) / 3.2) * (5.6 - 10) = -1.375
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == -1.375);
    }
    {
        std::string inputStr = "8 2 5 * + 1 3 2 * + 4 - /"; // (8 + (2 * 5)) / ((1 + (3 * 2)) - 4) = 18 / 3 = 6
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == 6);
    }
    {
        std::string inputStr = "1 2 + 4 * 3 +"; // ((1 + 2) * 4) + 3 = 15
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == 15);
    }
    {
        std::string inputStr = "3 4 + 1 - 2 / 3 *"; // (((3 + 4) - 1) / 2) * 3 = 9
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == 9);
    }
    {
        std::string inputStr = "85 3 4 + - 2 / 3 *"; // ((85 - (3 + 4)) / 2) * 3 = 117
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == 117);
    }
}

int main(int argc, char *argv[]) {

    TEST_RPNCalculator();

    return 0;
}
