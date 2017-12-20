#ifndef JOURNALITEM_H
#define JOURNALITEM_H
#include <QString>
#include <QtGlobal>
#include "calclib/calclib.h"


class JournalItem
{
public:
    enum ItemType : quint8 {
        Request,
        Error,
        Result
    };
//public:
//    JournalItem();
public: // data
    QString text;
    ItemType itemType;
    CalcLib::ErrorCode errorCode;
};

#endif // JOURNALITEM_H
