#include "Core/CommonPch.h"

namespace Game::Core
{
    ThreadLocalGuard::ThreadLocalGuard()
    {
        AssignThreadId();
    }

    ThreadLocalGuard::~ThreadLocalGuard()
    {}

    uint32_t ThreadLocalGuard::GetThreadId()
    {
        return t_threadId;
    }

    void ThreadLocalGuard::AssignThreadId()
    {
        // 1부터 순차적으로 할당
        static std::atomic<uint32_t> s_nextId = 1;
        t_threadId = s_nextId.fetch_add(1);
    }

    // Id가 할당되지 않은 상태에선 0
    thread_local uint32_t ThreadLocalGuard::t_threadId = 0;
}
