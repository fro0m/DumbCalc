#ifndef CALCLIB_H
#define CALCLIB_H
#include <QtCore/QtGlobal>

#if defined(CALCLIB)
#define CALCLIB_COMMON_DLLSPEC Q_DECL_EXPORT
#else
#define CALCLIB_COMMON_DLLSPEC Q_DECL_IMPORT
#endif
namespace CalcLib {
enum TypeWork : int {
    Addition = 0,
    Subtraction = 1,
    Division = 2,
    Multiplication = 3
};
enum ErrorCode : int {
    Div0 = -9,
    WrongTypeWork = -8,
    Ok = 0,
    OperandIsWorng = - 7
};
}

CALCLIB_COMMON_DLLSPEC double DoIt(int TypeWork, double OperandA, double OperandB, int& ErrorCode);

#endif // CALCLIB_H
