#ifndef QUEUEREQUESTS_H
#define QUEUEREQUESTS_H
#include <QQueue>
#include <QMutex>
#include "DataTypes/task.h"

class QueueRequests
{
public:
    static QueueRequests *instance() {
        static QueueRequests queueRequests;
        return &queueRequests;
    }
public:
    Task dequeue();
    void enqueue(const Task &task);
    int size();
private:
    QueueRequests();
private:
    mutable QMutex m_mutex;
    QQueue<Task> m_requests;
};

#endif // QUEUEREQUESTS_H
