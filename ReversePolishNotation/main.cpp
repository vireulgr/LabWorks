#include "Lexem.h"
#include "Parser.h"
#include "RPNComputer.h"

#include <vector>
#include <string>
#include <cstdio>
#include <cassert>

void TEST_RPNCalculator( ) {
    {
        std::string inputStr = "3 4 8 1 3 + - / *"; // 3 * (4 / (8 - (1 + 3))) = 3
        Parser parser;
        std::vector<Lexem> lexems = parser.parse(inputStr);

        RPNComputer computer;
        double res = computer.compute(lexems);
        assert(res == 3);
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
