#include "threadmanager.h"

ThreadManager::ThreadManager() {
    //thread1.start(QThread::IdlePriority);
    thread2.start(QThread::IdlePriority);
}

ThreadManager::~ThreadManager() {
//    thread1.quit();
//    if(!thread1.wait(3000)) //Wait until it actually has terminated (max. 3 sec)
//    {
//        thread1.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
//        thread1.wait(); //We have to wait again here!
//    }
    thread2.quit();
    if(!thread2.wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        thread2.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        thread2.wait(); //We have to wait again here!
    }
}

QThread *ThreadManager::getThread2()
{
    return &thread2;
}

//QThread *ThreadManager::getThread1()
//{
//    return &thread1;
//}
