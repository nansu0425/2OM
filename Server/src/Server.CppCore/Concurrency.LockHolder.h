#pragma once

namespace Server::CppCore::Concurrency
{
    /*------------------*
     *    LockHolder    *
     *------------------*/

    class LockHolder
    {
    public:
        LockHolder();
        ~LockHolder();

        LockHolder(const LockHolder&) = delete;
        LockHolder& operator=(const LockHolder&) = delete;

        void AcquireExclusiveLock();
        void ReleaseExclusiveLock();
        void AcquireSharedLock();
        void ReleaseSharedLock();

    private:
        SRWLOCK _lock;

    };
}
