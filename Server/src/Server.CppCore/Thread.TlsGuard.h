#pragma once

namespace Server::CppCore::Thread
{
    /*----------------*
     *    TlsGuard    *
     *----------------*/

    class TlsGuard
    {
    public:
        TlsGuard();
        ~TlsGuard();

        static uint32_t GetThreadId();

    private:
        static void AssignThreadId();

    private:
        static thread_local uint32_t t_threadId;

    };
}
