#include "calclib.h"
#include <limits>



double DoIt(int TypeWork, double OperandA, double OperandB, int &ErrorCode)
{
    switch (TypeWork) {
    case CalcLib::Addition:
        ErrorCode = CalcLib::Ok;
        return OperandA + OperandB;
    case  CalcLib::Subtraction:
        ErrorCode = CalcLib::Ok;
        return OperandA - OperandB;
    case CalcLib::Division:
        if(OperandB == 0) {
            ErrorCode = CalcLib::Div0;
            return std::numeric_limits<double>::infinity();
        }
        ErrorCode = CalcLib::Ok;
        return OperandA / OperandB;
    case CalcLib::Multiplication:
        ErrorCode = CalcLib::Ok;
        return OperandA * OperandB;
    default:
        ErrorCode = CalcLib::WrongTypeWork;
        return 0;
    }
}
