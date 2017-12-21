#include "core/threadmanager.h"
#include "queueswatcher.h"
#include "core/queuerequests.h"
#include "core/queueresults.h"
#include <QDebug>


QueuesWatcher::QueuesWatcher(QObject *parent) : QObject(parent)
{
    auto thread = ThreadManager::instance()->getThread2();
    Q_ASSERT(thread->isRunning());
    moveToThread(thread);
    thread->setPriority(QThread::LowPriority);
    qDebug() << "QueuesWatcher's thread is " << QObject::thread();
    timer.start(50); // updating every 50 msec
    connect(&timer, &QTimer::timeout, [this]{
        int size = QueueRequests::instance()->size();
        if (size != requestsSize()) {
            setRequestsSize(size);
        }
        size = QueueResults::instance()->size();
        if (size != resultsSize()) {
            setResultsSize(size);
            if(size > 0) {
                emit resultIsReady(QueueResults::instance()->dequeue());
            }
        }
    });
}

void QueuesWatcher::submitTask(const Task &task)
{
    QueueRequests::instance()->enqueue(task);
}

void QueuesWatcher::setRequestsSize(int requestsSize)
{
    if (m_requestsSize == requestsSize)
        return;
    m_requestsSize = requestsSize;
    emit requestsSizeChanged(m_requestsSize);
}

void QueuesWatcher::setResultsSize(int resultsSize)
{
    if (m_resultsSize == resultsSize)
        return;

    m_resultsSize = resultsSize;
    emit resultsSizeChanged(m_resultsSize);
}
