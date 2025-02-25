#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    Lock::Lock() noexcept
        : _srwLock(SRWLOCK_INIT)
    {}

    void Lock::Acquire(DeadlockDetector::LockName name)
    {
#if _DEBUG
        DeadlockDetector::PushLock(name);
#endif // _DEBUG

        AcquireSRWLockExclusive(&_srwLock);
    }

    void Lock::Release(DeadlockDetector::LockName name)
    {
#if _DEBUG
        DeadlockDetector::PopLock(name);
#endif // _DEBUG

        ReleaseSRWLockExclusive(&_srwLock);
    }

    LockGuard::LockGuard(Lock& lock, DeadlockDetector::LockName name)
        : _lock(lock)
        , _name(name)
    {
        _lock.Acquire(_name);
    }

    LockGuard::~LockGuard()
    {
        _lock.Release(_name);
    }
}
