#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Concurrency
{
    ExclusiveLockGuard::ExclusiveLockGuard(LockHolder& lockHolder)
        : _lockHolder(lockHolder)
    {
        _lockHolder.AcquireExclusiveLock();
    }

    ExclusiveLockGuard::~ExclusiveLockGuard()
    {
        _lockHolder.ReleaseExclusiveLock();
    }

    SharedLockGuard::SharedLockGuard(LockHolder& lockHolder)
        : _lockHolder(lockHolder)
    {
        _lockHolder.AcquireSharedLock();
    }

    SharedLockGuard::~SharedLockGuard()
    {
        _lockHolder.ReleaseSharedLock();
    }
}
