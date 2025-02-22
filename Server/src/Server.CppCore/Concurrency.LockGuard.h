#pragma once

namespace Server::CppCore::Concurrency
{
    /*--------------------------*
     *    ExclusiveLockGuard    *
     *--------------------------*/

    class ExclusiveLockGuard
    {
    public:
        ExclusiveLockGuard(LockHolder& lockHolder);
        ~ExclusiveLockGuard();

        ExclusiveLockGuard(const ExclusiveLockGuard&) = delete;
        ExclusiveLockGuard& operator=(const ExclusiveLockGuard&) = delete;

    private:
        LockHolder& _lockHolder;

    };

    /*-----------------------*
     *    SharedLockGuard    *
     *-----------------------*/

    class SharedLockGuard
    {
    public:
        SharedLockGuard(LockHolder& lockHolder);
        ~SharedLockGuard();

        SharedLockGuard(const SharedLockGuard&) = delete;
        SharedLockGuard& operator=(const SharedLockGuard&) = delete;

    private:
        LockHolder& _lockHolder;

    };
}
