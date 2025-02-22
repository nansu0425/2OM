#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Concurrency
{
    LockHolder::LockHolder()
        : _lock(SRWLOCK_INIT)
    {}

    LockHolder::~LockHolder()
    {}

    void LockHolder::AcquireExclusiveLock()
    {
        AcquireSRWLockExclusive(&_lock);
    }

    void LockHolder::ReleaseExclusiveLock()
    {
        ReleaseSRWLockExclusive(&_lock);
    }

    void LockHolder::AcquireSharedLock()
    {
        AcquireSRWLockShared(&_lock);
    }

    void LockHolder::ReleaseSharedLock()
    {
        ReleaseSRWLockShared(&_lock);
    }
}