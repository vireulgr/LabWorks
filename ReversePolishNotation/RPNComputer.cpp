#include "RPNComputer.h"

double myPlus(double left, double right) { return left + right; }
double myMinus(double left, double right) { return left - right; }
double myDivide(double left, double right) { return left / right; }
double myMultiply(double left, double right) { return left * right; }

typedef double(*MyFunctionType)(double, double);

RPNComputer::RPNComputer() {}

RPNComputer::~RPNComputer() {}

double RPNComputer::compute(std::vector<Lexem> const & input) {
    std::vector<Lexem> temp;
    temp.reserve(input.size() / 2);

    int idx = 0;
    for(; idx < input.size(); ++idx) {
        LexemType lexemType = input[idx].getType();

        if (lexemType == LexemType::plus
           || lexemType == LexemType::minus
           || lexemType == LexemType::multiply
           || lexemType == LexemType::divide)
        {
            MyFunctionType lexemFunction = nullptr;

            switch(lexemType) {
            case LexemType::plus: lexemFunction = myPlus; break;
            case LexemType::minus: lexemFunction = myMinus; break;
            case LexemType::multiply: lexemFunction = myMultiply; break;
            case LexemType::divide: lexemFunction = myDivide; break;
            }

            double rightArg = 0.0;
            double leftArg = 0.0;

            if(!temp.empty()) {
                rightArg = temp.back().getDoubleValue();
                temp.pop_back();
            }
            if(!temp.empty()) {
                leftArg = temp.back().getDoubleValue();
                temp.pop_back();
            }
            double res = lexemFunction(leftArg, rightArg);
            Lexem the = CreateLexem(res);
            temp.push_back(the);
        }
        else if(lexemType == LexemType::number) {
            temp.push_back(input[idx]);
        }
    }

    return temp.back().getDoubleValue();
}
