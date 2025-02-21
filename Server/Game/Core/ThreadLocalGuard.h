#pragma once

namespace Game::Core
{
    /*------------------------*
     *    ThreadLocalGuard    *
     *------------------------*/

    class ThreadLocalGuard
    {
    public:
        ThreadLocalGuard();
        ~ThreadLocalGuard();

        static uint32_t GetThreadId();

    private:
        static void AssignThreadId();

    private:
        static thread_local uint32_t t_threadId;

    };
}
