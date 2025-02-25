#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    TlsGuard::TlsGuard()
    {
        AssignThreadId();
    }

    TlsGuard::ThreadId TlsGuard::GetThreadId()
    {
        return t_threadId;
    }

    std::stack<DeadlockDetector::LockId>& TlsGuard::GetLockStack()
    {
        return t_lockStack;
    }

    void TlsGuard::AssignThreadId()
    {
        // 1부터 순차적으로 할당
        static std::atomic<ThreadId> s_nextId = 1;
        t_threadId = s_nextId.fetch_add(1);
    }

    // Id가 할당되지 않은 상태에선 0
    thread_local TlsGuard::ThreadId TlsGuard::t_threadId = 0;
    thread_local std::stack<DeadlockDetector::LockId> TlsGuard::t_lockStack;
}
