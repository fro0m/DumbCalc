#include <QMutexLocker>
#include "queuerequests.h"

Task QueueRequests::dequeue() {
    QMutexLocker locker(&m_mutex);
    return m_results.dequeue();
}

void QueueRequests::enqueue(const Task &task)
{
    QMutexLocker locker(&m_mutex);
    m_results.enqueue(task);
}

int QueueRequests::size() {
    QMutexLocker locker(&m_mutex);
    return m_results.size();
}

QueueRequests::QueueRequests()
{

}
