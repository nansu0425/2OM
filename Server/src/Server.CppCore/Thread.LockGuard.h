#pragma once

namespace Server::CppCore::Thread
{
    /*------------*
     *    Lock    *
     *------------*/

    class Lock
    {
    public:
        Lock() noexcept;
        
        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;

        void Acquire(DeadlockDetector::LockName name);
        void Release(DeadlockDetector::LockName name);

    private:
        SRWLOCK _srwLock;

    };

    /*-----------------*
     *    LockGuard    *
     *-----------------*/

    class LockGuard
    {
    public:
        LockGuard(Lock& lock, DeadlockDetector::LockName name);
        ~LockGuard();
        
    private:
        Lock& _lock;
        DeadlockDetector::LockName _name;

    };
}
