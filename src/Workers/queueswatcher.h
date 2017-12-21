#ifndef QUEUESWATCHER_H
#define QUEUESWATCHER_H

#include <QObject>
#include <QTimer>
#include "DataTypes/result.h"
#include "DataTypes/task.h"

class QueuesWatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int requestsSize READ requestsSize WRITE setRequestsSize NOTIFY requestsSizeChanged)
    Q_PROPERTY(int resultsSize READ resultsSize WRITE setResultsSize NOTIFY resultsSizeChanged)
public:
    explicit QueuesWatcher(QObject *parent = nullptr);
public:
    int requestsSize() const
    {
        return m_requestsSize;
    }
    int resultsSize() const
    {
        return m_resultsSize;
    }

protected:
    /// checking for changing sizes
//    void timerEvent(QTimerEvent *event);

signals:
    void requestsSizeChanged(int requestsSize);
    void resultsSizeChanged(int resultsSize);

signals: // data exchange
    void resultIsReady(const Result &result);
public slots: // data exchange
    void submitTask(const Task &task);

public slots:
    void setRequestsSize(int requestsSize);
    void setResultsSize(int resultsSize);
private: // misc
    QTimer timer;
private: // data
    int m_requestsSize = 0;
    int m_resultsSize = 0;
};

#endif // QUEUESWATCHER_H
