#ifndef THREADMANAGER_H
#define THREADMANAGER_H
#include <QThread>

/// Thread manager. Singleton
class ThreadManager
{
public:
    static ThreadManager *instance() {
        static ThreadManager tm;
        return &tm;
    }
public:
    //QThread * getThread1();
    QThread * getThread2();
private:
    ThreadManager();
    ~ThreadManager();
private: // data
    //QThread thread1;
    QThread thread2;
};

#endif // THREADMANAGER_H
