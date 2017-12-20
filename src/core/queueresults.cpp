#include <QMutexLocker>
#include "queueresults.h"
#include <QDebug>

Result QueueResults::dequeue() {
    QMutexLocker locker(&m_mutex);
    return m_results.dequeue();
}

void QueueResults::enqueue(const Result &Result)
{
    QMutexLocker locker(&m_mutex);
    m_results.enqueue(Result);
}

int QueueResults::size() {
    QMutexLocker locker(&m_mutex);
    return m_results.size();
}

QueueResults::QueueResults()
{

}
