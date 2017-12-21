#ifndef TASK_H
#define TASK_H
#include "calclib/calclib.h"

struct Task {
    CalcLib::TypeWork m_typeWork;
    double m_operandA;
    double m_operandB;
    int m_operationsComplexityInSec /*= 20*/; // MSVC2015 does not support default initializers when making aggregate inicialization (
};

#endif // TASK_H
