#include <QMutexLocker>
#include "queuerequests.h"

Task QueueRequests::dequeue() {
    QMutexLocker locker(&m_mutex);
    return m_requests.dequeue();
}

void QueueRequests::enqueue(const Task &task)
{
    QMutexLocker locker(&m_mutex);
    m_requests.enqueue(task);
}

int QueueRequests::size() {
    QMutexLocker locker(&m_mutex);
    return m_requests.size();
}

QueueRequests::QueueRequests()
{

}
