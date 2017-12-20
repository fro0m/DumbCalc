#ifndef QUEUERESULTS_H
#define QUEUERESULTS_H
#include <QQueue>
#include <QMutex>
#include "DataTypes/result.h"

/// wrapper
class QueueResults
{
public:
    static QueueResults *instance() {
        static QueueResults queueResults;
        return &queueResults;
    }
public:
    Result dequeue();
    void enqueue(const Result &Result);
    int size();
private:
    QueueResults();
private:
    mutable QMutex m_mutex;
    QQueue<Result> m_results;
};

#endif // QUEUERESULTS_H
