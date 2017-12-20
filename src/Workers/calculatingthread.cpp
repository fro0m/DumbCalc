#include <QDebug>
#include <QTime>
#include "calculatingthread.h"
#include "core/queuerequests.h"
#include "core/queueresults.h"

using namespace CalcLib;

CalculatingThread::CalculatingThread()
{
    moveToThread(this);
    start(QThread::IdlePriority);
    qDebug() << "CalculatingThread's thread is " << QObject::thread();
}

CalculatingThread::~CalculatingThread() {
    quit();
    if(!wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        wait(); //We have to wait again here!
    }
}

void CalculatingThread::run()
{
    forever {
        if(QueueRequests::instance()->size()) {
            setPriority(QThread::HighestPriority);
            Task task = QueueRequests::instance()->dequeue();
            int errCode;
            auto result = DoIt(task.m_typeWork, task.m_operandA, task.m_operandB, errCode);
            {
                QTime timer;
                timer.start();
                while(timer.elapsed() != task.m_operationsComplexityInSec * 1000) {
                    qt_noop(); //FIXME need to terminate it explicitly by checking flag and return
                }
            }
            QueueResults::instance()->enqueue({result, static_cast<CalcLib::ErrorCode>(errCode)});
        } else {
            setPriority(QThread::IdlePriority);
        }
    }
}


