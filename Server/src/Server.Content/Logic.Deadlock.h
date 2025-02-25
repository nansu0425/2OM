#pragma once

namespace Server::Content::Logic
{
    class B;

    /*---------*
     *    A    *
     *---------*/

    class A
    {
    public:
        void IncreaseA();
        // A -> B 잠금
        void IncreaseAB(B& b);

    private:
        SERVER_CPPCORE_LOCK;
        uint32_t _a = 0;

    };

    class C;

    /*---------*
     *    B    *
     *---------*/

    class B
    {
    public:
        void IncreaseB();
        // B -> C 잠금
        void IncreaseBC(C& c);

    private:
        SERVER_CPPCORE_LOCK;
        uint32_t _b = 0;
    };

    /*---------*
     *    C    *
     *---------*/

    class C
    {
    public:
        void IncreaseC();
        // C -> A 잠금
        void IncreaseCA(A& a);

    private:
        SERVER_CPPCORE_LOCK;
        uint32_t _c = 0;
    };

    void RunDeadlockThreads(A& a, B& b, C& c);
}
