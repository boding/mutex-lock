/************************************************
 *
 * file  : MutexLock.h
 * author: bobding
 * date  : 2014-10-23
 * detail:
 *
************************************************/

#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #include <pthread.h>
#endif

class MutexLock
{
public:
    MutexLock()
    {
#if defined(_WIN32) || defined(_WIN64)
        InitializeCriticalSection(&mMutex);
#else
        pthread_mutex_init(&mMutex, 0);
#endif
    }

    ~MutexLock()
    {
#if defined(_WIN32) || defined(_WIN64)
        DeleteCriticalSection(&mMutex);
#else
        pthread_mutex_destroy(&mMutex);
#endif
    }

    void lock()
    {
#if defined(_WIN32) || defined(_WIN64)
        EnterCriticalSection(&mMutex);
#else
        pthread_mutex_lock(&mMutex);
#endif
    }

    void unlock()
    {
#if defined(_WIN32) || defined(_WIN64)
        LeaveCriticalSection(&mMutex);
#else
        pthread_mutex_unlock(&mMutex);
#endif
    }

protected:
#if defined(_WIN32) || defined(_WIN64)
    CRITICAL_SECTION mMutex;
#else
    pthread_mutex_t mMutex;
#endif
};

static MutexLock glock;

class AutoMutexLock
{
public:
    AutoMutexLock() : mLock(glock)
    {
        mLock.lock();
    }

    AutoMutexLock(MutexLock& lock) : mLock(lock)
    {
        mLock.lock();
    }

    ~AutoMutexLock()
    {
        mLock.unlock();
    }

protected:
    MutexLock& mLock;
};

#endif // _MUTEXLOCK_H_