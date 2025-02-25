#include "Server.Content/Global.Pch.h"
#include "Server.Content/Logic.Deadlock.h"

namespace Server::Content::Logic
{
    void A::IncreaseA()
    {
        SERVER_CPPCORE_LOCK_GUARD;
        
        _a++;
        std::cout << "A: " << _a << std::endl;
    }

    void A::IncreaseAB(B &b)
    {
        SERVER_CPPCORE_LOCK_GUARD;
        
        _a++;
        std::cout << "A: " << _a << std::endl;

        b.IncreaseB();
    }

    void B::IncreaseB()
    {
        SERVER_CPPCORE_LOCK_GUARD;

        _b++;
        std::cout << "B: " << _b << std::endl;
    }

    void B::IncreaseBC(C& c)
    {
        SERVER_CPPCORE_LOCK_GUARD;

        _b++;
        std::cout << "B: " << _b << std::endl;

        c.IncreaseC();
    }

    void C::IncreaseC()
    {
        SERVER_CPPCORE_LOCK_GUARD;
        
        _c++;
        std::cout << "C: " << _c << std::endl;
    }

    void C::IncreaseCA(A& a)
    {
        SERVER_CPPCORE_LOCK_GUARD;

        _c++;
        std::cout << "C: " << _c << std::endl;

        a.IncreaseA();
    }

    void RunDeadlockThreads(A& a, B& b, C& c)
    {
        // A -> B 잠금 반복
        CppCore::Thread::Manager::Launch([&a, &b]()
                                         {
                                             while (true)
                                             {
                                                 a.IncreaseAB(b);
                                             }
                                         });

        // B -> C 잠금 반복
        CppCore::Thread::Manager::Launch([&b, &c]()
                                         {
                                             while (true)
                                             {
                                                 b.IncreaseBC(c);
                                             }
                                         });

        // C -> A 잠금 반복
        CppCore::Thread::Manager::Launch([&c, &a]()
                                         {
                                             while (true)
                                             {
                                                 c.IncreaseCA(a);
                                             }
                                         });
    }
}
