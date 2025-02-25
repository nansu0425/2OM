#pragma once

namespace Server::CppCore::Thread
{
    /*----------------*
     *    TlsGuard    *
     *----------------*/

    class TlsGuard
    {
    public:
        using ThreadId = uint32_t;

    public:
        TlsGuard();

        static ThreadId GetThreadId();
        static std::stack<DeadlockDetector::LockId>& GetLockStack();

    private:
        static void AssignThreadId();

    private:
        static thread_local ThreadId t_threadId;
        static thread_local std::stack<DeadlockDetector::LockId> t_lockStack;

    };
}
