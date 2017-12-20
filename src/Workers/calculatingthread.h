#ifndef CALCULATINGTHREAD_H
#define CALCULATINGTHREAD_H

#include <QThread>
#include <QQueue>
#include "calclib/calclib.h"
#include "DataTypes/result.h"


class CalculatingThread : public QThread
{   
    Q_OBJECT
public:
    CalculatingThread();
    ~CalculatingThread();

protected:
    void run() override;

};

#endif // CALCULATINGTHREAD_H
